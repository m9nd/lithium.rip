#include "main.h"

namespace v {
	namespace modules {
		namespace antiafk {
			void thread() {
				while (::info::verified) {
					if (GetForegroundWindow() == ::info::minecraft_window) {

						if (::modules::antiafk::enabled) {

							if (::local_player::inventory_open) {

								keybd_event(VK_ESCAPE, 0, 0, 0);
								std::this_thread::sleep_for(std::chrono::milliseconds(100));
								keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);

								keybd_event(::local_player::binds::jump, 0, 0, 0);

								std::this_thread::sleep_for(std::chrono::milliseconds(100));

								keybd_event(::local_player::binds::jump, 0, KEYEVENTF_KEYUP, 0);

							}
							else {

								keybd_event(::local_player::binds::jump, 0, 0, 0);

								std::this_thread::sleep_for(std::chrono::milliseconds(100));

								keybd_event(::local_player::binds::jump, 0, KEYEVENTF_KEYUP, 0);

							}

						}

						std::this_thread::sleep_for(std::chrono::seconds(5));

					}
					else {

						if (::modules::antiafk::enabled) {
							SetForegroundWindow(FindWindow(("LWJGL"), nullptr));
						}

					}

					std::this_thread::sleep_for(std::chrono::milliseconds(100));

				}

			}

		}
	}
}