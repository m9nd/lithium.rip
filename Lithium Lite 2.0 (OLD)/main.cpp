/* This version should have all auth removed and should compile for you just fine. If you're looking for the full version of this source, it should have
*  already been already uploaded. I'm too lazy to make sure everything is removed so if I forgot to do something just remove it yourself or whatever.e
*/

/*
* Credit to Paladin for some of their old shitty code.
* Credit to Koid for just about 99% of our source.
* Credit to Cucklord for some other parts of this entirely skidded source
*/


#include "misc/connector.h"

void changecolor(float col[4]);

namespace lith {
    namespace gui {
        ImVec4 color1 = ImColor(0.9f, 0.24f, 0.24f);
        ImVec4 color2 = ImVec4(0.56f, 0.00f, 1.00f, 0.50f);
        ImVec4 color3 = ImVec4(1.00f, 1.00f, 1.00f, 0.15f);
    }
}

void init_console() {

    SetConsoleTitleA("");

    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

    DWORD style = GetWindowLong(GetConsoleWindow(), GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX & ~WS_SYSMENU;
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, style);
    SetWindowPos(GetConsoleWindow(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;

    GetConsoleCursorInfo(out, &cci);
    cci.bVisible = false;
    SetConsoleCursorInfo(out, &cci);

    DWORD dw_mode = 0;

    GetConsoleMode(out, &dw_mode);
    SetConsoleMode(out, dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    DWORD prev_mode = 0; 
    
    GetConsoleMode(out, &prev_mode);
    SetConsoleMode(out, prev_mode & ~ENABLE_QUICK_EDIT_MODE);

    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(out, &info);

    COORD new_size = {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };

    SetConsoleScreenBufferSize(out, new_size);
}

#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004
#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2
typedef struct _SYSTEM_HANDLE {
    ULONG ProcessId;
    BYTE ObjectTypeNumber;
    BYTE Flags;
    USHORT Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, * PSYSTEM_HANDLE;
typedef struct _SYSTEM_HANDLE_INFORMATION {
    ULONG HandleCount;
    SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;
typedef NTSTATUS(NTAPI* _NtDuplicateObject)(HANDLE SourceProcessHandle, HANDLE SourceHandle, HANDLE TargetProcessHandle, PHANDLE TargetHandle, ACCESS_MASK DesiredAccess, ULONG Attributes, ULONG Options);

typedef LONG NTSTATUS, * PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

static RTL_OSVERSIONINFOW GetRealOSVersion()
{
    HMODULE hMod = GetModuleHandleA(xors("ntdll.dll"));
    if (hMod)
    {
        RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)GetProcAddress(hMod, xors("RtlGetVersion"));
        if (fxPtr != nullptr)
        {
            RTL_OSVERSIONINFOW rovi = { 0 };
            rovi.dwOSVersionInfoSize = sizeof(rovi);
            if (STATUS_SUCCESS == fxPtr(&rovi))
            {
                return rovi;
            }
        }
    }
    RTL_OSVERSIONINFOW rovi = { 0 };
    return rovi;
}
static RTL_OSVERSIONINFOW WindowsVersion()
{
    RTL_OSVERSIONINFOW i = GetRealOSVersion();
    return i;
}

static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
static std::wstring s2ws(const std::string& str)
{
    return converter.from_bytes(str);
}
static std::string ws2s(const std::wstring& wstr)
{
    return converter.to_bytes(wstr);
}

static bool verifyembeddedsignature(LPCWSTR pwszSourceFile)
{
    LONG lStatus;

    // Initialize the WINTRUST_FILE_INFO structure.

    WINTRUST_FILE_INFO FileData;

    memset(&FileData, 0, sizeof(FileData));

    FileData.cbStruct = sizeof(WINTRUST_FILE_INFO);
    FileData.pcwszFilePath = pwszSourceFile;
    FileData.hFile = NULL;
    FileData.pgKnownSubject = NULL;

    /*
    WVTPolicyGUID specifies the policy to apply on the file
    WINTRUST_ACTION_GENERIC_VERIFY_V2 policy checks:
    1) The certificate used to sign the file chains up to a root
    certificate located in the trusted root certificate store. This
    implies that the identity of the publisher has been verified by
    a certification authority.
    2) In cases where user interface is displayed (which this example
    does not do), WinVerifyTrust will check for whether the
    end entity certificate is stored in the trusted publisher store,
    implying that the user trusts content from this publisher.
    3) The end entity certificate has sufficient permission to sign
    code, as indicated by the presence of a code signing EKU or no
    EKU.
    */

    GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    WINTRUST_DATA WinTrustData;

    // Initialize the WinVerifyTrust input data structure.

    // Default all fields to 0.
    memset(&WinTrustData, 0, sizeof(WinTrustData));

    WinTrustData.cbStruct = sizeof(WinTrustData);

    // Use default code signing EKU.
    WinTrustData.pPolicyCallbackData = NULL;

    // No data to pass to SIP.
    WinTrustData.pSIPClientData = NULL;

    // Disable WVT UI.
    WinTrustData.dwUIChoice = WTD_UI_NONE;

    // No revocation checking.
    WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;

    // Verify an embedded signature on a file.
    WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;

    // Verify action.
    WinTrustData.dwStateAction = WTD_STATEACTION_VERIFY;

    // Verification sets this value.
    WinTrustData.hWVTStateData = NULL;

    // Not used.
    WinTrustData.pwszURLReference = NULL;

    // This is not applicable if there is no UI because it changes 
    // the UI to accommodate running applications instead of 
    // installing applications.
    WinTrustData.dwUIContext = 0;

    // Set pFile.
    WinTrustData.pFile = &FileData;

    // WinVerifyTrust verifies signatures as specified by the GUID 
    // and Wintrust_Data.
    lStatus = WinVerifyTrust(
        NULL,
        &WVTPolicyGUID,
        &WinTrustData);

    bool good = false;

    switch (lStatus) {
    case ERROR_SUCCESS:
        /*
        Signed file:
        - Hash that represents the subject is trusted.
        - Trusted publisher without any verification errors.
        */
        good = true;
        break;
    default:
        // The UI was disabled in dwUIChoice or the admin policy 
        // has disabled user trust. lStatus contains the 
        // publisher or time stamp chain error.
        wprintf_s(L"Error is: 0x%x.\n", lStatus);
        break;
    }

    // Any hWVTStateData must be released by a call with close.
    WinTrustData.dwStateAction = WTD_STATEACTION_CLOSE;

    lStatus = WinVerifyTrust(
        NULL,
        &WVTPolicyGUID,
        &WinTrustData);

    return good;
}

static std::vector<std::pair<DWORD, std::pair<std::string, ACCESS_MASK>>> findhandlestoprocess(DWORD pid)
{
    std::vector<std::pair<DWORD, std::pair<std::string, ACCESS_MASK>>> keks;

    auto winver = WindowsVersion();
    DWORD pathSize = MAX_PATH;

    std::string defsvchost = getenv(xors("SystemDrive"));
    std::string defconhost = getenv(xors("SystemDrive"));
    std::string deflsass = getenv(xors("SystemDrive"));
    std::string defexplorer = getenv(xors("SystemDrive"));
    std::string defcsrss = getenv(xors("SystemDrive"));
    std::string defwininit = getenv(xors("SystemDrive"));
    std::string defwinlogon = getenv(xors("SystemDrive"));
    defsvchost.append(xors("\\Windows\\System32\\svchost.exe"));
    defconhost.append(xors("\\Windows\\System32\\conhost.exe"));
    deflsass.append(xors("\\Windows\\System32\\lsass.exe"));
    defexplorer.append(xors("\\Windows\\explorer.exe"));
    defcsrss.append(xors("\\Windows\\System32\\csrss.exe"));
    defwininit.append(xors("\\Windows\\System32\\wininit.exe"));
    defwinlogon.append(xors("\\Windows\\System32\\winlogon.exe"));

    wchar_t thispath[MAX_PATH];
    GetModuleFileNameW(NULL, thispath, MAX_PATH);

    PSYSTEM_HANDLE_INFORMATION handleInfo;
    ULONG handleInfoSize = 0x10000;
    handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

    NTSTATUS status;
    _NtDuplicateObject NtDuplicateObject = (_NtDuplicateObject)GetProcAddress(GetModuleHandleA(xors("ntdll.dll")), xors("NtDuplicateObject"));

    while ((status = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
        handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

    for (ULONG i = 0; i < handleInfo->HandleCount; i++)
    {
        SYSTEM_HANDLE handle = handleInfo->Handles[i];
        HANDLE dupHandle = NULL;

        if ((int)handle.ObjectTypeNumber != 7) // Process
            continue;

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_DUP_HANDLE, false, handle.ProcessId);
        NTSTATUS succ = NtDuplicateObject(processHandle, (HANDLE)handle.Handle, GetCurrentProcess(), &dupHandle, PROCESS_QUERY_LIMITED_INFORMATION, 0, 0);
        if (NT_SUCCESS(succ))
        {
            wchar_t modulePath[MAX_PATH];

            if (winver.dwMajorVersion == 6 && winver.dwMinorVersion == 1) // Win 7
                QueryFullProcessImageNameW(dupHandle, 0, modulePath, &pathSize);
            else
                GetModuleFileNameExW(dupHandle, NULL, modulePath, MAX_PATH);
            std::wstring mod(modulePath);

            if (mod == thispath)
            {
                char badPath[MAX_PATH];

                if (winver.dwMajorVersion == 6 && winver.dwMinorVersion == 1) // Win 7
                    QueryFullProcessImageNameA(processHandle, 0, badPath, &pathSize);
                else
                    GetModuleFileNameExA(processHandle, NULL, badPath, MAX_PATH);

                if (_stricmp(badPath, defsvchost.c_str()) == 0 || _stricmp(badPath, deflsass.c_str()) == 0 || _stricmp(badPath, defexplorer.c_str()) == 0 || _stricmp(badPath, defcsrss.c_str()) == 0 || _stricmp(badPath, defwininit.c_str()) == 0)
                {
                    if (winver.dwMajorVersion == 10) // why the fuck is nothing signed in windows 7 or 8?
                    {
                        if (!verifyembeddedsignature(s2ws(badPath).c_str()))
                            goto yup;
                    }
                }
                else if (_stricmp(badPath, defconhost.c_str()) != 0 && _stricmp(badPath, defwinlogon.c_str()) != 0) // conhost & winlogon are unsigned
                    goto yup;
                goto kys;
            yup:
                keks.push_back({ handle.ProcessId, { badPath, handle.GrantedAccess } });
            }
        }
    kys:
        CloseHandle(processHandle);
        CloseHandle(dupHandle);
    }
    free(handleInfo);

    return keks;
}

const std::vector<std::tuple<std::string, std::string>> process_list =
{
    { xors("Fiddler Everywhere.exe"),	xors("Fiddler web debugging tool") },		   // Fiddler web debugging tool
    { xors("ollydbg.exe"),	xors("OllyDebug debugger") },		   // OllyDebug debugger
    { xors("tcpview.exe"),	xors("Part of Sysinternals Suite") },			   // Part of Sysinternals Suite
    { xors("autoruns.exe"),	xors("Part of Sysinternals Suite") },	   // Part of Sysinternals Suite
    { xors("autorunsc.exe"), xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("filemon.exe"),	xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("procmon.exe"),	xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("idag.exe"), xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("hookshark.exe"), xors("Part of Sysinternals Suite") },	   // Part of Sysinternals Suite
    { xors("peid.exe"), xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("lordpe.exe"), xors("Part of Sysinternals Suite") },		   // Part of Sysinternals Suite
    { xors("regmon.exe"), xors("Part of Sysinternals Suite") },	   // Part of Sysinternals Suite
    { xors("idaq.exe"), xors("IDA Pro Interactive Disassembler") },	   // IDA Pro Interactive Disassembler
    { xors("idaq64.exe"), xors("IDA Pro Interactive Disassembler") },		   // IDA Pro Interactive Disassembler
    { xors("ImmunityDebugger.exe"), xors("ImmunityDebugger") },   // ImmunityDebugger
    { xors("Wireshark.exe"), xors("Wireshark packet sniffer") },		   // Wireshark packet sniffer
    { xors("dumpcap.exe"), xors("Network traffic dump tool") },			   // Network traffic dump tool
    { xors("HookExplorer.exe"), xors("Find various types of runtime hooks") },	   // Find various types of runtime hooks
    { xors("ImportREC.exe"), xors("Import Reconstructor") },		   // Import Reconstructor
    { xors("PETools.exe"), xors("PE Tools") },			   // PE Tool
    { xors("LordPE.exe"), xors("LordPE") },			   // LordPE
    { xors("SysInspector.exe"), xors("ESET SysInspector") },	   // ESET SysInspector
    { xors("proc_analyzer.exe"), xors("IDA Pro Interactive Disassembler") },	   // Part of SysAnalyzer iDefense
    { xors("sysAnalyzer.exe"), xors("Part of SysAnalyzer iDefense") },		   // Part of SysAnalyzer iDefense
    { xors("sniff_hit.exe"), xors("Part of SysAnalyzer iDefense") },		   // Part of SysAnalyzer iDefense
    { xors("joeboxcontrol.exe"), xors("Part of Joe Sandbox") },	   // Part of Joe Sandbox
    { xors("joeboxserver.exe"), xors("Part of Joe Sandbox") },	   // Part of Joe Sandbox
    { xors("ida.exe"), xors("IDA Hexrays Pro") },				   // IDA Hexrays Pro
    { xors("HTTPDebuggerSvc.exe"), xors("HTTPDEBUGGER") },     // HTTPDEBUGGER
    { xors("ResourceHacker.exe"),	xors("RESOURCE HACKER") },		   // RESOURCE HACKER
    { xors("ProcessHacker.exe"), xors("PROCESS HACKER") },      // PROCESS HACKER
    { xors("cheatengine-x86_64-SSE4-AVX2.exe"), xors("CHEAT ENGINE") },   // CHEAT ENGINE
    { xors("cheatengine-i386.exe"), xors("CHEAT ENGINE") },   // CHEAT ENGINE
    { xors("cheatengine-x86_64.exe"), xors("CHEAT ENGINE") }, // CHEAT ENGINE
};

const std::vector<std::string> bad_titles =
{
    xors("cheat engine"),
    xors("- ida"),
    xors("http Debugger"),
    xors("dbg"),
    xors("debugger"),
    xors("disassembler"),
    xors("decompiler"),
    xors("fiddler"),
    xors("wireshark"),
    xors("process hacker"),
    xors("string search"),
    //xors("visual studio")
};

void replacestr(std::string& s, const std::string& search, const std::string& replace)
{
    for (size_t pos = 0; ; pos += replace.length())
    {
        pos = s.find(search, pos);
        if (pos == std::string::npos) break;
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
}

void integrity() {

    while (true) {

        if (!lith::info::verified) {

            if (lith::module::clicker::left::enabled ||
                lith::module::clicker::right::enabled ||
                lith::module::reach::enabled ||
                lith::module::velocity::enabled) {

                std::exit(EXIT_SUCCESS);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void copy_to_clipboard(HWND hwnd, const std::string& s) {

    OpenClipboard(hwnd);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg) {

        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

std::string random_string(std::size_t size) {

    const std::string chars = xors("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < size; ++i)
        random_string += chars[distribution(generator)];

    return random_string;
}


static std::string xorr(std::string toEncrypt, const char* key, size_t key_len)
{
    std::string output = toEncrypt;
    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key[i % key_len];
    return output;
}

static std::string hex2str(std::string hex)
{
    int len = (int)hex.length();
    std::string s;
    for (int i = 0; i < len; i += 2)
    {
        std::string byte = hex.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        s.push_back(chr);
    }
    return s;
}

static std::string str2hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

int main() {

    init_console();

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(out, 12);

    std::cout << xors(R"(
██╗░░░░░██╗████████╗██╗░░██╗██╗██╗░░░██╗███╗░░░███╗  ██╗░░░░░██╗████████╗███████╗
██║░░░░░██║╚══██╔══╝██║░░██║██║██║░░░██║████╗░████║  ██║░░░░░██║╚══██╔══╝██╔════╝
██║░░░░░██║░░░██║░░░███████║██║██║░░░██║██╔████╔██║  ██║░░░░░██║░░░██║░░░█████╗░░
██║░░░░░██║░░░██║░░░██╔══██║██║██║░░░██║██║╚██╔╝██║  ██║░░░░░██║░░░██║░░░██╔══╝░░
███████╗██║░░░██║░░░██║░░██║██║╚██████╔╝██║░╚═╝░██║  ███████╗██║░░░██║░░░███████╗
╚══════╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░╚═════╝░╚═╝░░░░░╚═╝  ╚══════╝╚═╝░░░╚═╝░░░╚══════╝

██╗░░░░░███████╗░█████╗░██╗░░██╗███████╗██████╗░
██║░░░░░██╔════╝██╔══██╗██║░██╔╝██╔════╝██╔══██╗
██║░░░░░█████╗░░███████║█████═╝░█████╗░░██║░░██║
██║░░░░░██╔══╝░░██╔══██║██╔═██╗░██╔══╝░░██║░░██║
███████╗███████╗██║░░██║██║░╚██╗███████╗██████╔╝
╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝╚═════╝░                                                                                                  
    )") << std::endl;

    SetConsoleTextAttribute(out, 7);

    lith::info::stage = 1;

    auto handles = findhandlestoprocess(0);
    for (auto i : handles)
    {
        HANDLE term = OpenProcess(PROCESS_TERMINATE, false, i.first);
        TerminateProcess(term, 1);
    }

    std::vector<std::string> detected;
    for (auto tuple : process_list)
    {
        DWORD pid = lith::tools::getprocessid(std::get<0>(tuple));
        if (pid != NULL)
        {
            lith::tools::terminateprocess(pid);
            detected.push_back(std::get<1>(tuple));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    lith::info::stage = 2;

    //CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&selfprotect, nullptr, 0, 0);
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&integrity, nullptr, 0, 0);

    lith::info::stage = 5;

    bool first = true;

    while (true) {

        if (first) {

            std::cout << xors("Waiting for Minecraft...") << std::endl;
            first = false;
        }
        else if (!lith::tools::isminecraftrunning()) {

            std::cout << xors("No supported Minecraft version running.") << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::exit(EXIT_SUCCESS);
        }
        else {

            if (!lith::tools::createhandletoprocess(lith::info::pid)) {

                std::string cmd = xors("/C echo Error - Lithium Lite v") + std::string(lith::info::version) + xors(" & echo. & echo Unable to create a handle to the target process. ") + std::string("Stage: " + std::to_string(lith::info::stage)) + xors("& echo. & pause");
                ShellExecuteA(0, xors("runas"), xors("cmd.exe"), cmd.c_str(), 0, SW_SHOW);
                std::exit(EXIT_SUCCESS);
            }
            else {

                char window[MAX_PATH];
                GetWindowTextA(FindWindowA(xors("LWJGl"), nullptr), window, MAX_PATH);
                std::cout << window << xors(" found.");
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    ShowWindow(GetConsoleWindow(), 0);

    RECT rect;
    int x = 500;
    int y = 300;
    if (GetWindowRect(GetDesktopWindow(), &rect)) {

        x = rect.right - rect.left;
        y = rect.bottom - rect.top;
    }

    lith::info::stage = 6;

    const int width = 720;
    const int height = 530;

    ::SetWindowPos(lith::gui::hwnd, NULL, x / 2 - 317, y / 2 - 315, width, height, SWP_FRAMECHANGED);

    ::ShowWindow(lith::gui::hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(lith::gui::hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    auto oxygenregular = io.Fonts->AddFontFromMemoryCompressedTTF(roboto_compressed_data, 14, 14.f, NULL, io.Fonts->GetGlyphRangesDefault());

    ImFontConfig config;
    config.MergeMode = true;
    config.PixelSnapH = true;

    static const ImWchar ranges[] =
    {
        0xf000,
        0xf976,
        0
    };

    auto fa = io.Fonts->AddFontFromMemoryCompressedTTF(fa_compressed_data, fa_compressed_size, 15, &config, ranges);

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(lith::gui::hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    ImVec4 clear_color = ImColor(0, 0, 0);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    io.IniFilename = NULL;

    lith::launch::all_threads();

    while (msg.message != WM_QUIT && lith::info::verified) {

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        
        const auto style = &ImGui::GetStyle();
        const auto colors = style->Colors;

        style->WindowBorderSize = 1.f;
        style->WindowRounding = 0.f;
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->FrameRounding = 0.f;
        style->GrabRounding = 0.f;
        style->ChildRounding = 0.f;
        style->ItemSpacing = ImVec2(5, 10);
        style->FramePadding = ImVec2(1, 1);
        style->PopupRounding = 3.f;

        //colors[ImGuiCol_Text] = ImColor(133, 130, 132);
        //colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 1.00f, 1.00f, 0.25f);
        //colors[ImGuiCol_WindowBg] = ImColor(28, 28, 28);
        //colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        //colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

        colors[ImGuiCol_Border] = ImColor(51, 51, 51);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

        colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.10f, 0.10f, 0.15f, 0.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(lith::gui::color1);

        colors[ImGuiCol_SliderGrab] = ImVec4(lith::gui::color1); //used for sliders
        colors[ImGuiCol_SliderGrabActive] = ImVec4(lith::gui::color1); //used for sliders

        colors[ImGuiCol_Button] = ImColor(20, 20, 20);
        colors[ImGuiCol_ButtonHovered] = ImColor(20, 20, 20);
        colors[ImGuiCol_ButtonActive] = ImColor(20, 20, 20);

        colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

        colors[ImGuiCol_Separator] = ImVec4(lith::gui::color3);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(lith::gui::color3);
        colors[ImGuiCol_SeparatorActive] = ImVec4(lith::gui::color3);

        colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.05f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
        
        colors[ImGuiCol_WindowBg] = ImColor(28, 28, 28);
        colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 20);
        colors[ImGuiCol_FrameBg] = ImColor(45, 45, 45);
        colors[ImGuiCol_FrameBgHovered] = ImColor(45, 45, 45);
        colors[ImGuiCol_FrameBgActive] = ImColor(45, 45, 45);
        colors[ImGuiCol_ChildBg] = ImColor(23, 23, 23);

        {
            ImGui::SetNextWindowSize(ImVec2(width, height));
            ImGui::SetNextWindowPos(ImVec2(0, 0));

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            ImGui::Begin(("##main"), NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

            if (!lith::gui::item_being_used) {

                if (ImGui::IsItemActive()) {

                    lith::gui::window_being_dragged = true;

                }
                else {

                    lith::gui::window_being_dragged = false;

                }

            }

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(19, 120));

            ImGui::SetCursorPos(ImVec2(0, 0));
            ImGui::BeginChild("##tabs", ImVec2(75, height), true);
            {

                //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(75, height), ImColor(23, 23, 23));
            
                ImGui::PopStyleVar();

                ImGui::NewLine();

                //ImGui::SetCursorPos(ImVec2(40, 35));

                ImGui::PushFont(fa);

                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(23, 23, 23));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(23, 23, 23));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(23, 23, 23));

                if (lith::gui::tab_main != 1) {
                    ImGui::Button(u8"\uf05b", ImVec2(40, 40), false);
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(lith::gui::color1));
                    ImGui::Button(u8"\uf05b", ImVec2(40, 40), false);
                    ImGui::PopStyleColor();
                }
                if (ImGui::IsItemClicked()) {
                    lith::gui::tab_main = 1;
                }

                //ImGui::SetCursorPos(ImVec2(40, 125));

                if (lith::gui::tab_main != 2) {
                    ImGui::Button(u8"\uf554", ImVec2(40, 40), false);
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(lith::gui::color1));
                    ImGui::Button(u8"\uf554", ImVec2(40, 40), false);
                    ImGui::PopStyleColor();
                }
                if (ImGui::IsItemClicked()) {
                    lith::gui::tab_main = 2;
                }

                //ImGui::SetCursorPos(ImVec2(40, 215));

                if (lith::gui::tab_main != 3) {
                    ImGui::Button(u8"\uf06e", ImVec2(40, 40), false);
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(lith::gui::color1));
                    ImGui::Button(u8"\uf06e", ImVec2(40, 40), false);
                    ImGui::PopStyleColor();
                }
                if (ImGui::IsItemClicked()) {
                    lith::gui::tab_main = 3;
                }

                //ImGui::SetCursorPos(ImVec2(40, 305));

                if (lith::gui::tab_main != 4) {
                    ImGui::Button(u8"\uf0c9", ImVec2(40, 40), false);
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(lith::gui::color1));
                    ImGui::Button(u8"\uf0c9", ImVec2(40, 40), false);
                    ImGui::PopStyleColor();
                }
                if (ImGui::IsItemClicked()) {
                    lith::gui::tab_main = 4;
                }

                //ImGui::SetCursorPos(ImVec2(40, 400));

                if (lith::gui::tab_main != 5) {
                    ImGui::Button(u8"\uf057", ImVec2(40, 40), false);
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(lith::gui::color1));
                    ImGui::Button(u8"\uf057", ImVec2(40, 40), false);
                    ImGui::PopStyleColor();
                }
                if (ImGui::IsItemClicked()) {
                    lith::gui::tab_main = 5;
                }

                ImGui::PopStyleColor(3);

                ImGui::PopFont();

                ImGui::EndChild();
            }

            ImGui::PopStyleVar();

            ImGui::SetCursorPosY(15);

            ImGui::Spacing(); ImGui::SameLine(90);

            if (lith::gui::tab_main == 1) {
                ImGui::BeginChild(("##left_clicker_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Left clicker"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::clicker::left::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::clicker::left::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::clicker::left::bindpressed = true;
                        lith::module::clicker::left::bind = "[...]";
                    }

                    ImGui::Text(("Average CPS"));
                    ImGui::SliderFloat(("##CPS"), &lith::module::clicker::left::value, 5.f, 20.f, "%.1f");

                    ImGui::Text("Blockhit Delay");
                    ImGui::SliderFloat(("##Blockhit delay"), &lith::module::clicker::left::value2, 500.f, 1000.f, "%.0f");

                    ImGui::Checkbox(("Inventory"), &lith::module::clicker::left::inventory);
                    ImGui::Checkbox(("Blockhit"), &lith::module::clicker::left::blockhit);
                    ImGui::Checkbox(("RMB Lock"), &lith::module::clicker::left::rmb_lock);

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##right_clicker_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Right clicker"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::clicker::right::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::clicker::right::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::clicker::right::bindpressed = true;
                        lith::module::clicker::right::bind = "[...]";
                    }

                    ImGui::Text(("Average CPS"));

                    ImGui::SliderFloat(("##CPS"), &lith::module::clicker::right::value, 5.f, 20.f, "%.1f");

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##reach_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Reach"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::reach::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::reach::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::reach::bindpressed = true;
                        lith::module::reach::bind = "[...]";
                    }

                    if (lith::module::reach::minvalue > lith::module::reach::maxvalue) {

                        lith::module::reach::minvalue = lith::module::reach::maxvalue;

                    }

                    ImGui::Text(("Minimum Reach"));

                    ImGui::SliderFloat(("##Minimum"), &lith::module::reach::minvalue, 3.f, 6.f, "%.2f");

                    if (lith::module::reach::maxvalue < lith::module::reach::minvalue) {

                        lith::module::reach::maxvalue = lith::module::reach::minvalue;

                    }

                    ImGui::Text(("Maximum Reach"));

                    ImGui::SliderFloat(("##Maximum"), &lith::module::reach::maxvalue, 3.f, 6.f, "%.2f");

                    ImGui::Checkbox(("Only while sprinting"), &lith::module::reach::onlysprinting);

                    ImGui::EndChild();
                }

                ImGui::Spacing(); ImGui::SameLine(90);

                ImGui::BeginChild(("##velocity_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Velocity"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::velocity::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::velocity::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::velocity::bindpressed = true;
                        lith::module::velocity::bind = "[...]";
                    }

                    if (lith::module::velocity::minvalue > lith::module::velocity::maxvalue) {

                        lith::module::velocity::minvalue = lith::module::velocity::maxvalue;

                    }

                    ImGui::Text(("Minimum Velocity"));

                    ImGui::SliderFloat(("##Minimum"), &lith::module::velocity::minvalue, 1.f, 100.f, "%.2f");

                    if (lith::module::velocity::maxvalue < lith::module::velocity::minvalue) {

                        lith::module::velocity::maxvalue = lith::module::velocity::minvalue;

                    }

                    ImGui::Text(("Maximum Velocity"));

                    ImGui::SliderFloat(("##Maximum"), &lith::module::velocity::maxvalue, 1.f, 100.f, "%.2f");

                    ImGui::Checkbox(("Only while sprinting"), &lith::module::velocity::onlysprinting);

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##throwpot_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Throwpot"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::throwpot::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::throwpot::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::throwpot::bindpressed = true;
                        lith::module::throwpot::bind = "[...]";
                    }

                    ImGui::Text(("Potion Slots"));

                    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 1));

                    for (int i = 0; i < 9; i++) {

                        ImGui::Checkbox(std::string("##slot" + std::to_string(i)).c_str(), &lith::module::throwpot::slot[i]);

                        ImGui::SameLine();
                    }

                    ImGui::PopStyleVar();

                    ImGui::NewLine();

                    ImGui::Text("Throw Delay");

                    ImGui::SliderFloat(("##Delay"), &lith::module::throwpot::value, 100.f, 500.f, "%.0f");

                    ImGui::Text("Return Slot");

                    ImGui::SliderFloat(("##Return"), &lith::module::throwpot::return_pos, 1.f, 9.f, "%.0f");

                    ImGui::Checkbox(("Drop item"), &lith::module::throwpot::throw_item);

                    ImGui::EndChild();
                }
            }
            else if (lith::gui::tab_main == 2) {
                ImGui::BeginChild(("##timer_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Timer"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::timer::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::timer::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::timer::bindpressed = true;
                        lith::module::timer::bind = "[...]";
                    }

                    ImGui::Text("Multiplier");

                    ImGui::SliderFloat(("##Multiplier"), &lith::module::timer::value, 1.f, 5.f, "%.2f");

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##bhop_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Bhop"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::bhop::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::bhop::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::bhop::bindpressed = true;
                        lith::module::bhop::bind = "[...]";
                    }

                    ImGui::Text("Multiplier");

                    ImGui::SliderFloat(("##Multiplier"), &lith::module::bhop::value, 1.f, 100.f, "%.2f");

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##fly_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Fly"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::fly::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::fly::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::fly::bindpressed = true;
                        lith::module::fly::bind = "[...]";
                    }

                    ImGui::EndChild();
                }

                ImGui::Spacing(); ImGui::SameLine(90);

                ImGui::BeginChild(("##antiafk_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("AntiAFK"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::antiafk::enabled);

                    ImGui::EndChild();
                }
            }
            else if (lith::gui::tab_main == 3) {
                ImGui::BeginChild(("##nametags_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Nametags"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::nametags::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::nametags::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::nametags::bindpressed = true;
                        lith::module::nametags::bind = "[...]";
                    }

                    ImGui::Text("Multiplier");

                    ImGui::SliderFloat(("##Multiplier"), &lith::module::nametags::value, 1.f, 3.f, "%.2f");

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##esp_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("PlayerESP"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::esp::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::esp::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::esp::bindpressed = true;
                        lith::module::esp::bind = "[...]";
                    }

                    ImGui::EndChild();
                }

                ImGui::SameLine();

                ImGui::BeginChild(("##cavefinder_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("CaveFinder"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Checkbox(("Enabled"), &lith::module::cavefinder::enabled);

                    ImGui::SameLine(); ImGui::TextDisabled(lith::module::cavefinder::bind.c_str());

                    if (ImGui::IsItemClicked()) {

                        lith::module::cavefinder::bindpressed = true;
                        lith::module::cavefinder::bind = "[...]";
                    }

                    ImGui::EndChild();
                }
            }
            else if (lith::gui::tab_main == 4) {
                ImGui::BeginChild(("##color_child"), ImVec2(200, 220), true);
                {
                    ImGui::Text(("Color"));

                    ImGui::PushItemWidth(170);

                    //ImGui::Spacing();

                    ImGui::ColorPicker4(("##colorpicker1"), (float*)&lith::gui::color1, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs);

                    ImGui::Checkbox(("Rainbow mode"), &lith::gui::rainbow_mode);

                    ImGui::EndChild();
                }
            }
            else if (lith::gui::tab_main == 5) {
                ImGui::BeginChild(("##destruct_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Destruct"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    if (ImGui::Button("Destruct", ImVec2(90, 22))) {

                        lith::module::destruct::execute();
                    }

                    ImGui::SameLine();

                    ImGui::Button(lith::module::destruct::bind.c_str(), ImVec2(90, 22));

                    if (ImGui::IsItemClicked()) {

                        lith::module::destruct::bindpressed = true;
                        lith::module::destruct::bind = "[...]";
                    }

                    ImGui::EndChild();
                }

                ImGui::Spacing(); ImGui::SameLine(90);
                
                ImGui::BeginChild(("##hide_child"), ImVec2(200, 240), true);
                {
                    ImGui::Text(("Hide"));

                    ImGui::PushItemWidth(185);

                    //ImGui::Spacing();

                    ImGui::Button(lith::module::hide::bind.c_str(), ImVec2(185, 22));

                    if (ImGui::IsItemClicked()) {

                        lith::module::hide::bindpressed = true;
                        lith::module::hide::bind = "[...]";
                    }

                    ImGui::EndChild();
                }
            }

            ImGui::End();

            if (!lith::gui::item_being_used) {

                if (!lith::gui::window_being_dragged) {

                    std::this_thread::sleep_for(std::chrono::milliseconds(5));

                }
                else {



                }

            }
            else {

                std::this_thread::sleep_for(std::chrono::milliseconds(1));

            }

            if (!lith::info::verified) {
                break;
            }

            changecolor((float*)&lith::gui::color1);
            lith::gui::item_being_used = false;
        }

        ImGui::EndFrame();
        ImGui::Render();

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(0, 0); // Present without vsync

    }
}

bool CreateDeviceD3D(HWND hWnd) {

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;

}

void CleanupDeviceD3D() {

    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }

}

void CreateRenderTarget() {

    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();

}

void CleanupRenderTarget() {

    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }

}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }

        return 0;

    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);

}


void changecolor(float col[4]) {

    if (lith::gui::rainbow_mode) {

        if (!lith::gui::window_being_dragged) {

            float add = 0.04f;

            if (lith::gui::item_being_used) {

                add = 0.003f;

            }

            static size_t turn = 0;

            if (turn == 0) {

                col[0] += add;

                if (col[0] >= 1.00f) {

                    col[0] = 1.00f;
                    turn++;

                }

            }

            if (turn == 1) {

                col[1] += add;

                if (col[1] >= 1.00f) {

                    col[1] = 1.00f;
                    turn++;

                }

            }

            if (turn == 2) {

                col[0] -= add;

                if (col[0] <= 0.00f) {

                    col[0] = 0.00f;
                    turn++;

                }

            }

            if (turn == 3) {

                col[2] += add;

                if (col[2] >= 1.00f) {

                    col[2] = 1.00f;
                    turn++;

                }

            }

            if (turn == 4) {

                col[1] -= add;

                if (col[1] <= 0.00f) {

                    col[1] = 0.00f;
                    turn++;

                }

            }

            if (turn == 5) {

                col[0] += add;

                if (col[0] >= 1.00f) {

                    col[0] = 1.00f;
                    turn++;

                }

            }

            if (turn == 6) {

                col[2] -= add;

                if (col[2] <= 0.00f) {

                    col[2] = 0.00f;
                    turn = 0;

                }

            }
        }
    }

    lith::gui::color2 = ImVec4(col[0], col[1], col[2], col[3] - 0.40f);

}
