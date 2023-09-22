#ifdef _WIN32
    #include "General_.h"
    #ifdef _WIN32
    #include <WS2tcpip.h>
    #define WIN32_LEAN_AND_MEAN
    #include <WinSock2.h>
    #endif

    #define Pause_() system("pause")
    #define Sleep_(duration) Sleep(duration)
    void ProceedPlatformSpecificCode_(std::mutex &m_appNameAccess, std::string &appName, std::atomic<bool> &appCeased, std::mutex &m_tableAccess, std::map<std::string, bool> &table);
#endif