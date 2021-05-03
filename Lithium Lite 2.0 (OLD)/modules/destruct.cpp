
#include "../misc/connector.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

std::string getexepath() {
	char path[MAX_PATH];
	::GetModuleFileName(0, path, MAX_PATH);
	return path;
}

std::string getexename() {
	std::string path = getexepath();
	std::string exename = path.substr(path.rfind("\\") + 1);
	return exename;
}

double cleanedstrings = 0;
void cleanstrings(DWORD pid, std::vector<std::string> findvector, bool ispca = false) {

	if (HANDLE processhandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid)) {
		for (size_t i = 0; i < findvector.size(); i++) {
			std::string lmao = findvector[i];
			for (const char x : lmao) {
				if (!isprint(x)) {
					findvector.erase(findvector.begin() + i);
					break;
				}
			}
		}

		if (pid != GetCurrentProcessId()) {
			MEMORY_BASIC_INFORMATION memory;
			INT64 address = 0;
			while (VirtualQueryEx(processhandle, (LPVOID)address, &memory, sizeof(MEMORY_BASIC_INFORMATION))) {
				if (memory.State == MEM_COMMIT && (
					(memory.Protect == PAGE_EXECUTE_READWRITE) |
					(memory.Protect == PAGE_READWRITE) |
					(memory.Protect == PAGE_EXECUTE_WRITECOPY) |
					(memory.Protect == PAGE_WRITECOPY))) {
					
					{
						std::vector<char> buffer(memory.RegionSize);
						if (ReadProcessMemory(processhandle, (LPVOID)address, &buffer[0], memory.RegionSize, 0)) {
							for (std::string x : findvector) {
								INT64 lenght = x.length();
								INT64 size = static_cast<INT64>(memory.RegionSize);
								for (INT64 i = 0; i <= size; i++) {
									INT64 j;
									for (j = 0; j < lenght; j++)
										if (buffer[i + j] != x[j])
											break;
									if (j == lenght) {

										if (ispca) {

											std::string current_pca;
											size_t current_pca_start = address + i;
											size_t location = current_pca_start;
											size_t new_pca_size = 0;

											for (;;) {

												std::vector<char>char_a(1);
												if (ReadProcessMemory(processhandle, (LPVOID)location, &char_a[0], (sizeof(char) * 1), 0)) {

													current_pca.push_back(char_a[0]);

												}

												std::vector<char>char_b(5);
												if (ReadProcessMemory(processhandle, (LPVOID)location, &char_b[0], (sizeof(char)*5), 0)) {
													
													size_t counter = 0; 
													for (const char x : char_b) { if (x <= 126 && x >= 32) {} else { counter++; } }
													if (counter == 5) { break; } else { new_pca_size += 2; }

												}

												location++;

											}

											size_t addition = 0;
											std::string new_pca;
											std::istringstream iss(current_pca);
											for (std::string line; std::getline(iss, line);) {

												if (line.find(getexename()) != std::string::npos) {

													addition += line.length() + 2;

												} else { new_pca += (line); }

											}

											char nullthat = 0;								
											for (size_t m = 0; m < current_pca.length(); m++) {
												WriteProcessMemory(processhandle, (LPVOID)(current_pca_start + m), &nullthat, 1, 0);
											}
											
											for (size_t m = 0; m < new_pca.length(); m++) {
												WriteProcessMemory(processhandle, (LPVOID)(current_pca_start + addition + m), &new_pca[m], 1, 0);
											}

											break;

										}
										else {
											std::string newstring;
											for (size_t y = 0; y < lenght; y++) { newstring.push_back(0); }
											WriteProcessMemory(processhandle, (LPVOID)(address + i), &newstring, lenght, 0);
										}

										cleanedstrings++;
									}
								}
							}
						}
					}

					{
						if (!ispca) {
							std::vector<WCHAR> buffer(memory.RegionSize);
							if (ReadProcessMemory(processhandle, (LPVOID)address, &buffer[0], memory.RegionSize, 0)) {
								for (std::string x : findvector) {
									INT64 lenght = x.length();
									INT64 size = static_cast<INT64>(memory.RegionSize);
									for (INT64 i = 0; i <= size; i++) {
										INT64 j;
										for (j = 0; j < lenght; j++)
											if (buffer[i + j] != x[j])
												break;
										if (j == lenght) {
											cleanedstrings++;
											WCHAR writeme = 0;
											INT64 x = i; INT64 counter = 0;
											for (;;) {
												WriteProcessMemory(processhandle, (LPVOID)(address + (x * (INT64)2)), &writeme, (sizeof(WCHAR)), 0);
												x++; counter++; if (counter >= lenght) { break; }
											}
										}
									}
								}
							}
						}
					}

				}
				address += memory.RegionSize;
			}
		}
	}

}

void cleanprefetch() {
	std::string prefetchstring = "\\Windows\\prefetch\\";
	std::string findmeprefetch = getexename();
	std::transform(findmeprefetch.begin(), findmeprefetch.end(), findmeprefetch.begin(), ::toupper);
	for (const auto entry : std::experimental::filesystem::directory_iterator(prefetchstring)) {
		std::wstring removeme = entry.path();
		std::string removemestring(removeme.begin(), removeme.end());
		if (strstr(removemestring.c_str(), findmeprefetch.c_str())) {
			remove(removemestring.c_str());
		}

		if (strstr(removemestring.c_str(), "WMIC")) {
			remove(removemestring.c_str());
		}
	}
}

bool cleandnscache() {
	BOOL(WINAPI * DoDnsFlushResolverCache)();
	*(FARPROC*)&DoDnsFlushResolverCache = GetProcAddress(LoadLibrary("dnsapi.dll"), "DnsFlushResolverCache");
	if (!DoDnsFlushResolverCache) return FALSE;
	return DoDnsFlushResolverCache();
}

std::vector<std::string>hostvector() {
	std::vector<std::string>returnme = {
	"http://cps.letsencrypt.org", "http://cps.root-x1.letsencrypt.org", "#http://cert.int-x3.letsencrypt.org/0D",
	"csp.int-x3.letsencrypt.org", "ert.int-x3.letsencrypt.org",
	"Let's Encrypt Authority X3", "Let's Encrypt1#0!", "cps.letsencrypt.org", "letsencrypt.org-ng.edgekey.net", "letsencrypt.org"
	"Let's Encrypt", "crypt1#0!", "vrt-debi", "skidclient.wtf", "https://skidclient.wtf/api/download" }; return returnme;
};

std::vector<std::string>exevector() {
	std::vector<std::string>returnme;
	std::string exepath = getexepath();
	returnme.push_back(exepath);

	std::string exename = getexename();
	returnme.push_back(exename);

	return returnme;
}

std::vector<std::string>pcavector() {
	std::vector<std::string>returnme;

	//std::string pca_path = "TRACE,0000,0000,PcaClient,MonitorProcess," + getexepath() + ",Time,0";
	std::string pca_path = "TRACE,";
	returnme.push_back(pca_path);

	return returnme;
}

void stop_service(const char* service_name) {

	SERVICE_STATUS Status;
	SC_HANDLE SCManager = OpenSCManager(NULL, NULL, MAXIMUM_ALLOWED);
	SC_HANDLE SHandle = OpenService(SCManager, service_name, MAXIMUM_ALLOWED);
	if (SHandle) {
		ControlService(SHandle, SERVICE_CONTROL_STOP, &Status);
	}
	CloseServiceHandle(SCManager);
	CloseServiceHandle(SHandle);

}

namespace lith {
	namespace module {
		namespace destruct {
			void execute() {

				lith::module::clicker::left::enabled = false;
				lith::module::clicker::right::enabled = false;
				lith::module::reach::enabled = false;
				lith::module::velocity::enabled = false;
				lith::module::throwpot::enabled = false;
				lith::module::fly::enabled = false;
				lith::module::nametags::enabled = false;
				lith::module::timer::enabled = false;
				lith::module::esp::enabled = false;
				lith::module::cavefinder::enabled = false;
				lith::module::bhop::enabled = false;
				lith::module::velocity::enabled = false;

				lith::module::clicker::left::selectedbind = 0;
				lith::module::clicker::right::selectedbind = 0;
				lith::module::reach::selectedbind = 0;
				lith::module::velocity::selectedbind = 0;
				lith::module::throwpot::selectedbind = 0;
				lith::module::fly::selectedbind = 0;
				lith::module::nametags::selectedbind = 0; 
				lith::module::timer::selectedbind = 0;
				lith::module::esp::selectedbind = 0;
				lith::module::cavefinder::selectedbind = 0;
				lith::module::bhop::selectedbind = 0;
				lith::module::velocity::selectedbind = 0;

				cleandnscache();

				cleanprefetch();

				while (lith::module::reach::used || lith::module::fly::used || lith::module::nametags::used || lith::module::timer::used || lith::module::esp::used || lith::module::cavefinder::used || lith::module::bhop::used || lith::module::velocity::used) {

					std::this_thread::sleep_for(std::chrono::milliseconds(10));

				}

				CloseHandle(lith::info::handle);

				//stop_service("DPS");
				lith::tools::terminateprocess(lith::tools::getprocessid("smartscreen.exe"));

				cleanstrings(lith::tools::getprocessid("explorer.exe"), pcavector(), true);

				cleanstrings(lith::tools::getprocessid("smartscreen.exe"), exevector());
				cleanstrings(lith::tools::getprocessid("smartscreen.exe"), hostvector());

				cleanstrings(lith::tools::getprocessid("SearchIndexer.exe"), exevector());
				cleanstrings(lith::tools::getprocessid("ctfmon.exe"), exevector());
				cleanstrings(lith::tools::getprocessid("lsass.exe"), hostvector());

				cleanstrings(lith::tools::getserviceid("PcaSvc"), exevector());
				cleanstrings(lith::tools::getserviceid("DiagTrack"), exevector());
				cleanstrings(lith::tools::getserviceid("DPS"), exevector());
				cleanstrings(lith::tools::getserviceid("Dnscache"), hostvector());

				MessageBoxA(0, std::string("Destruct complete. Cleaned a total of " + std::to_string((int)cleanedstrings) + " strings.").c_str(), " ", MB_ICONINFORMATION);

				std::exit(EXIT_SUCCESS);
				
			}
		}
	}

}
