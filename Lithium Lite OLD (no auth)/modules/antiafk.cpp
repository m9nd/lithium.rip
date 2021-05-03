
#include "../misc/connector.h"

namespace lith {
	namespace module {
		namespace antiafk {

			void thread() {

				for (;;) {

					if (!lith::info::verified) {//integrity
						break;
					}
					if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {

						if (lith::module::antiafk::enabled) {

							if (lith::localplayer::inventoryopen) {

								keybd_event(VK_ESCAPE, 0, 0, 0);
								std::this_thread::sleep_for(std::chrono::milliseconds(100));
								keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);

								keybd_event(lith::localplayer::binds::jump, 0, 0, 0);

								std::this_thread::sleep_for(std::chrono::milliseconds(100));

								keybd_event(lith::localplayer::binds::jump, 0, KEYEVENTF_KEYUP, 0);

							}
							else {

								keybd_event(lith::localplayer::binds::jump, 0, 0, 0);

								std::this_thread::sleep_for(std::chrono::milliseconds(100));

								keybd_event(lith::localplayer::binds::jump, 0, KEYEVENTF_KEYUP, 0);

							}

						}
					
						std::this_thread::sleep_for(std::chrono::seconds(5));
					
					}
					else {

						if (lith::module::antiafk::enabled) {
							SetForegroundWindow(FindWindow(("LWJGL"), nullptr));
						}

					}

					std::this_thread::sleep_for(std::chrono::milliseconds(100));

				}

			}

		}
	}
}