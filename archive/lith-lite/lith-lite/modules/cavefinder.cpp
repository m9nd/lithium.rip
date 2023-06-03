
#include "../misc/connector.h"

static double defaultcavefinder = 16;
static double newcavefinder = 1879048192;

namespace lith {
	namespace module {
		namespace cavefinder {

			void enable() {
				double buffer;
				for (size_t x = 0; x < lith::module::cavefinder::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::cavefinder::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer >= 16 && buffer <= 1879048192) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::cavefinder::locations[x], &newcavefinder, sizeof(double), 0);
						}
						else {
							lith::module::cavefinder::locations.erase(lith::module::cavefinder::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::cavefinder::locations.erase(lith::module::cavefinder::locations.begin() + x);
						x = 0;
					}
				}


			}

			void disable() {
				double buffer;
				for (size_t x = 0; x < lith::module::cavefinder::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::cavefinder::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer >= 16 && buffer <= 1879048192) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::cavefinder::locations[x], &defaultcavefinder, sizeof(double), 0);
						}
						else {
							lith::module::cavefinder::locations.erase(lith::module::cavefinder::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::cavefinder::locations.erase(lith::module::cavefinder::locations.begin() + x);
						x = 0;
					}
				}

			}

			void thread() {
				for (;;) {

					if (lith::module::cavefinder::enabled) {
						lith::module::cavefinder::used = true;
						enable();
					}
					else {
						if (lith::module::cavefinder::used) {
							disable();
							lith::module::cavefinder::used = false;
						}

					}

					if (lith::module::cavefinder::enabled) {
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