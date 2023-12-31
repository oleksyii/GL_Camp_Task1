#pragma once

namespace PNet
{
	static const int g_MaxPacketSize = 8192;
	#ifndef _WIN32
	static const int INVALID_SOCKET = ~0;
	typedef int BOOL;
	static const BOOL FALSE = 0;
	static const BOOL TRUE = 1;
	static const int SOCKET_ERROR = -1;

	#ifndef WSAGetLastError()
		#define WSAGetLastError() errno
	#endif
	#ifndef closesocket
		#define closesocket(fd) close(fd)
	#endif
	// #ifndef GetLastError()
	// 	#define GetLastError() errno
	// #endif

	#endif
}