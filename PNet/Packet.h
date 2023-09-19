#pragma once
#include <vector>
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace PNet
{
	class Packet
	{
	public:
		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t& data);

		std::vector<char>buffer
	};
}