#include "main.h"

static float defaultspeed = 0.16277136f;
namespace v
{
    namespace modules
    {
        namespace speed
        {
            void enable() {
                float newspeed = defaultspeed * ::modules::speed::multiplier;
                float buffer;
                for (size_t x = 0; x < ::modules::speed::locations.size(); x++) {

                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::speed::locations[x], &buffer, sizeof(float), nullptr)) {
                        \
                            if (buffer <= 3.2554272f && buffer >= 0.16277136f) {
                                WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::speed::locations[x], &newspeed, sizeof(float), nullptr);
                            }
                            else {
                                ::modules::speed::locations.erase(::modules::speed::locations.begin() + x);
                                x = 0;
                            }
                    }
                    else {
                        ::modules::speed::locations.erase(::modules::speed::locations.begin() + x);
                        x = 0;
                    }
                }

            }

            void disable() {
                float buffer;
                for (size_t x = 0; x < ::modules::speed::locations.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::speed::locations[x], &buffer, sizeof(float), nullptr)) {
                        if (buffer <= 3.2554272f && buffer >= 0.16277136f) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::speed::locations[x], &defaultspeed, sizeof(float), nullptr);
                        }
                        else {
                            ::modules::speed::locations.erase(::modules::speed::locations.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::speed::locations.erase(::modules::speed::locations.begin() + x);
                        x = 0;
                    }
                }
            }

            void thread() {
                while (::info::verified) {
                    if (::modules::speed::enabled) {
                        ::modules::speed::used = true;
                        enable();
                    }
                    else {
                        if (::modules::speed::used) {
                            disable();
                            ::modules::speed::used = false;
                        }

                    }

                    if (::modules::speed::enabled) {
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