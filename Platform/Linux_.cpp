#ifndef _WIN32
#include "Linux_.h"

void ProceedPlatformSpecificCode_(std::mutex& m_appNameAccess, std::string& appName, std::atomic<bool>& appCeased, std::mutex& m_tableAccess, std::map<std::string,bool>& table)
{
    pid_t childPid = fork(); // Create a child process

		if (childPid == -1)
		{
			std::cerr << "Error creating a child process." << std::endl;
			return;
		}
		else if (childPid == 0) // Inside the child
		{
			// Child process code
			std::lock_guard<std::mutex> lock(m_appNameAccess);
			// Launch the application using exec
			if (execlp(appName.c_str(), appName.c_str(), NULL) == -1)
			{
				std::cerr << "Error launching the application." << std::endl;
				return;
			}
		}
		else // Inside the parent
		{
			// Parent process code

			while (true)
			{
				// Check if the child process has finished
				int status;
				pid_t result = waitpid(childPid, &status, WNOHANG);

				if (result == -1)
				{
					std::cerr << "Error waiting for the child process." << std::endl;
					return;
				}
				else if (result > 0)
				{
					// The child process has finished
					if (WIFEXITED(status))
					{
						std::cout << "Application exited with status: " << WEXITSTATUS(status) << std::endl;
						appCeased = true;
					}
					else
					{
						std::cout << "Application terminated abnormally." << std::endl;
					}
					break; // Exit the loop
				}
				// Terminate the process
				{
					std::lock_guard<std::mutex> lock(m_tableAccess);
					std::lock_guard<std::mutex> lock2(m_appNameAccess);

					if (!table[appName])
					{
						pid_t temp = childPid;
						if (kill(childPid, SIGTERM) != 0)
						{
							std::cerr << "Error terminating process: " << GetLastError() << std::endl;
						}
						else
						{
							std::cout << "The process PID: " << temp << " was succesfully terminated." << std::endl;
							appCeased = true;
							break;
						}
					}
				}
				// Sleep(1000);
				sleep(1);
			}
		}
}

#endif