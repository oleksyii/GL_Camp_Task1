// Client code
#include <PNet/IncludeMe.h>
#include <Platform/IncludeMe.h>

using namespace PNet;

std::atomic<bool> appCeased(false);
std::mutex m_consoleAccess; // Mutex for console access
std::string appName = "";
std::mutex m_appNameAccess;

typedef struct MyData
{
	Socket *socket;
	MyData(Socket *ptr) : socket(ptr){};
} MYDATA, *PMYDATA;

std::mutex m_tableAccess;
std::map<std::string, bool> table;

bool presentInMap(std::map<std::string, bool> map, std::string value)
{
	std::lock_guard<std::mutex> lock(m_tableAccess);
	std::map<std::string, bool>::iterator it = map.find(value);
	return (it == map.end() ? false : true);
}

bool ProcessPacket(Packet &packet)
{
	switch (packet.GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::lock_guard<std::mutex> lock(m_appNameAccess);
		packet >> appName;
		std::cout << appName << std::endl;
		if (!presentInMap(table, appName))
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table.insert(std::pair<std::string, bool>(appName, true));
		}
		else if (table[appName])
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table[appName] = false;
		}
		else if (table[appName])
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table[appName] = true;
		}
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		packet >> arraySize;
		std::cout << "Array size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
		return false;
	}
	return true;
}

/*
 * The fucntion's purpose is to get a name of the app to laucnh.
 * If the same name comes again it changes the atomic value to notify a thread to
 * force running app
 */
void HandleReceivingPackets(void *in)
{
	PMYDATA nn = static_cast<PMYDATA>(in);
	Socket socket = *(nn->socket);

	Packet packet;
	while (true)
	{
		PResult result = socket.Recv(packet);
		if (result != PResult::P_Success)
			break;

		if (!ProcessPacket(packet))
			break;
	}
	socket.Close();
}

void HandleSendingPackets(Socket &socket, Packet packet)
{
	PResult result;
	result = socket.Send(packet);

	if (result != PResult::P_Success)
		return;

	std::cout << "Attempting to send chunk of data..." << std::endl;
}

void HandleApp()
{
	bool proceed = false;
	{
		std::lock_guard<std::mutex> lock(m_tableAccess);
		std::lock_guard<std::mutex> lock2(m_appNameAccess);
		if (table[appName])
			proceed = true;
	}


	if (proceed)
	{
		ProceedPlatformSpecificCode_(m_appNameAccess, appName, appCeased, m_tableAccess, table);		
	}
	else
	{
		return;
	}

	return;
}

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock API succesfully itialized." << std::endl;
		PMYDATA myData;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			// #1
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4799)) == PResult::P_Success)
			{
				std::cout << "Succesfully conected to a server!" << std::endl;
				//  #2
				myData = new MYDATA(&socket);
				std::thread userInput(HandleReceivingPackets, static_cast<void *>(myData));
				userInput.detach();

				while (appName == "")
				{
					Sleep_(1000);
				}
				// #3
				std::thread appThread(HandleApp);
				appThread.detach();

				while (true)
				{
					if (!appCeased)
					{
						// #4
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("App is running");

						HandleSendingPackets(socket, stringPacket);
						Sleep_(1000);
					}
					else
					{
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("The app has ceased to exist");

						HandleSendingPackets(socket, stringPacket);
						appCeased = false;
						break;
					}
				}

				delete (myData);
			}
			else
			{
				std::cerr << "Failed to connect to a server." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	Pause_();
}