
#include "connector.h"

namespace lith {

	namespace tools {

		BOOL getprivilege(HANDLE processhandle, std::string perm) {

			const char* permchar = perm.c_str();
			HANDLE tokenhandle; LUID permissionidentifier; TOKEN_PRIVILEGES tokenpriv;

			if (OpenProcessToken(processhandle, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &tokenhandle)) {

				if (LookupPrivilegeValue(NULL, permchar, &permissionidentifier)) {

					tokenpriv.PrivilegeCount = 1;
					tokenpriv.Privileges[0].Luid = permissionidentifier;
					tokenpriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
					if (AdjustTokenPrivileges(tokenhandle, false, &tokenpriv, sizeof(tokenpriv), NULL, NULL)) { return true; }
					else { return false; }

				}
				else { return false; }

			}
			else { return false; }

			CloseHandle(tokenhandle);

		}

		DWORD getprocessid(std::string processname) {

			PROCESSENTRY32 processinfo;
			processinfo.dwSize = sizeof(processinfo);
			HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

			if (processesSnapshot == INVALID_HANDLE_VALUE) {

				return (DWORD)0;

			}

			Process32First(processesSnapshot, &processinfo);
			if (!processname.compare(processinfo.szExeFile)) {

				CloseHandle(processesSnapshot);
				return processinfo.th32ProcessID;

			}

			while (Process32Next(processesSnapshot, &processinfo)) {

				if (!processname.compare(processinfo.szExeFile)) {

					CloseHandle(processesSnapshot);
					return processinfo.th32ProcessID;

				}

			}
			
			CloseHandle(processesSnapshot); return (DWORD)0;

		}

		DWORD getserviceid(const char* serviceName) {

			const auto hScm = OpenSCManager(nullptr, nullptr, NULL);
			const auto hSc = OpenService(hScm, serviceName, SERVICE_QUERY_STATUS);

			SERVICE_STATUS_PROCESS ssp = {};
			DWORD bytesNeeded = 0;

			QueryServiceStatusEx(hSc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp), &bytesNeeded);
			CloseServiceHandle(hSc);
			CloseServiceHandle(hScm);

			return ssp.dwProcessId;

		}

		DWORD isminecraftrunning() {

			HWND windowhwnd = 0;
			if (HWND windowhwnd = FindWindowA(("LWJGL"), nullptr)) {

				if (GetWindowThreadProcessId(windowhwnd, &lith::info::pid)) {

					return lith::info::pid;

				}
				else {

					return 0;

				}

			}
			else {

				return 0;

			}
		}

		bool createhandletoprocess(DWORD pid) {

			lith::tools::getprivilege(GetCurrentProcess(), SE_DEBUG_NAME);

			if (lith::info::handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid)) {

				return true;

			}
			else {

				return false;

			}
		}

		float getrandomfloat(float min, float max) {

			float returnme;
			std::random_device dev;
			std::mt19937 rng(dev());

			if (min < max) {

				std::uniform_real_distribution<> dist(min, max);
				returnme = dist(rng);
				return returnme;
			}

			if (max < min) {

				std::uniform_real_distribution<> dist(max, min);
				returnme = dist(rng);
				return returnme;
			}

			if (max == min) {

				return min;
			}
		}

		void suspendprocess(DWORD pid) {
			if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
				BOOL result = SuspendThread(hProcess); CloseHandle(hProcess);
			}
		}

		void resumeprocess(DWORD pid) {
			if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
				BOOL result = ResumeThread(hProcess); CloseHandle(hProcess);
			}
		}

		void terminateprocess(DWORD pid) {
			if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
				BOOL result = TerminateProcess(hProcess, 1); CloseHandle(hProcess);
			}
		}

	}
}