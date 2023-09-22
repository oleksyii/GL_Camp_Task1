#ifdef _WIN32
#include "Windows_.h"


void ProceedPlatformSpecificCode_(std::mutex& m_appNameAccess, std::string& appName, std::atomic<bool>& appCeased, std::mutex& m_tableAccess, std::map<std::string,bool>& table)
{
    		// Define the path to the application you want to launch
		// Convert the UTF-8 string to a UTF-16 wstrin
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring utf16String;
		{
			std::lock_guard<std::mutex> lock(m_appNameAccess);
			utf16String = converter.from_bytes(appName);
		}

		// CreateProcess parameters
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// Launch the application
		if (!CreateProcess(
				NULL,										// Application name (use NULL to use command line)
				const_cast<wchar_t *>(utf16String.c_str()), // Command line
				NULL,										// Process security attributes
				NULL,										// Thread security attributes
				FALSE,										// Inherit handles
				0,											// Creation flags
				NULL,										// Use parent's environment
				NULL,										// Use parent's current directory
				&si,										// STARTUPINFO structure
				&pi											// PROCESS_INFORMATION structure
				))
		{
			std::cerr << "Error creating process: " << GetLastError() << std::endl;
			return;
			appCeased = true;
		}
		std::cout << "succesfully created app PID: " << pi.dwProcessId << "\nThreadID: " << pi.dwThreadId << std::endl;
		// Wait for the application to finish, checking every one second
		DWORD exitCode;
		while (true)
		{
			if (WaitForSingleObject(pi.hProcess, 1000) == WAIT_OBJECT_0 &&
				GetExitCodeProcess(pi.hProcess, &exitCode))
			{
				appCeased = true;
				std::cout << "Application exited with code: " << exitCode << std::endl;
				break;
			}

			// TODO:Kill the app if table says false

			// Terminate the process
			{
				std::lock_guard<std::mutex> lock(m_tableAccess);
				std::lock_guard<std::mutex> lock2(m_appNameAccess);

				if (!table[appName])
				{
					HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pi.dwProcessId);
					if (TerminateProcess(hProc, 0) == 0)
					{
						std::cerr << "Error terminating process: " << GetLastError() << std::endl;
					}
					else
					{
						std::cout << "The process PID: " << pi.dwProcessId << " was succesfully stopped." << std::endl;
						CloseHandle(hProc);
						appCeased = true;
						break;
					}

					CloseHandle(hProc);
				}
			}
		}

		// Close process and thread handles
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
}
#endif