cmake_minimum_required(VERSION 3.28.1)
project(su_isc_crackme)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.2\\mingw_64")
endif()

find_package(
        Qt6 COMPONENTS
        Core
        Widgets
        Gui
        REQUIRED)

include_directories(${Qt6Widgets_INCLUDE_DIRS})
add_executable(su_isc_crackme src/main.cpp
        src/License.cpp
        src/License.h
)
target_link_libraries(su_isc_crackme
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
)

if (WIN32)
    add_custom_command(TARGET su_isc_crackme POST_BUILD
        COMMAND C:/Qt/6.7.2/mingw_64/bin/windeployqt.exe --release $<TARGET_FILE:su_isc_crackme>
        COMMENT "Running windeployqt to bundle Qt dependencies")
endif()