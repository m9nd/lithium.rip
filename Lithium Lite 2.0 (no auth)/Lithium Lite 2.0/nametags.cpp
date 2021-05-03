#include "main.h"

static float defaultnametags1 = 0.02666667f;
static float defaultnametags2 = -0.02666667f;

namespace v
{
    namespace modules
    {
        namespace nametags
        {
            void enable() {
                float newnametags1 = defaultnametags1 * ::modules::nametags::multiplier;
                float newnametags2 = -(defaultnametags1 * ::modules::nametags::multiplier);
                float buffer;
                for (size_t x = 0; x < ::modules::nametags::locations1.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations1[x], &buffer, sizeof(float), 0)) {
                        if (buffer <= 0.09f && buffer >= 0.02666667f) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations1[x], &newnametags1, sizeof(float), 0);
                        }
                        else {
                            ::modules::nametags::locations1.erase(::modules::nametags::locations1.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::nametags::locations1.erase(::modules::nametags::locations1.begin() + x);
                        x = 0;
                    }
                }

                for (size_t x = 0; x < ::modules::nametags::locations2.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations2[x], &buffer, sizeof(float), 0)) {
                        if (buffer <= -0.02666667f && buffer >= -0.09f) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations2[x], &newnametags2, sizeof(float), 0);
                        }
                        else {
                            ::modules::nametags::locations2.erase(::modules::nametags::locations2.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::nametags::locations2.erase(::modules::nametags::locations2.begin() + x);
                        x = 0;
                    }
                }

            }

            void disable() {
                float buffer;
                for (size_t x = 0; x < ::modules::nametags::locations1.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations1[x], &buffer, sizeof(float), 0)) {
                        if (buffer <= 0.09f && buffer >= 0.02666667f) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations1[x], &defaultnametags1, sizeof(float), 0);
                        }
                        else {
                            ::modules::nametags::locations1.erase(::modules::nametags::locations1.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::nametags::locations1.erase(::modules::nametags::locations1.begin() + x);
                        x = 0;
                    }
                }

                for (size_t x = 0; x < ::modules::nametags::locations2.size(); x++) {
                    if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations2[x], &buffer, sizeof(float), 0)) {
                        if (buffer <= -0.02666667f && buffer >= -0.09f) {
                            WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::nametags::locations2[x], &defaultnametags2, sizeof(float), 0);
                        }
                        else {
                            ::modules::nametags::locations2.erase(::modules::nametags::locations2.begin() + x);
                            x = 0;
                        }
                    }
                    else {
                        ::modules::nametags::locations2.erase(::modules::nametags::locations2.begin() + x);
                        x = 0;
                    }
                }
            }

            void thread() {
                while (::info::verified) {
                    if (::modules::nametags::enabled) {
                        ::modules::nametags::used = true;
                        enable();
                    }
                    else {
                        if (::modules::nametags::used) {
                            disable();
                                ::modules::nametags::used = false;
                        }

                    }

                    if (::modules::nametags::enabled) {
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