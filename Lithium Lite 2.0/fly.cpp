#include "main.h"

void enablef(double value) {
    double buffer;
    for (size_t x = 0; x < ::modules::fly::locationsfly.size(); x++) {
        if (ReadProcessMemory(::info::minecraft_handle, (LPVOID)::modules::fly::locationsfly[x], &buffer, sizeof(double), 0)) {
            if (buffer == 0.9800000190734863 || buffer == 0.08) {
                WriteProcessMemory(::info::minecraft_handle, (LPVOID)::modules::fly::locationsfly[x], &value, sizeof(double), 0);
            }
            else {
                ::modules::fly::locationsfly.erase(::modules::fly::locationsfly.begin() + x);
                x = 0;
            }
        }
        else {
            ::modules::fly::locationsfly.erase(::modules::fly::locationsfly.begin() + x);
            x = 0;
        }
    }

}

void ::modules::fly::disable() {
    enablef(0.9800000190734863);
}

void ::modules::fly::thread() {

    while (::info::verified) {
        if (::modules::fly::enabled) {
            ::modules::fly::used = true;
            enablef(0.08);

        }
        else {

            if (::modules::fly::used) {

                disable();
                ::modules::fly::used = false;

            }

        }

        if (::modules::fly::enabled) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

    }
}