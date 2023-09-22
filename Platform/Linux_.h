#ifndef _WIN32
#include "General_.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define Sleep_(duration) sleep(duration/1000)
#define Pause_() getchar()
#define GetLastError() errno

void ProceedPlatformSpecificCode_(std::mutex& m_appNameAccess, std::string& appName, std::atomic<bool>& appCeased, std::mutex& m_tableAccess, std::map<std::string, bool>& table);
#endif