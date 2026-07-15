cmake_minimum_required(VERSION 3.20)
project(rust_trainer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # Silence the noise and use UTF-8 for the wide-char string handling.
    add_compile_options(/W3 /utf-8)
endif()

# ---------------------------------------------------------------------------
#  Dear ImGui is fetched automatically at configure time. No manual download.
#  Pinned to a known-good tag. Bump GIT_TAG to upgrade.
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.9
)
FetchContent_Populate(imgui)

# imgui ships no CMake target of its own here, so build it from sources.
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# ---------------------------------------------------------------------------
#  Trainer as an injected DLL (internal cheat).
# ---------------------------------------------------------------------------
add_library(rust_trainer SHARED
    src/main.cpp
    src/core/mem.cpp
    src/core/mem.h
    src/core/vecmath.h
    src/esp/esp.cpp
    src/esp/esp.h
    src/overlay/overlay.cpp
    src/overlay/overlay.h
)

# All source subdirs are on the include path so headers can be included
# by bare filename (e.g. #include "rust-dumper_output.h").
target_include_directories(rust_trainer PRIVATE
    src
    src/core
    src/esp
    src/overlay
    src/offsets
)

target_link_libraries(rust_trainer PRIVATE imgui d3d11 dxgi)
