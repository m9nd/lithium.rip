#include "main.h"

template<class val>
std::vector<size_t> get_positions(std::vector<val> buffer, val value, size_t times_found) {
    std::vector<size_t> positions;
    size_t pos = std::distance(buffer.begin(), find(buffer.begin(), buffer.end(), value));
    size_t lastpos = pos;

    while (pos < buffer.size()) {
        if (positions.size() >= times_found)
            break;
        positions.push_back(pos);
        size_t calc = pos + 1;
        pos = std::distance(buffer.begin(), find(buffer.begin() + calc, buffer.end(), value));
        if (pos == lastpos)
            break;
    }
    return positions;
}

size_t min_address = 0x02000000;
size_t max_address = 0x08000000;

void calculator() {
    while (::info::verified) {
        bool found = false;

        size_t address = 0x2000000;

        MEMORY_BASIC_INFORMATION mbi;

        while (NT_SUCCESS(ZwQueryVirtualMemory(::info::minecraft_handle, (void*)address, MemoryBasicInformation,
            &mbi, sizeof(mbi), nullptr))) {
            if (mbi.State == MEM_COMMIT && ((mbi.Protect == PAGE_EXECUTE_READWRITE) | (mbi.Protect == PAGE_READWRITE) |
                (mbi.Protect == PAGE_EXECUTE_WRITECOPY) |
                (mbi.Protect == PAGE_WRITECOPY))) {

                if (!found) {
                    min_address = address;
                    found = !found;
                }

            }

            if (address + mbi.RegionSize >= 0x10000000)
                break;
            else
                address += mbi.RegionSize;
        }
        max_address = address;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

}

void ::scanner::thread() {
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&calculator,
        nullptr, 0, nullptr);
    while (::info::verified) {
        DWORD status = 0;
        if (GetExitCodeProcess(::info::minecraft_handle, &status)) {
            if (status != STILL_ACTIVE)
                exit(0);
        }

        for (size_t address = min_address; address <= max_address; address += 4096) {
            std::vector<double> memoryd(4096);
            std::vector<float> memoryf(4096);

            bool doubleread = NT_SUCCESS(ZwReadVirtualMemory(::info::minecraft_handle, (void*)address, &memoryd[0], 4096,
                nullptr));
            bool floatread = false;

            if (doubleread)
                floatread = NT_SUCCESS(ZwReadVirtualMemory(::info::minecraft_handle, (void*)address, &memoryf[0], 4096, nullptr));

            if (doubleread && floatread) {
                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 4.5)) {
                    for (const size_t location : get_positions(memoryd, 4.5, x)) {
                        ::modules::reach::unlimit.push_back(address + location * sizeof(double));

                        sort(::modules::reach::unlimit.begin(), ::modules::reach::unlimit.end());
                        ::modules::reach::unlimit.erase(
                            unique(::modules::reach::unlimit.begin(), ::modules::reach::unlimit.end()),
                            ::modules::reach::unlimit.end());

                    }


                    if (size_t d = std::count(memoryd.begin(), memoryd.end(), 3.0)) {
                        for (const size_t location : get_positions(memoryd, 3.0, d)) {
                            ::modules::reach::doubles.push_back(address + location * sizeof(double));

                            sort(::modules::reach::doubles.begin(), ::modules::reach::doubles.end());
                            ::modules::reach::doubles.erase(
                                unique(::modules::reach::doubles.begin(), ::modules::reach::doubles.end()),
                                ::modules::reach::doubles.end());

                        }

                    }

                    if (size_t f = std::count(memoryf.begin(), memoryf.end(), 3.0f)) {
                        for (const size_t location : get_positions(memoryf, 3.0f, f)) {
                            ::modules::reach::floats.push_back(address + location * sizeof(float));

                            sort(::modules::reach::floats.begin(), ::modules::reach::floats.end());
                            ::modules::reach::floats.erase(
                                unique(::modules::reach::floats.begin(), ::modules::reach::floats.end()),
                                ::modules::reach::floats.end());

                        }

                    }
                }

                if (address > 0x03000000) {
                    if (size_t x = std::count(memoryf.begin(), memoryf.end(), 2.5f)) {
                        for (const size_t location : get_positions(memoryf, 2.5f, x)) {
                            ::modules::esp::locations.push_back(address + location * sizeof(float));
                            sort(::modules::esp::locations.begin(), ::modules::esp::locations.end());
                            ::modules::esp::locations.erase(
                                unique(::modules::esp::locations.begin(), ::modules::esp::locations.end()),
                                ::modules::esp::locations.end());
                        }
                    }
                }

                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 16.0)) {
                    for (const size_t location : get_positions(memoryd, 16.0, x)) {
                        ::modules::cavefinder::locations.push_back(address + location * sizeof(double));
                        sort(::modules::cavefinder::locations.begin(), ::modules::cavefinder::locations.end());
                        ::modules::cavefinder::locations.erase(unique(::modules::cavefinder::locations.begin(),
                            ::modules::cavefinder::locations.end()),
                            ::modules::cavefinder::locations.end());
                    }
                }

                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 8000.0)) {
                    for (const size_t location : get_positions(memoryd, 8000.0, x)) {
                        ::modules::velocity::locations.push_back(address + location * sizeof(double));
                        sort(::modules::velocity::locations.begin(), ::modules::velocity::locations.end());
                        ::modules::velocity::locations.erase(
                            unique(::modules::velocity::locations.begin(), ::modules::velocity::locations.end()),
                            ::modules::velocity::locations.end());
                    }
                }

                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 1000.0)) {
                    for (const size_t location : get_positions(memoryd, 1000.0, x)) {
                        ::modules::timer::locations.push_back(address + location * sizeof(double));
                        sort(::modules::timer::locations.begin(), ::modules::timer::locations.end());
                        ::modules::timer::locations.erase(
                            unique(::modules::timer::locations.begin(), ::modules::timer::locations.end()),
                            ::modules::timer::locations.end());
                    }
                }

                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.3)) {
                    for (const size_t location : get_positions(memoryd, 0.3, x)) {
                        ::modules::bhop::locations.push_back(address + location * sizeof(double));
                        sort(::modules::bhop::locations.begin(), ::modules::bhop::locations.end());
                        ::modules::bhop::locations.erase(
                            unique(::modules::bhop::locations.begin(), ::modules::bhop::locations.end()),
                            ::modules::bhop::locations.end());
                    }
                }

                if (size_t x = std::count(memoryf.begin(), memoryf.end(), 0.02666667f)) {
                    for (const size_t location : get_positions(memoryf, 0.02666667f, x)) {
                        ::modules::nametags::locations1.push_back(address + location * sizeof(float));
                        sort(::modules::nametags::locations1.begin(), ::modules::nametags::locations1.end());
                        ::modules::nametags::locations1.erase(unique(::modules::nametags::locations1.begin(),
                            ::modules::nametags::locations1.end()),
                            ::modules::nametags::locations1.end());
                    }
                }

                if (size_t x = std::count(memoryf.begin(), memoryf.end(), 0.16277136f)) {
                    for (const size_t location : get_positions(memoryf, 0.16277136f, x)) {
                        ::modules::speed::locations.push_back(address + location * sizeof(float));
                        sort(::modules::speed::locations.begin(), ::modules::speed::locations.end());
                        ::modules::speed::locations.erase(unique(::modules::speed::locations.begin(),
                            ::modules::speed::locations.end()),
                            ::modules::speed::locations.end());
                    }
                }

                if (size_t x = std::count(memoryf.begin(), memoryf.end(), -0.02666667f)) {
                    for (const size_t location : get_positions(memoryf, -0.02666667f, x)) {
                        ::modules::nametags::locations2.push_back(address + location * sizeof(float));

                        sort(::modules::nametags::locations2.begin(), ::modules::nametags::locations2.end());
                        ::modules::nametags::locations2.erase(unique(::modules::nametags::locations2.begin(),
                            ::modules::nametags::locations2.end()),
                            ::modules::nametags::locations2.end());
                    }
                }

                if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.08)) {
                    if (size_t x = std::count(memoryd.begin(), memoryd.end(), 0.9800000190734863)) {
                        for (const size_t location : get_positions(memoryd, 0.9800000190734863, x)) {
                            ::modules::fly::locationsfly.push_back(address + location * sizeof(double));

                            sort(::modules::fly::locationsfly.begin(), ::modules::fly::locationsfly.end());
                            ::modules::fly::locationsfly.erase(
                                unique(::modules::fly::locationsfly.begin(), ::modules::fly::locationsfly.end()),
                                ::modules::fly::locationsfly.end());
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}