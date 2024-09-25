cmake_minimum_required(VERSION 3.29)
project(su_isc_crackme)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(
        Qt5 COMPONENTS
        Core
        Widgets
        Gui
        REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_executable(su_isc_crackme main.cpp
        License.cpp
        License.h
#        b64.cpp
#        b64.h
)
target_link_libraries(su_isc_crackme
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
)

