#include "IPEndpoint.h"
#include <assert.h>
#include <iostream>

namespace PNet
{
	const int IPv4_size = 16;
	const int IPv6_size = 46;

	IPEndpoint::IPEndpoint(const char* ip, unsigned short port)
	{
		this->port = port;

		in_addr addr; //location to store the ipv4 address
		int result = inet_pton(AF_INET, ip, &addr);

		if (result == 1)
		{
			if (addr.S_un.S_addr != INADDR_NONE)
			{
				ip_string = ip;
				hostname = ip;
				
				ip_bytes.resize(sizeof(ULONG));
				memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG));

				ipversion = IPVersion::IPv4;
				return;
			}
		}

		//attempt to resolve hostname to ipv4 address
		addrinfo hints = {}; //hints will filter the results we get back for getaddrinfo
		hints.ai_family = AF_INET; //ipv4 addresses only
		addrinfo* hostinfo = nullptr;
		result = getaddrinfo(ip, NULL, &hints, &hostinfo);
		if (result == 0)
		{
			sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);

			//host_addr->sin_addr.S_un.S_addr
			ip_string.resize(IPv4_size);
			inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], IPv4_size); //for ipv4 it needs to be 16, for ipv6 - 46
			
			hostname = ip;
			ULONG ip_long = host_addr->sin_addr.S_un.S_addr;
			ip_bytes.resize(sizeof(ULONG));
			memcpy(&ip_bytes[0], &ip_long, sizeof(ULONG));

			ipversion = IPVersion::IPv4;

			freeaddrinfo(hostinfo); //memory cleanup for getaddrinfo call
			return;
		}

		/**
		* Additional logic for IPv6 should go here if you will
		*/
	}

	IPEndpoint::IPEndpoint(sockaddr* addr)
	{
		assert(addr->sa_family == AF_INET);
		sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
		ipversion = IPVersion::IPv4;

		port = ntohs(addrv4->sin_port);
		ip_bytes.resize(sizeof(ULONG));
		memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ULONG));


		ip_string.resize(IPv4_size);
		inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], IPv4_size); //for ipv4 it needs to be 16, for ipv6 - 46

		hostname = ip_string;
	}

	IPVersion IPEndpoint::GetIPVersion()
	{
		return ipversion;
	}

	std::vector<uint8_t> IPEndpoint::GetIPBytes()
	{
		return ip_bytes;
	}

	std::string IPEndpoint::GetHostName()
	{
		return hostname;
	}

	std::string IPEndpoint::GetIpString()
	{
		return ip_string;
	}

	unsigned short IPEndpoint::GetPort()
	{
		return port;
	}
	sockaddr_in IPEndpoint::GetSockaddrIPv4()
	{
		assert(ipversion == IPVersion::IPv4);
		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
		addr.sin_port = htons(port);
		return addr;
	}
	void IPEndpoint::Print()
	{
		switch (ipversion)
		{
		case IPVersion::IPv4:
			std::cout << "Ip Version: IPv4" << std::endl;
			break;
		case IPVersion::IPv6:
			std::cout << "Ip Version: IPv6" << std::endl;
			break;
		default:
			std::cout << "Ip Version: Unknown" << std::endl;
		}
		std::cout << "Hostname: " << hostname << std::endl;
		std::cout << "IP: " << ip_string << std::endl;
		std::cout << "Port: " << port << std::endl;
		std::cout << "Hostname: " << hostname << std::endl ;
		std::cout << "IP Bytes..." << std::endl;
		for (auto& digit : ip_bytes)
		{
			std::cout << (int)digit << std::endl;
		}
	}
}
