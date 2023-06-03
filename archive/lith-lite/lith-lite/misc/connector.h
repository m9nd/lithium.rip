

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "../imgui/imgui.h"
#include "../fonts/roboto.h"
#include "../fonts/fa.h"

#include <TlHelp32.h>
#include <algorithm>
#include <iostream>
#include <dinput.h>
#include <tchar.h>
#include <vector>
#include <thread>
#include <random>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#include <winternl.h>
#include <Softpub.h>
#include <Psapi.h>
#include <shellapi.h>
#include <codecvt>
#include <WinBase.h>
#include <WbemCli.h>
#include <comdef.h>

#include "../misc/xor.h"
#include "../misc/json.h"

#include "../misc/crypto/md5.h"
#include "../misc/crypto/sha256.h"
#include "../misc/crypto/sha512.h"

using json = nlohmann::json;

#include <ThemidaSDK.h>

#define Background_Window_Flags ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus
#define Window_Flags ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus
#define Window_Flags_Title ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings

namespace lith {

	namespace auth {

		int authenticate(std::string hwid, std::string token);
		std::vector<char>* getreq(std::string* params, int extra = 0);

		enum {

			authenticating = 52635,
			authenticated = 23017,
			not_authorized = 53965,
			outdated = 32288,
			banned = 97902,
			error = 69442,
			inited = 78517
		};
	}

	namespace info {

		extern std::string hwid;
		extern bool verified;
		extern const char* version;
		extern DWORD pid;
		extern HANDLE handle;
		extern int stage;
	}

	namespace launch {

		extern void all_threads();

	}

	namespace gui {

		extern HWND hwnd;
		extern ImVec4 color1;
		extern ImVec4 color2;
		extern ImVec4 color3;
		extern bool rainbow_mode;
		extern bool window_being_dragged;
		extern bool item_being_used;
		extern size_t tab_main;
		extern void move_window();

	}

	namespace status {

		extern void thread();

	}

	namespace scanner {

		extern void thread();

	}

	namespace localplayer {

		extern bool moving;
		extern bool sprinting;
		extern bool jumping;
		extern bool inventoryopen;
		extern size_t current_slot;

		namespace binds {

			extern size_t slot1;
			extern size_t slot2;
			extern size_t slot3;
			extern size_t slot4;
			extern size_t slot5;
			extern size_t slot6;
			extern size_t slot7;
			extern size_t slot8;
			extern size_t slot9;

			extern size_t w;
			extern size_t a;
			extern size_t s;
			extern size_t d;

			extern size_t jump;
			extern size_t sprint;
			extern 	size_t drop;
			extern size_t inventory;
		}
	}

	namespace binds {

		void thread();

	}

	namespace module {

		namespace clicker {

			namespace left {

				namespace jitter {

					extern void thread();

				}

				extern void thread();
				extern bool enabled;
				extern float value;
				extern float value2;
				extern float valuex;
				extern float valuey;
				extern bool inventory;
				extern bool blockhit;
				extern bool rmb_lock;
				extern bool slot[9];
				extern std::string bind;
				extern bool bindpressed;
				extern size_t selectedbind;

			}

			namespace right {

				extern void thread();
				extern bool enabled;
				extern float value;
				extern bool slot[9];
				extern std::string bind;
				extern bool bindpressed;
				extern size_t selectedbind;

			}

		}

		namespace reach {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>unlimit;
			extern std::vector<size_t>floats;
			extern std::vector<size_t>doubles;
			extern bool enabled;
			extern float minvalue;
			extern float maxvalue;
			extern bool onlysprinting;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace throwpot {

			extern void thread();
			extern bool enabled;
			extern bool throw_item;
			extern float return_pos;
			extern float value;
			extern bool slot[9];
			extern std::string bind;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace fly {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locationsfly;
			extern bool enabled;
			extern bool waiting;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace nametags {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations1;
			extern std::vector<size_t>locations2;
			extern std::vector<size_t>locations3;
			extern bool enabled;
			extern float value;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace esp {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations;
			extern bool enabled;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace cavefinder {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations;
			extern bool enabled;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace timer {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations;
			extern bool enabled;
			extern float value;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace velocity {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations;
			extern bool enabled;
			extern float minvalue;
			extern float maxvalue;
			extern bool onlysprinting;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace bhop {

			extern void thread();
			extern void disable();
			extern std::vector<size_t>locations;
			extern bool enabled;
			extern float value;
			extern std::string bind;
			extern bool used;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace antiafk {

			extern void thread();
			extern bool enabled;

		}

		namespace destruct {

			extern void execute();
			extern std::string bind;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

		namespace hide {

			extern bool enabled;
			extern std::string bind;
			extern bool bindpressed;
			extern size_t selectedbind;

		}

	}

	namespace tools {

		extern DWORD getprocessid(std::string processname);
		extern DWORD getserviceid(const char* serviceName);
		extern DWORD isminecraftrunning();
		extern bool createhandletoprocess(DWORD pid);
		extern float getrandomfloat(float min, float max);
		extern void suspendprocess(DWORD pid);
		extern void resumeprocess(DWORD pid);
		extern void terminateprocess(DWORD pid);

	}

}