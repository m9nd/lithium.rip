
#include "../misc/connector.h"

static double defaultvelocity = 8000.0;

namespace lith {
	namespace module {
		namespace velocity {

			void enable() {

				double newvelocity = 800000.0 / (double)lith::tools::getrandomfloat(lith::module::velocity::minvalue, lith::module::velocity::maxvalue);
				double buffer;
				for (size_t x = 0; x < lith::module::velocity::locations.size(); x++) {

					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::velocity::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 800000.0 && buffer >= 8000.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::velocity::locations[x], &newvelocity, sizeof(double), 0);
						}
						else {
							lith::module::velocity::locations.erase(lith::module::velocity::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::velocity::locations.erase(lith::module::velocity::locations.begin() + x);
						x = 0;
					}
				}

			}

			void disable() {
				double buffer;
				for (size_t x = 0; x < lith::module::velocity::locations.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::velocity::locations[x], &buffer, sizeof(double), 0)) {
						if (buffer <= 800000.0 && buffer >= 8000.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::velocity::locations[x], &defaultvelocity, sizeof(double), 0);
						}
						else {
							lith::module::velocity::locations.erase(lith::module::velocity::locations.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::velocity::locations.erase(lith::module::velocity::locations.begin() + x);
						x = 0;
					}
				}
			}

			void thread() {
				for (;;) {

					if (!lith::info::verified) {//integrity
						break;
					}
					if (lith::module::velocity::enabled) {
						lith::module::velocity::used = true;
						enable();
					}
					else {
						if (lith::module::velocity::used) {
							disable();
							lith::module::velocity::used = false;
						}

					}

					if (lith::module::velocity::enabled) {
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