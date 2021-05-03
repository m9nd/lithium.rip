
#include "../misc/connector.h"

static double defaulttimer = 1000.0;

namespace lith {
	namespace module {
		namespace timer {

			void enable() {

				double newtimer = defaulttimer/lith::module::timer::value;
				double buffer;
				for (size_t x = 0; x < lith::module::timer::locations.size(); x++) {

					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::timer::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 1000.0 && buffer >= 200.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::timer::locations[x], &newtimer, sizeof(double), 0);
						}
						else {
							lith::module::timer::locations.erase(lith::module::timer::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::timer::locations.erase(lith::module::timer::locations.begin() + x);
						x = 0;
					}
				}

			}

			void disable() {
				double buffer;
				for (size_t x = 0; x < lith::module::timer::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::timer::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 1000.0 && buffer >= 200.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::timer::locations[x], &defaulttimer, sizeof(double), 0);
						}
						else {
							lith::module::timer::locations.erase(lith::module::timer::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::timer::locations.erase(lith::module::timer::locations.begin() + x);
						x = 0;
					}
				}
			}

			void thread() {
				for (;;) {

					if (lith::module::timer::enabled) {
						lith::module::timer::used = true;
						enable();
					}
					else {
						if (lith::module::timer::used) {
							disable();
							lith::module::timer::used = false;
						}

					}

					if (lith::module::timer::enabled) {
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