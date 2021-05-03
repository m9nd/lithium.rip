#include "main.h"

static double defaultbhop = 0.3;

namespace v
{
    namespace modules
    {
        namespace bhop
        {
            void enable() {
                double newbhop = defaultbhop * ::modules::bhop::speed;
                double buffer;
                for (size_t x = 0; x < ::modules::bhop::locations.size(); x++) {

                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::bhop::locations[x], &buffer, sizeof(double), 0)) {
                        if (buffer <= 30.0 && buffer >= 0.3) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::bhop::locations[x], &newbhop, sizeof(double), 0);
                        }
                        else {
                            ::modules::bhop::locations.erase(::modules::bhop::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::bhop::locations.erase(::modules::bhop::locations.begin() + x);
                        x = 0;
                    }
                }

            }

            void disable() {
                double buffer;
                for (size_t x = 0; x < ::modules::bhop::locations.size(); x++) {
                    if (ReadProcessMemory::info::minecraft_handle, (LPVOID)::modules::bhop::locations[x], &buffer, sizeof(double), 0)) {
                        if (buffer <= 30.0 && buffer >= 0.3) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::bhop::locations[x], &defaultbhop, sizeof(double), 0);
                        }
                        else {
                            ::modules::bhop::locations.erase(::modules::bhop::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::bhop::locations.erase(::modules::bhop::locations.begin() + x);
                        x = 0;
                    }
                }
            }

            void thread() {
                while (::info::verified) {
                    if (::modules::bhop::enabled) {
                        ::modules::bhop::used = true;
                        enable();
                    }
                    else {
                        if (::modules::bhop::used) {
                            disable();
                            ::modules::bhop::used = false;
                        }

                    }

                    if (::modules::bhop::enabled) {
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