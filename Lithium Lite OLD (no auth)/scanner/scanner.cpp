
#include "../misc/connector.h"

template <class val>
std::vector<size_t>get_positions(std::vector<val>buffer, val value, size_t timesfound) {

	std::vector<size_t> positions;
	size_t pos = std::distance(buffer.begin(), find(buffer.begin(), buffer.end(), value));
	size_t lastpos = pos;

	while (pos < buffer.size()) {

		if (positions.size() >= timesfound) { break; }
		positions.push_back(pos);
		size_t calc = pos + 1;
		pos = std::distance(buffer.begin(), find(buffer.begin() + calc, buffer.end(), value));
		if (pos == lastpos) { break; }

	}

	return positions;

}

namespace lith {

	namespace scanner {

		size_t minaddress = 0x02000000;
		size_t maxaddress = 0x08000000;

		void calculator() {

			for (;;) {

				if (!lith::info::verified) {//integrity
					break;
				}
				bool found = false;

				size_t address = 0x2000000;

				MEMORY_BASIC_INFORMATION memory;

				while (VirtualQueryEx(lith::info::handle, (LPVOID)address, &memory, sizeof(MEMORY_BASIC_INFORMATION))) {

					if (memory.State == MEM_COMMIT && (
						(memory.Protect == PAGE_EXECUTE_READWRITE) |
						(memory.Protect == PAGE_READWRITE) |
						(memory.Protect == PAGE_EXECUTE_WRITECOPY) |
						(memory.Protect == PAGE_WRITECOPY))) {

						if (!found) {
							minaddress = address;
							found = !found;
						}

					}

					if (address + memory.RegionSize >= 0x10000000) {
						break;
					}

					else {
						address += memory.RegionSize;
					}

				}

				maxaddress = address;
				std::this_thread::sleep_for(std::chrono::seconds(10));

			}

		}

		void selfprotect() {

			for (;;) {

				DWORD status; if (GetExitCodeProcess(lith::info::handle, &status)) {
					if (status != STILL_ACTIVE) { exit(EXIT_SUCCESS); }
				}

				/*
				char buffer[255];
				GetWindowText(GetForegroundWindow(), buffer, 255);
				if (strstr(buffer, "Cheat Engine")) {
					exit(EXIT_SUCCESS);
				}

				if (lith::tools::getprocessid("cheatengine-x86_64.exe")) {
					exit(EXIT_SUCCESS);
				}

				if (lith::tools::getprocessid("cheatengine-i386.exe")) {
					exit(EXIT_SUCCESS);
				}
				*/

				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}

		}

		void thread() {
			
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&calculator, nullptr, 0, 0);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&selfprotect, nullptr, 0, 0);
			
			for (;;) {

				if (lith::info::verified) {

					for (size_t address = minaddress; address <= maxaddress; address += 4096) {

						std::vector<double>memoryd(4096);
						std::vector<float>memoryf(4096);

						bool doubleread = ReadProcessMemory(lith::info::handle, (LPVOID)address, &memoryd[0], 4096, 0);

						bool floatread;  if (doubleread) {
	
							floatread = ReadProcessMemory(lith::info::handle, (LPVOID)address, &memoryf[0], 4096, 0);

						}

						if (doubleread && floatread) {

							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 4.5)) {

								for (const size_t location : get_positions(memoryd, 4.5, x)) {

									lith::module::reach::unlimit.push_back(address + location * sizeof(double));

									sort(lith::module::reach::unlimit.begin(), lith::module::reach::unlimit.end());
									lith::module::reach::unlimit.erase(unique(lith::module::reach::unlimit.begin(), lith::module::reach::unlimit.end()), lith::module::reach::unlimit.end());

								}


								if (size_t d = std::count(memoryd.begin(), memoryd.end(), 3.0)) {

									for (const size_t location : get_positions(memoryd, 3.0, d)) {

										lith::module::reach::doubles.push_back(address + location * sizeof(double));

										sort(lith::module::reach::doubles.begin(), lith::module::reach::doubles.end());
										lith::module::reach::doubles.erase(unique(lith::module::reach::doubles.begin(), lith::module::reach::doubles.end()), lith::module::reach::doubles.end());

									}

								}

								if (size_t f = std::count(memoryf.begin(), memoryf.end(), 3.0f)) {

									for (const size_t location : get_positions(memoryf, 3.0f, f)) {

										lith::module::reach::floats.push_back(address + location * sizeof(float));

										sort(lith::module::reach::floats.begin(), lith::module::reach::floats.end());
										lith::module::reach::floats.erase(unique(lith::module::reach::floats.begin(), lith::module::reach::floats.end()), lith::module::reach::floats.end());

									}

								}

							}

							if (address > 0x03000000) {

								if (size_t x = std::count(memoryf.begin(), memoryf.end(), 2.5f)) {

									for (const size_t location : get_positions(memoryf, 2.5f, x)) {

										lith::module::esp::locations.push_back(address + location * sizeof(float));
										sort(lith::module::esp::locations.begin(), lith::module::esp::locations.end());
										lith::module::esp::locations.erase(unique(lith::module::esp::locations.begin(), lith::module::esp::locations.end()), lith::module::esp::locations.end());

									}
								}
							}

							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 16.0)) {

								for (const size_t location : get_positions(memoryd, 16.0, x)) {

									lith::module::cavefinder::locations.push_back(address + location * sizeof(double));
									sort(lith::module::cavefinder::locations.begin(), lith::module::cavefinder::locations.end());
									lith::module::cavefinder::locations.erase(unique(lith::module::cavefinder::locations.begin(), lith::module::cavefinder::locations.end()), lith::module::cavefinder::locations.end());

								}
							}
			
							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 8000.0)) {

								for (const size_t location : get_positions(memoryd, 8000.0, x)) {

									lith::module::velocity::locations.push_back(address + location * sizeof(double));
									sort(lith::module::velocity::locations.begin(), lith::module::velocity::locations.end());
									lith::module::velocity::locations.erase(unique(lith::module::velocity::locations.begin(), lith::module::velocity::locations.end()), lith::module::velocity::locations.end());

								}
							}

							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 1000.0)) {

								for (const size_t location : get_positions(memoryd, 1000.0, x)) {

									lith::module::timer::locations.push_back(address + location * sizeof(double));
									sort(lith::module::timer::locations.begin(), lith::module::timer::locations.end());
									lith::module::timer::locations.erase(unique(lith::module::timer::locations.begin(), lith::module::timer::locations.end()), lith::module::timer::locations.end());

								}
							}

							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.3)) {

								for (const size_t location : get_positions(memoryd, 0.3, x)) {

									lith::module::bhop::locations.push_back(address + location * sizeof(double));
									sort(lith::module::bhop::locations.begin(), lith::module::bhop::locations.end());
									lith::module::bhop::locations.erase(unique(lith::module::bhop::locations.begin(), lith::module::bhop::locations.end()), lith::module::bhop::locations.end());

								}
							}

							if (size_t x = std::count(memoryf.begin(), memoryf.end(), 0.02666667f)) {

								for (const size_t location : get_positions(memoryf, 0.02666667f, x)) {

									lith::module::nametags::locations1.push_back(address + location * sizeof(float));

									sort(lith::module::nametags::locations1.begin(), lith::module::nametags::locations1.end());
									lith::module::nametags::locations1.erase(unique(lith::module::nametags::locations1.begin(), lith::module::nametags::locations1.end()), lith::module::nametags::locations1.end());

								}

							}

							if (size_t x = std::count(memoryf.begin(), memoryf.end(), -0.02666667f)) {

								for (const size_t location : get_positions(memoryf, -0.02666667f, x)) {

									lith::module::nametags::locations2.push_back(address + location * sizeof(float));

									sort(lith::module::nametags::locations2.begin(), lith::module::nametags::locations2.end());
									lith::module::nametags::locations2.erase(unique(lith::module::nametags::locations2.begin(), lith::module::nametags::locations2.end()), lith::module::nametags::locations2.end());

								}

							}

							if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.08)) {

								if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.9800000190734863)) {

									for (const size_t location : get_positions(memoryd, 0.9800000190734863, x)) {

										lith::module::fly::locationsfly.push_back(address + location * sizeof(double));

										sort(lith::module::fly::locationsfly.begin(), lith::module::fly::locationsfly.end());
										lith::module::fly::locationsfly.erase(unique(lith::module::fly::locationsfly.begin(), lith::module::fly::locationsfly.end()), lith::module::fly::locationsfly.end());

									}

								}
							}

						}

					}

					std::this_thread::sleep_for(std::chrono::seconds(5));
				}

			}

		}

	}

}