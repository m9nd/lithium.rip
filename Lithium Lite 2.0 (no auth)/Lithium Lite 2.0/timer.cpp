#include "main.h"

static double defaulttimer = 1000.0;
namespace v
{
    namespace modules
    {
        namespace timer
        {
            void enable() {
                double newtimer = defaulttimer / 
                    
                    
                    modules::timer::multiplier;
                double buffer;
                for (size_t x = 0; x < ::modules::timer::locations.size(); x++) {

                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::timer::locations[x], &buffer, sizeof(double), nullptr)) {
                        if (buffer <= 1000.0 && buffer >= 200.0) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::timer::locations[x], &newtimer, sizeof(double), nullptr);
                        }
                        else {
                            ::modules::timer::locations.erase(::modules::timer::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::timer::locations.erase(::modules::timer::locations.begin() + x);
                        x = 0;
                    }
                }

            }

            void disable() {
                double buffer;
                for (size_t x = 0; x < ::modules::timer::locations.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::timer::locations[x], &buffer, sizeof(double), nullptr)) {
                        if (buffer <= 1000.0 && buffer >= 200.0) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::timer::locations[x], &defaulttimer, sizeof(double), nullptr);
                        }
                        else {
                            ::modules::timer::locations.erase(::modules::timer::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::timer::locations.erase(::modules::timer::locations.begin() + x);
                        x = 0;
                    }
                }
            }

            void thread() {
                while (::info::verified) {
                    if (::modules::timer::enabled) {
                        ::modules::timer::used = true;
                        enable();
                    }
                    else {
                        if (::modules::timer::used) {
                            disable();
                            ::modules::timer::used = false;
                        }

                    }

                    if (::modules::timer::enabled) {
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