
#include "../misc/connector.h"

static double defaultbhop = 0.3;

namespace lith {
	namespace module {
		namespace bhop {

			void enable() {

				double newbhop = defaultbhop * lith::module::bhop::value;
				double buffer;
				for (size_t x = 0; x < lith::module::bhop::locations.size(); x++) {

					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::bhop::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 30.0 && buffer >= 0.3) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::bhop::locations[x], &newbhop, sizeof(double), 0);
						}
						else {
							lith::module::bhop::locations.erase(lith::module::bhop::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::bhop::locations.erase(lith::module::bhop::locations.begin() + x);
						x = 0;
					}
				}

			}

			void disable() {
				double buffer;
				for (size_t x = 0; x < lith::module::bhop::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::bhop::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 30.0 && buffer >= 0.3) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::bhop::locations[x], &defaultbhop, sizeof(double), 0);
						}
						else {
							lith::module::bhop::locations.erase(lith::module::bhop::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::bhop::locations.erase(lith::module::bhop::locations.begin() + x);
						x = 0;
					}
				}
			}

			void thread() {
				for (;;) {

					if (lith::module::bhop::enabled) {
						lith::module::bhop::used = true;
						enable();
					}
					else {
						if (lith::module::bhop::used) {
							disable();
							lith::module::bhop::used = false;
						}

					}

					if (lith::module::bhop::enabled) {
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