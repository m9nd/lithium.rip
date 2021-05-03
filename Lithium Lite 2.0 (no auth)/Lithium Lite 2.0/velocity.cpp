#include "main.h"

static double defaultvelocity = 8000.0;

namespace v
{
    namespace modules
    {
        namespace velocity
        {
            void enable() {
                double newvelocity = 800000.0 / (double)
                    
                    
                    
                    
                    utils::random_float(::modules::velocity::min, ::modules::velocity::max);
                double buffer;
                for (size_t x = 0; x < ::modules::velocity::locations.size(); x++) {

                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::velocity::locations[x], &buffer, sizeof(double), nullptr)) {
                        if (buffer <= 800000.0 && buffer >= 8000.0) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::velocity::locations[x], &newvelocity, sizeof(double), nullptr);
                        }
                        else {
                            ::modules::velocity::locations.erase(::modules::velocity::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::velocity::locations.erase(::modules::velocity::locations.begin() + x);
                        x = 0;
                    }
                }

            }

            void disable() {
                double buffer;
                for (size_t x = 0; x < ::modules::velocity::locations.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::velocity::locations[x], &buffer, sizeof(double), 0)) {
                        if (buffer <= 800000.0 && buffer >= 8000.0) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::velocity::locations[x], &defaultvelocity, sizeof(double), 0);
                        }
                        else {
                            ::modules::velocity::locations.erase(::modules::velocity::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::velocity::locations.erase(::modules::velocity::locations.begin() + x);
                        x = 0;
                    }
                }
            }

            void thread() {
                while (::info::verified) {
                    if (::modules::velocity::enabled) {
                        ::modules::velocity::used = true;
                        enable();
                    }
                    else {
                        if (::modules::velocity::used) {
                            disable();
                            ::modules::velocity::used = false;
                        }

                    }

                    if (::modules::velocity::enabled) {
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