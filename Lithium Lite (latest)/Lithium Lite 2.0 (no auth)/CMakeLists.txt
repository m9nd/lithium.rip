cmake_minimum_required(VERSION 3.17)
project(LithiumLite)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(auth)
include_directories(auth/crypto)
include_directories(imgui)
include_directories(imgui/fonts)
add_executable(LithiumLite
        imgui/fonts/fa.h
        imgui/fonts/roboto.h
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_dx11.cpp
        imgui/imgui_impl_dx11.h
        imgui/imgui_impl_win32.cpp
        imgui/imgui_impl_win32.h
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        misc/binds.cpp
        misc/status.cpp
        modules/combat/clicker.cpp
        modules/combat/reach.cpp
        modules/combat/throwpot.cpp
        modules/combat/velocity.cpp
        modules/destruct/destruct.cpp
        modules/movement/antiafk.cpp
        modules/movement/bhop.cpp
        modules/movement/fly.cpp
        modules/movement/speed.cpp
        modules/movement/timer.cpp
        modules/visuals/cavefinder.cpp
        modules/visuals/esp.cpp
        modules/visuals/nametags.cpp
        scanner/scanner.cpp
        main.cpp
        main.h
        ntdll.h
        xorstr.h)

SET_TARGET_PROPERTIES(LithiumLite PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:CONSOLE ")