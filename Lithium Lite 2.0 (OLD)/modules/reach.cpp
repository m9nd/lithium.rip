
#include "../misc/connector.h"

static float defaultreachf = 3.0f;
static double defaultreachd = 3.0;
static double defaultreachl = 4.5;
static double newreachl = 7.5;

namespace lith {
	namespace module {
		namespace reach {

			void enable() {
				float newreachf = lith::tools::getrandomfloat(lith::module::reach::minvalue, lith::module::reach::maxvalue);
				double newreachd = newreachf;

				float bufferf;
				double bufferd;

				if (lith::module::reach::maxvalue >= 4.25f) {
					for (size_t x = 0; x < lith::module::reach::unlimit.size(); x++) {
						if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &bufferd, sizeof(double), 0)) {
							if (bufferd <= 7.5 && bufferd >= 4.5) {
								WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &newreachl, sizeof(double), 0);
							}
							else {
								lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
								x = 0;
							}
						}
						else {
							lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
							x = 0;
						}
					}
				}
				else {
					for (size_t x = 0; x < lith::module::reach::unlimit.size(); x++) {
						if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &bufferd, sizeof(double), 0)) {
							if (bufferd <= 7.5 && bufferd >= 4.5) {
								WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &defaultreachl, sizeof(double), 0);
							}
							else {
								lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
								x = 0;
							}
						}
						else {
							lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
							x = 0;
						}
					}
				}

				for (size_t x = 0; x < lith::module::reach::doubles.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::doubles[x], &bufferd, sizeof(double), 0)) {
						if (bufferd <= 6.0 && bufferd >= 3.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::doubles[x], &newreachd, sizeof(double), 0);
						}
						else {
							lith::module::reach::doubles.erase(lith::module::reach::doubles.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::reach::doubles.erase(lith::module::reach::doubles.begin() + x);
						x = 0;
					}
				}

				for (size_t x = 0; x < lith::module::reach::floats.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)(lith::module::reach::floats[x]), &bufferf, sizeof(float), 0)) {
						if (bufferf <= 6.0f && bufferf >= 3.0f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::floats[x], &newreachf, sizeof(float), 0);
						}
						else {
							lith::module::reach::floats.erase(lith::module::reach::floats.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::reach::floats.erase(lith::module::reach::floats.begin() + x);
						x = 0;
					}
				}

			}
			void disable() {

				float bufferf;
				double bufferd;

				for (size_t x = 0; x < lith::module::reach::unlimit.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &bufferd, sizeof(double), 0)) {
						if (bufferd <= 7.5 && bufferd >= 4.5) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::unlimit[x], &defaultreachl, sizeof(double), 0);
						}
						else {
							lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::reach::unlimit.erase(lith::module::reach::unlimit.begin() + x);
						x = 0;
					}
				}

				for (size_t x = 0; x < lith::module::reach::doubles.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::doubles[x], &bufferd, sizeof(double), 0)) {
						if (bufferd <= 6.0 && bufferd >= 3.0) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::doubles[x], &defaultreachd, sizeof(double), 0);
						}
						else {
							lith::module::reach::doubles.erase(lith::module::reach::doubles.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::reach::doubles.erase(lith::module::reach::doubles.begin() + x);
						x = 0;
					}
				}

				for (size_t x = 0; x < lith::module::reach::floats.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::floats[x], &bufferf, sizeof(float), 0)) {
						if (bufferf <= 6.0f && bufferf >= 3.0f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::reach::floats[x], &defaultreachf, sizeof(float), 0);
						}
						else {
							lith::module::reach::floats.erase(lith::module::reach::floats.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::reach::floats.erase(lith::module::reach::floats.begin() + x);
						x = 0;
					}
				}

			}

			void thread() {
				for (;;) {

					if (lith::module::reach::enabled) {
						lith::module::reach::used = true;
						if (lith::module::reach::onlysprinting) {
							if (lith::localplayer::sprinting) {
								enable();
							}
							else {
								disable();
							}
						}
						else {
							enable();
						}
					}
					else {
						if (lith::module::reach::used) {
							disable();
							lith::module::reach::used = false;
						}

					}

					if (lith::module::reach::enabled) {
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