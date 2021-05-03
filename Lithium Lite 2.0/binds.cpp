#include "main.h"

std::string getbindtext(size_t hex);

void ::binds::thread() {
    size_t selected_bind = 0;
    bool bind_break = false;

    while (::info::verified) {
        if (
            
            
            modules::clicker::left::bind_pressed) {

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            selected_bind = 1;
            ::modules::clicker::left::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;

            while (::modules::clicker::left::selected_bind == 0) {

                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }

                std::this_thread::sleep_for(std::chrono::milliseconds(2));

                for (size_t i = 3; i < 256; i++) {

                    if (i != 13) {

                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::clicker::left::selected_bind == 0) {

                            if (!lith_bind_first_loop) {

                                ::modules::clicker::left::selected_bind = i;
                                ::modules::clicker::left::bind = getbindtext(i);

                                if (i == 27) {
                                    ::modules::clicker::left::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::clicker::left::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::clicker::left::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::clicker::left::selected_bind) & 0x8000) {
            if (!::modules::clicker::left::enabled) {
                while (GetAsyncKeyState(::modules::clicker::left::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::clicker::left::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::clicker::left::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::clicker::left::enabled = false;
            }
        }

        if (::modules::clicker::right::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::clicker::right::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::clicker::right::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::clicker::right::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::clicker::right::selected_bind = i; ::modules::clicker::right::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::clicker::right::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::clicker::right::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::clicker::right::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::clicker::right::selected_bind) & 0x8000) {
            if (!::modules::clicker::right::enabled) {
                while (GetAsyncKeyState(::modules::clicker::right::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::clicker::right::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::clicker::right::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::clicker::right::enabled = false;
            }
        }

        if (::modules::velocity::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::velocity::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::velocity::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::velocity::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::velocity::selected_bind = i; ::modules::velocity::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::velocity::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::velocity::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::velocity::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
            if (!::modules::velocity::enabled) {
                while (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::velocity::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::velocity::enabled = false;
            }
        }

        if (::modules::reach::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::reach::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::reach::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::reach::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::reach::selected_bind = i; ::modules::reach::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::reach::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::reach::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::reach::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::reach::selected_bind) & 0x8000) {
            if (!::modules::reach::enabled) {
                while (GetAsyncKeyState(::modules::reach::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::reach::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::reach::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::reach::enabled = false;
            }
        }

        if (::modules::velocity::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::velocity::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::velocity::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::velocity::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::velocity::selected_bind = i; ::modules::velocity::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::velocity::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::velocity::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::velocity::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
            if (!::modules::velocity::enabled) {
                while (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::velocity::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::velocity::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::velocity::enabled = false;
            }
        }

        if (::modules::throwpot::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::throwpot::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::throwpot::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::throwpot::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::throwpot::selected_bind = i; ::modules::throwpot::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::throwpot::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::throwpot::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::throwpot::bind_pressed = false;
                bool_counter++;
            }
        }

        if (::modules::fly::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::fly::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::fly::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::fly::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::fly::selected_bind = i; ::modules::fly::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::fly::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::fly::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::fly::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::fly::selected_bind) & 0x8000) {
            if (!::modules::fly::waiting) {
                if (!::modules::fly::enabled) {
                    while (GetAsyncKeyState(::modules::fly::selected_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }::modules::fly::enabled = true;
                }
                else {
                    while (GetAsyncKeyState(::modules::fly::selected_bind) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    }::modules::fly::enabled = false;
                }
            }
        }

        if (::modules::nametags::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::nametags::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::nametags::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::nametags::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::nametags::selected_bind = i; ::modules::nametags::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::nametags::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::nametags::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::nametags::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::nametags::selected_bind) & 0x8000) {
            if (!::modules::nametags::enabled) {
                while (GetAsyncKeyState(::modules::nametags::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::nametags::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::nametags::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::nametags::enabled = false;
            }
        }

        if (::modules::esp::bind_pressed) {

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            selected_bind = 1;
            ::modules::esp::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;

            while (::modules::esp::selected_bind == 0) {

                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }

                std::this_thread::sleep_for(std::chrono::milliseconds(2));

                for (size_t i = 3; i < 256; i++) {

                    if (i != 13) {

                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::esp::selected_bind == 0) {

                            if (!lith_bind_first_loop) {

                                ::modules::esp::selected_bind = i;
                                ::modules::esp::bind = getbindtext(i);

                                if (i == 27) {
                                    ::modules::esp::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::esp::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::esp::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::esp::selected_bind) & 0x8000) {
            if (!::modules::esp::enabled) {
                while (GetAsyncKeyState(::modules::esp::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::esp::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::esp::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::esp::enabled = false;
            }
        }

        if (::modules::cavefinder::bind_pressed) {

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            selected_bind = 1;
            ::modules::cavefinder::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;

            while (::modules::cavefinder::selected_bind == 0) {

                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }

                std::this_thread::sleep_for(std::chrono::milliseconds(2));

                for (size_t i = 3; i < 256; i++) {

                    if (i != 13) {

                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::cavefinder::selected_bind == 0) {

                            if (!lith_bind_first_loop) {

                                ::modules::cavefinder::selected_bind = i;
                                ::modules::cavefinder::bind = getbindtext(i);

                                if (i == 27) {
                                    ::modules::cavefinder::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::cavefinder::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::cavefinder::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::cavefinder::selected_bind) & 0x8000) {
            if (!::modules::cavefinder::enabled) {
                while (GetAsyncKeyState(::modules::cavefinder::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::cavefinder::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::cavefinder::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::cavefinder::enabled = false;
            }
        }

        if (::modules::timer::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::timer::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::timer::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::timer::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::timer::selected_bind = i; ::modules::timer::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::timer::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::timer::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::timer::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::timer::selected_bind) & 0x8000) {
            if (!::modules::timer::enabled) {
                while (GetAsyncKeyState(::modules::timer::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::timer::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::timer::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::timer::enabled = false;
            }
        }

        if (::modules::bhop::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::bhop::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::bhop::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::bhop::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::bhop::selected_bind = i; ::modules::bhop::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::bhop::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::bhop::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::bhop::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::bhop::selected_bind) & 0x8000) {
            if (!::modules::bhop::enabled) {
                while (GetAsyncKeyState(::modules::bhop::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::bhop::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::bhop::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::bhop::enabled = false;
            }
        }

        if (::modules::speed::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::speed::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::speed::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::speed::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::speed::selected_bind = i; ::modules::speed::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::speed::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::speed::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::speed::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::speed::selected_bind) & 0x8000) {
            if (!::modules::speed::enabled) {
                while (GetAsyncKeyState(::modules::speed::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::speed::enabled = true;
            }
            else {
                while (GetAsyncKeyState(::modules::speed::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::speed::enabled = false;
            }
        }

        if (::modules::destruct::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::destruct::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::destruct::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::destruct::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::destruct::selected_bind = i; ::modules::destruct::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::destruct::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::destruct::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::destruct::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::destruct::selected_bind) & 0x8000) {

            ::modules::destruct::execute();

        }

        if (::modules::hide::bind_pressed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            selected_bind = 1;
            ::modules::hide::selected_bind = 0;
            bool lith_bind_first_loop = false; size_t bool_counter = 0;
            while (::modules::hide::selected_bind == 0) {
                if (bool_counter < 1) { lith_bind_first_loop = true; }
                else { lith_bind_first_loop = false; }
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                for (size_t i = 3; i < 256; i++) {
                    if (i != 13) {
                        if (GetAsyncKeyState((i)&SHRT_MAX) && ::modules::hide::selected_bind == 0) {
                            if (!lith_bind_first_loop) {
                                ::modules::hide::selected_bind = i; ::modules::hide::bind = getbindtext(i);
                                if (i == 27) {
                                    ::modules::hide::bind = "[NONE]";
                                    selected_bind = 1;
                                    ::modules::hide::selected_bind = 0;
                                    bind_break = true;
                                }
                                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                            }
                        }
                    }
                }
                if (bind_break) { bind_break = false; break; }
                selected_bind = 0;
                ::modules::hide::bind_pressed = false;
                bool_counter++;
            }
        }
        if (GetAsyncKeyState(::modules::hide::selected_bind) & 0x8000) {
            if (!::modules::hide::enabled) {
                ShowWindow(::gui::hwnd, SW_HIDE);
                while (GetAsyncKeyState(::modules::hide::selected_bind) & 0x8000) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }::modules::hide::enabled = true;
            }
            else {
                ShowWindow(::gui::hwnd, SW_SHOW);
                while (GetAsyncKeyState(::modules::hide::selected_bind) & 0x8000) {

                    std::this_thread::sleep_for(std::chrono::milliseconds(5));

                }
                ::modules::hide::enabled = false;
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}


std::string getbindtext(size_t hex) {
    const char* const lith_key_string[] = {
        "Unknown",
        "LButton",
        "RButton",
        "CANCEL",
        "MButton",
        "MButton2",
        "MButton3",
        "Unknown",
        "Back",
        "Tab",
        "Unknown",
        "Unknown",
        "Clear",
        "Return",
        "Unknown",
        "Unknown",
        "Shift",
        "Control",
        "Menu",
        "Pause",
        "Capital",
        "Unknown",
        "Unknown",
        "Unknown",
        "Final",
        "Unknown",
        "Unknown",
        "Escape",
        "Convert",
        "NonConvert",
        "Accept",
        "ModeChange",
        "Space",
        "Prior",
        "Next",
        "End",
        "Home",
        "Left",
        "Up",
        "Right",
        "Down",
        "Select",
        "Print",
        "Execute",
        "SnpShot",
        "Insert",
        "Delete",
        "Help",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "Lwin",
        "Rwin",
        "Apps",
        "Unknown",
        "Sleep",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "*",
        "+",
        "Separator",
        "-",
        "Decimal",
        "/",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "F13",
        "F14",
        "F15",
        "F16",
        "F17",
        "F18",
        "F19",
        "F20",
        "F21",
        "F22",
        "F23",
        "F24",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Numlock",
        "Scroll",
        "Equal",
        "Masshou",
        "Touroku",
        "Loya",
        "Roya",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "LShift",
        "RShift",
        "Control",
        "Control",
        "Menu",
        "RMenu",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
        "Unknown",
    };
    return "[Bind: " + std::string(lith_key_string[hex]) + "]";
}