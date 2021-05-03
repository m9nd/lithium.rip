#include "main.h"

static double defaultcavefinder = 16;
static double newcavefinder = 1879048192;

namespace v
{
    namespace modules
    {
        namespace cavefinder
        {
            void enable() {
                double buffer;
                for (size_t x = 0; x < ::modules::cavefinder::locations.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::cavefinder::locations[x], &buffer, sizeof(double), nullptr)) {
                        if (buffer >= 16 && buffer <= 1879048192) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::cavefinder::locations[x], &newcavefinder, sizeof(double), nullptr);
                        }
                        else {
                            ::modules::cavefinder::locations.erase(::modules::cavefinder::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::cavefinder::locations.erase(::modules::cavefinder::locations.begin() + x);
                        x = 0;
                    }
                }


            }

            void disable() {
                double buffer;
                for (size_t x = 0; x < ::modules::cavefinder::locations.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::cavefinder::locations[x], &buffer, sizeof(double), nullptr)) {
                        if (buffer >= 16 && buffer <= 1879048192) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::cavefinder::locations[x], &defaultcavefinder, sizeof(double), nullptr);
                        }
                        else {
                            ::modules::cavefinder::locations.erase(::modules::cavefinder::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::cavefinder::locations.erase(::modules::cavefinder::locations.begin() + x);
                        x = 0;
                    }
                }

            }

            void thread() {
                while (::info::verified) {
                    if (::modules::cavefinder::enabled) {
                        ::modules::cavefinder::used = true;
                        enable();
                    }
                    else {
                        if (::modules::cavefinder::used) {
                            disable();
                            ::modules::cavefinder::used = false;
                        }

                    }

                    if (::modules::cavefinder::enabled) {
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