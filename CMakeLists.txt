cmake_minimum_required(VERSION 3.20)
project(rust_trainer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # خاموش کردن اخطارهای امنیتی و استفاده از UTF-8
    add_compile_options(/W3 /utf-8 /D_CRT_SECURE_NO_WARNINGS)
endif()

# ---------------------------------------------------------------------------
#  Dear ImGui به‌صورت خودکار در زمان Configure دانلود می‌شود.
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.9
)
FetchContent_Populate(imgui)

# ساخت کتابخانه استاتیک ImGui از سورس
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
#  فایل DLL اصلی (ترینر)
# ---------------------------------------------------------------------------
add_library(rust_trainer SHARED
    src/main.cpp
    # src/core/mem.cpp   <-- این خط را حذف کن (توابع در mem.h تعریف شده‌اند)
    src/core/mem.h
    src/core/vecmath.h
    src/esp/esp.cpp
    src/esp/esp.h
    src/overlay/overlay.cpp
    src/overlay/overlay.h
)

# مسیرهای Include برای تمام زیرپوشه‌ها
target_include_directories(rust_trainer PRIVATE
    src
    src/core
    src/esp
    src/overlay
    src/offsets
)

target_link_libraries(rust_trainer PRIVATE imgui d3d11 dxgi psapi)
