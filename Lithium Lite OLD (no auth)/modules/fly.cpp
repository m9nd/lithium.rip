
#include "../misc/connector.h"

namespace lith {
	namespace module {
		namespace fly {

			void enablef(double value) {
				double buffer;
				for (size_t x = 0; x < lith::module::fly::locationsfly.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::fly::locationsfly[x], &buffer, sizeof(double), 0)) {
						if (buffer == 0.9800000190734863 || buffer == 0.08) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::fly::locationsfly[x], &value, sizeof(double), 0);
						}
						else {
							lith::module::fly::locationsfly.erase(lith::module::fly::locationsfly.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::fly::locationsfly.erase(lith::module::fly::locationsfly.begin() + x);
						x = 0;
					}
				}

			}

			void disable() {
				enablef(0.9800000190734863);
			}

			void thread() {
				
				for (;;) {

					if (lith::module::fly::enabled) {
						lith::module::fly::used = true;
						enablef(0.08);

					}
					else {

						if (lith::module::fly::used) {

							disable();
							lith::module::fly::used = false;

						}

					}

					if (lith::module::fly::enabled) {
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