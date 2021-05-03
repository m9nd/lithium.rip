
#include "../misc/connector.h"

static float defaultnametags1 = 0.02666667f;
static float defaultnametags2 = -0.02666667f;

namespace lith {
	namespace module {
		namespace nametags {

			void enable() {
				float newnametags1 = defaultnametags1 * lith::module::nametags::value;
				float newnametags2 = -(defaultnametags1 * lith::module::nametags::value);
				float buffer;
				for (size_t x = 0; x < lith::module::nametags::locations1.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations1[x], &buffer, sizeof(float), 0)) {
						if (buffer <= 0.09f && buffer >= 0.02666667f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations1[x], &newnametags1, sizeof(float), 0);
						}
						else {
							lith::module::nametags::locations1.erase(lith::module::nametags::locations1.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::nametags::locations1.erase(lith::module::nametags::locations1.begin() + x);
						x = 0;
					}
				}

				for (size_t x = 0; x < lith::module::nametags::locations2.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations2[x], &buffer, sizeof(float), 0)) {
						if (buffer <= -0.02666667f && buffer >= -0.09f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations2[x], &newnametags2, sizeof(float), 0);
						}
						else {
							lith::module::nametags::locations2.erase(lith::module::nametags::locations2.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::nametags::locations2.erase(lith::module::nametags::locations2.begin() + x);
						x = 0;
					}
				}

			}

			void disable() {
				float buffer;
				for (size_t x = 0; x < lith::module::nametags::locations1.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations1[x], &buffer, sizeof(float), 0)) {
						if (buffer <= 0.09f && buffer >= 0.02666667f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations1[x], &defaultnametags1, sizeof(float), 0);
						}
						else {
							lith::module::nametags::locations1.erase(lith::module::nametags::locations1.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::nametags::locations1.erase(lith::module::nametags::locations1.begin() + x);
						x = 0;
					}
				}

				for (size_t x = 0; x < lith::module::nametags::locations2.size(); x++) {
					if (ReadProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations2[x], &buffer, sizeof(float), 0)) {
						if (buffer <= -0.02666667f && buffer >= -0.09f) {
							WriteProcessMemory(lith::info::handle, (LPVOID)lith::module::nametags::locations2[x], &defaultnametags2, sizeof(float), 0);
						}
						else {
							lith::module::nametags::locations2.erase(lith::module::nametags::locations2.begin() + x);
							x = 0;
						}
					}
					else {
						lith::module::nametags::locations2.erase(lith::module::nametags::locations2.begin() + x);
						x = 0;
					}
				}
			}

			void thread() {
				for (;;) {

					if (lith::module::nametags::enabled) {
						lith::module::nametags::used = true;
						enable();
					}
					else {
						if (lith::module::nametags::used) {
							disable();
							lith::module::nametags::used = false;
						}

					}

					if (lith::module::nametags::enabled) {
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