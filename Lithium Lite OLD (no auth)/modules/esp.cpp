
#include "../misc/connector.h"

static float defaultesp = 2.5f;
static float newesp = 3.3699999f;

namespace lith {
	namespace module {
		namespace esp {

			void enable() {
				float buffer;
				for (size_t x = 0; x < lith::module::esp::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::esp::locations[x], &buffer, sizeof(float), 0)) {
						if (buffer >= 2.5f && buffer <= 3.3699999f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::esp::locations[x], &newesp, sizeof(float), 0);
						}
						else {
							lith::module::esp::locations.erase(lith::module::esp::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::esp::locations.erase(lith::module::esp::locations.begin() + x);
						x = 0;
					}
				}


			}

			void disable() {
				float buffer;
				for (size_t x = 0; x < lith::module::esp::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::esp::locations[x], &buffer, sizeof(float), 0)) {
						if (buffer >= 2.5f && buffer <= 3.3699999f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::esp::locations[x], &defaultesp, sizeof(float), 0);
						}
						else {
							lith::module::esp::locations.erase(lith::module::esp::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::esp::locations.erase(lith::module::esp::locations.begin() + x);
						x = 0;
					}
				}

			}

			void thread() {
				for (;;) {

					if (lith::module::esp::enabled) {
						lith::module::esp::used = true;
						enable();
					}
					else {
						if (lith::module::esp::used) {
							disable();
							lith::module::esp::used = false;
						}

					}

					if (lith::module::esp::enabled) {
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
					}
					else {
						std::this_thread::sleep_for(std::chrono::milliseconds(50));
					}

				}

			}

		}
	}
}