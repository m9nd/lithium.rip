
#include "connector.h"

namespace lith {

	namespace info {

		bool verified = true;
		const char* version = "1.5.2";
		DWORD pid = 0;
		HANDLE handle;
		std::string hwid;
		int stage = 0;
	}

	namespace launch {

		void all_threads() {

			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::gui::move_window, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::scanner::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::status::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::binds::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::clicker::left::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::clicker::left::jitter::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::clicker::right::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::reach::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::throwpot::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::fly::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::nametags::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::esp::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::cavefinder::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::timer::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::bhop::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::antiafk::thread, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&lith::module::velocity::thread, nullptr, 0, 0);
		}

	}

	namespace gui {

		HWND hwnd;
		bool rainbow_mode = false;
		bool window_being_dragged = false;
		bool item_being_used = false;
		size_t tab_main = 1;

	}

	namespace localplayer {

		bool moving = false;
		bool sprinting = false;
		bool jumping = false;
		bool inventoryopen = false;
		size_t current_slot = 1;

		namespace binds {

			size_t slot1 = 0x31;
			size_t slot2 = 0x32;
			size_t slot3 = 0x33;
			size_t slot4 = 0x34;
			size_t slot5 = 0x35;
			size_t slot6 = 0x36;
			size_t slot7 = 0x37;
			size_t slot8 = 0x38;
			size_t slot9 = 0x39;

			size_t w = 'w';
			size_t a = 'a';
			size_t s = 's';
			size_t d = 'd';

			size_t jump = VK_SPACE;
			size_t sprint = VK_LCONTROL;

			size_t inventory = 'e';

			size_t drop = 'q';

		}

	}

	namespace module {

		namespace clicker {

			namespace left {

				bool enabled = false;
				float value = 5;
				float value2 = 500;
				float valuex = 0;
				float valuey = 0;
				bool inventory = false;
				bool blockhit = false;
				bool rmb_lock = true;
				bool slot[9] = { true, true, true, true, true, true, true, true, true };
				std::string bind = "[NONE]";
				bool bindpressed = false;
				size_t selectedbind = 0;

			}

			namespace right {

				bool enabled = false;
				float value = 5;
				bool slot[9] = { true, true, true, true, true, true, true, true, true };
				std::string bind = "[NONE]";
				bool bindpressed = false;
				size_t selectedbind = 0;

			}

		}

		namespace velocity {

			std::vector<size_t>locations;
			bool enabled = false;
			float minvalue = 100;
			float maxvalue = 100;
			bool onlysprinting = true;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace reach {

			std::vector<size_t>unlimit;
			std::vector<size_t>floats;
			std::vector<size_t>doubles;
			bool enabled = false;
			float minvalue = 3;
			float maxvalue = 3;
			bool onlysprinting = false;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace throwpot {

			bool enabled = false;
			bool throw_item = false;
			float return_pos = 1;
			float value = 100.0f;
			bool slot[9] = { false, false, false, true, true, true, true, true, true };
			std::string bind = "[NONE]";
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace fly {

			std::vector<size_t>locationsfly;
			bool enabled = false;
			bool waiting = false;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace nametags {

			std::vector<size_t>locations1;
			std::vector<size_t>locations2;
			std::vector<size_t>locations3;
			bool enabled = false;
			float value = 1;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace esp {

			std::vector<size_t>locations;
			bool enabled = false;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace cavefinder {

			std::vector<size_t>locations;
			bool enabled = false;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace timer {

			std::vector<size_t>locations;
			bool enabled = false;
			float value = 1;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace bhop {

			std::vector<size_t>locations;
			bool enabled = false;
			float value = 1;
			std::string bind = "[NONE]";
			bool used = false;
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace antiafk {

			bool enabled = false;

		}

		namespace destruct {

			std::string bind = "[NONE]";
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

		namespace hide {

			bool enabled = false;
			std::string bind = "[NONE]";
			bool bindpressed = false;
			size_t selectedbind = 0;

		}

	}

}