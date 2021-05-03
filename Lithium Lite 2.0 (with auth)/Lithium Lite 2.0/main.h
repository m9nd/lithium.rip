#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>

#define DIRECTINPUT_VERSION 0x0800

#include "fa.h"
#include "roboto.h"

#include "md5.h"
#include "sha512.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")


static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include "xorstr.h"
#include "ntdll.h"

namespace info {
     DWORD minecraft_pid;
     HANDLE minecraft_handle;
     HWND minecraft_window;
     bool verified = true;
     std::string version = ("0.1");
     std::string hwid;
}

namespace launch {
    extern void all_threads();
}

namespace status {
    extern void thread();
}

namespace binds {
    extern void thread();
}

namespace gui {
     HWND hwnd;
     ImVec4 color1 = ImColor(0.9f, 0.24f, 0.24f);
     ImVec4 color2 = ImVec4(0.56f, 0.00f, 1.00f, 0.50f);
     ImVec4 color3 = ImVec4(1.00f, 1.00f, 1.00f, 0.15f);
     bool rainbow_mode = false;
     bool window_being_dragged = false;
     bool item_being_used = false;
     int tab_main = 1;
     char lithgui = 'A';
     bool memeversion = false;
    extern void move_window();
}

namespace local_player {
     bool moving = false;
     bool sprinting = false;
     bool jumping = false;
     bool inventory_open = false;
     int current_slot = 1;

    namespace binds {
         int slot1 = 0x31;
         int slot2 = 0x32;
         int slot3 = 0x33;
         int slot4 = 0x34;
         int slot5 = 0x35;
         int slot6 = 0x36;
         int slot7 = 0x37;
         int slot8 = 0x38;
         int slot9 = 0x39;

         int w = 'w';
         int a = 'a';
         int s = 's';
         int d = 'd';

         int jump = VK_SPACE;
         int sprint = VK_LCONTROL;
         int drop = 'q';
         int inventory = 'e';
    }
}

namespace scanner {
    extern void thread();
}

namespace modules {
    namespace clicker {
        namespace left {
            namespace jitter {
                extern void thread();
            }

            extern void thread();

             bool enabled = false;
             float cps = 12.f;
             float blockhit_delay;
             float x_jitter;
             float y_jitter;
             bool inventory = false;
             bool blockhit = false;
             bool rmb_lock = true;
             bool slot[9] = { true, true, true, true, true, true, true, true, true };
             std::string bind = xorstr("[NONE]");
             bool bind_pressed = false;
             size_t selected_bind = 0;
        }

        namespace right {
            extern void thread();

             bool enabled;
             float cps = 12.f;
             bool slot[9] = { true, true, true, true, true, true, true, true, true };
             std::string bind = xorstr("[NONE]");
             bool bind_pressed;
             size_t selected_bind;
        }
    }

    namespace reach {
        extern void thread();

        extern void disable();

         std::vector<size_t> unlimit;
         std::vector<size_t> floats;
         std::vector<size_t> doubles;
         bool enabled;
         float minvalue;
         float maxvalue;
         bool while_moving = true;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace throwpot {
        extern void thread();

         bool enabled;
         bool throw_item;
         float return_pos;
         float throw_delay;
         bool slot[9];
         std::string bind = xorstr("[NONE]");
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace fly {
        extern void thread();

        extern void disable();

         std::vector<size_t> locationsfly;
         bool enabled;
         bool waiting;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace nametags {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations1;
         std::vector<size_t> locations2;
         bool enabled;
         float multiplier = 1.f;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace esp {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace cavefinder {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace timer {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         float multiplier = 1.f;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace speed {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         float multiplier = 1.f;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace velocity {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         float min;
         float max;
         bool while_moving = true;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace bhop {
        extern void thread();

        extern void disable();

         std::vector<size_t> locations;
         bool enabled;
         float speed = 1.f;
         std::string bind = xorstr("[NONE]");
         bool used;
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace antiafk {
        extern void thread();

         bool enabled;
    }

    namespace destruct {
        extern void execute();

         bool pcaclean = false;
         bool traceless = true;

         std::string bind = xorstr("[NONE]");
         bool bind_pressed;
         size_t selected_bind;
    }

    namespace hide {
         bool enabled;
         std::string bind = xorstr("[NONE]");
         bool bind_pressed;
         size_t selected_bind;
    }
}
namespace utils {
     int random_int(int min, int max) {
        static auto device = std::random_device();
        static auto engine = std::mt19937(device());
        const auto gen = std::uniform_int_distribution<int>(min, max);
        return gen(engine);
    }

     float random_float(float min, float max) {
        static auto device = std::random_device();
        static auto engine = std::mt19937(device());
        const auto gen = std::uniform_real_distribution<float>(min, max);
        return gen(engine);
    }

     DWORD get_pid(const std::string& process_name) {
        PROCESSENTRY32 process_info;
        process_info.dwSize = sizeof(process_info);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (snapshot == INVALID_HANDLE_VALUE)
            return 0;

        Process32First(snapshot, &process_info);
        if (!process_name.compare(process_info.szExeFile)) {
            CloseHandle(snapshot);
            return process_info.th32ProcessID;
        }

        while (Process32Next(snapshot, &process_info)) {
            if (!process_name.compare(process_info.szExeFile)) {
                CloseHandle(snapshot);
                return process_info.th32ProcessID;
            }
        }

        CloseHandle(snapshot);

        return 0;
    }

     DWORD get_service_pid(const std::string& service_name) {
        SC_HANDLE scm = OpenSCManager(nullptr, nullptr, NULL);
        SC_HANDLE sc = OpenService(scm, service_name.c_str(), SERVICE_QUERY_STATUS);

        SERVICE_STATUS_PROCESS ssp = { 0 };
        DWORD bytes_needed = 0;
        QueryServiceStatusEx(sc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp),
            &bytes_needed);

        CloseServiceHandle(sc);
        CloseServiceHandle(scm);

        return ssp.dwProcessId;
    }
     void suspend_process(DWORD pid) {
        if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
            BOOL result = SuspendThread(hProcess);
            CloseHandle(hProcess);
        }
    }

     void resume_process(DWORD pid) {
        if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
            BOOL result = ResumeThread(hProcess);
            CloseHandle(hProcess);
        }
    }

     void terminate_process(DWORD pid) {
        if (HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pid)) {
            BOOL result = TerminateProcess(hProcess, 1);
            CloseHandle(hProcess);
        }
    }

     std::string get_hwid() {
        std::string drive_name = (std::string)getenv(xorstr("SystemDrive"));
        drive_name.append(xorstr("\\"));

        DWORD drive_serial = 0;
        GetVolumeInformationA(drive_name.c_str(), nullptr, NULL, &drive_serial,
            nullptr, nullptr, nullptr, NULL);

        std::ostringstream o;
        o << std::hex << HIWORD(drive_serial) << LOWORD(drive_serial);
        return o.str();
    }

     std::string random_string(std::size_t size) {

        const std::string chars = xorstr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, chars.size() - 1);

        std::string random_string;

        for (std::size_t i = 0; i < size; ++i)
            random_string += chars[distribution(generator)];

        return random_string;
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
}