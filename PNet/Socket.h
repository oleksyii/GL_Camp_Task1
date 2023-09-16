#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndpoint.h"

namespace PNet
{
	class Socket
	{
	public:
		Socket(	IPVersion ipversion = IPVersion::IPv4,
				SocketHandle handle = INVALID_SOCKET); 
		PResult Create();
		PResult Close();
		PResult Bind(IPEndpoint endpoint);
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	private:
		PResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}