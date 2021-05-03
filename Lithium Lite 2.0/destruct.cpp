#include "main.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define crt_no_warnings

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
            while (NT_SUCCESS(ZwQueryVirtualMemory(processhandle, (LPVOID)address, MemoryBasicInformation, &memory,
                sizeof(MEMORY_BASIC_INFORMATION), nullptr))) {
                if (memory.State == MEM_COMMIT && (
                    (memory.Protect == PAGE_EXECUTE_READWRITE) |
                    (memory.Protect == PAGE_READWRITE) |
                    (memory.Protect == PAGE_EXECUTE_WRITECOPY) |
                    (memory.Protect == PAGE_WRITECOPY))) {

                        {
                            std::vector<char> buffer(memory.RegionSize);
                            if (NT_SUCCESS(
                                ZwReadVirtualMemory(processhandle, (LPVOID)address, &buffer[0], memory.RegionSize,
                                    nullptr))) {
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

                                                    std::vector<char> char_a(1);
                                                    if (ReadProcessMemory(processhandle, (LPVOID)location, &char_a[0],
                                                        (sizeof(char) * 1), 0)) {

                                                        current_pca.push_back(char_a[0]);

                                                    }

                                                    std::vector<char> char_b(5);
                                                    if (ReadProcessMemory(processhandle, (LPVOID)location, &char_b[0],
                                                        (sizeof(char) * 5), 0)) {

                                                        size_t counter = 0;
                                                        for (const char x : char_b) {
                                                            if (x <= 126 && x >= 32) {}
                                                            else { counter++; }
                                                        }
                                                        if (counter == 5) { break; }
                                                        else { new_pca_size += 2; }

                                                    }

                                                    location++;

                                                }

                                                size_t addition = 0;
                                                std::string new_pca;
                                                std::istringstream iss(current_pca);
                                                for (std::string line; std::getline(iss, line);) {

                                                    if (line.find(getexename()) != std::string::npos) {

                                                        addition += line.length() + 2;

                                                    }
                                                    else { new_pca += (line); }

                                                }

                                                char nullthat = 0;
                                                for (size_t m = 0; m < current_pca.length(); m++) {
                                                    WriteProcessMemory(processhandle, (LPVOID)(current_pca_start + m),
                                                        &nullthat, 1, 0);
                                                }

                                                for (size_t m = 0; m < new_pca.length(); m++) {
                                                    WriteProcessMemory(processhandle,
                                                        (LPVOID)(current_pca_start + addition + m),
                                                        &new_pca[m], 1, 0);
                                                }

                                                break;

                                            }
                                            else {
                                                std::string newstring;
                                                for (size_t y = 0; y < lenght; y++) { newstring.push_back(0); }
                                                WriteProcessMemory(processhandle, (LPVOID)(address + i), &newstring,
                                                    lenght, 0);
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
                                if (NT_SUCCESS(
                                    ZwReadVirtualMemory(processhandle, (LPVOID)address, &buffer[0], memory.RegionSize,
                                        nullptr))) {
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
                                                INT64 x = i;
                                                INT64 counter = 0;
                                                for (;;) {
                                                    WriteProcessMemory(processhandle, (LPVOID)(address + (x * (INT64)2)),
                                                        &writeme, (sizeof(WCHAR)), 0);
                                                    x++;
                                                    counter++;
                                                    if (counter >= lenght) { break; }
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

        std::vector<std::string> exevector() {
        std::vector<std::string> returnme;
        std::string exepath = getexepath();
        returnme.push_back(exepath);

        std::string exename = getexename();
        returnme.push_back(exename);

        return returnme;
    }

    std::vector<std::string> pcaclient() {
        std::vector<std::string> x;
        std::string one = "TRACE,0000,0000,PcaClient,MonitorProcess," + getexepath() + ",Time,0";
        std::string two = R"(\n)";
        x.push_back(one);
        x.push_back(two);
        return x;
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

    void ::modules::destruct::execute() {
        ::SetWindowPos(::gui::hwnd, NULL, ::utils::random_int(50, 500), ::utils::random_int(50, 500),
            ::utils::random_int(50, 500), ::utils::random_int(50, 500), SWP_FRAMECHANGED);

        ::ShowWindow(::gui::hwnd, 0);

        ::modules::clicker::left::enabled = false;
        ::modules::clicker::right::enabled = false;
        ::modules::reach::enabled = false;
        ::modules::velocity::enabled = false;
        ::modules::throwpot::enabled = false;
        ::modules::fly::enabled = false;
        ::modules::nametags::enabled = false;
        ::modules::timer::enabled = false;
        ::modules::esp::enabled = false;
        ::modules::cavefinder::enabled = false;
        ::modules::bhop::enabled = false;
        ::modules::velocity::enabled = false;
        ::modules::speed::enabled = false;

        ::modules::clicker::left::selected_bind = 0;
        ::modules::clicker::right::selected_bind = 0;
        ::modules::reach::selected_bind = 0;
        ::modules::velocity::selected_bind = 0;
        ::modules::throwpot::selected_bind = 0;
        ::modules::fly::selected_bind = 0;
        ::modules::nametags::selected_bind = 0;
        ::modules::timer::selected_bind = 0;
        ::modules::esp::selected_bind = 0;
        ::modules::cavefinder::selected_bind = 0;
        ::modules::bhop::selected_bind = 0;
        ::modules::velocity::selected_bind = 0;
        ::modules::speed::selected_bind = 0;

        while (::modules::speed::used || ::modules::reach::used || ::modules::fly::used || ::modules::nametags::used ||
            ::modules::timer::used || ::modules::esp::used || ::modules::cavefinder::used || ::modules::bhop::used ||
            ::modules::velocity::used) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        CloseHandle(::info::minecraft_handle);

        if (::modules::destruct::pcaclean) {
            cleanstrings(::utils::get_pid("explorer.exe"), pcaclient(), true);
        }
        if (::modules::destruct::traceless) {
            cleandnscache();
            cleanprefetch();
            cleanstrings(::utils::get_pid("smartscreen.exe"), exevector());
            cleanstrings(::utils::get_pid("smartscreen.exe"), hostvector());
            ::utils::terminate_process(::utils::get_pid("smartscreen.exe"));
            cleanstrings(::utils::get_pid("SearchIndexer.exe"), exevector());
            cleanstrings(::utils::get_pid("ctfmon.exe"), exevector());
            cleanstrings(::utils::get_pid("lsass.exe"), hostvector());
            cleanstrings(::utils::get_service_pid("PcaSvc"), exevector());
            cleanstrings(::utils::get_service_pid("DiagTrack"), exevector());
            cleanstrings(::utils::get_service_pid("DPS"), exevector());
            cleanstrings(::utils::get_service_pid("Dnscache"), hostvector());
        }
        std::exit(EXIT_SUCCESS);
    }