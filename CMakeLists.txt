cmake_minimum_required(VERSION 3.28.1)
project(su_isc_crackme)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.2\\mingw_64")
endif()

if (APPLE)
    set(CMAKE_PREFIX_PATH "/usr/local/opt/qt@5")
    find_package(
            Qt5 COMPONENTS
            Core
            Widgets
            Gui
            REQUIRED)
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    include(BundleUtilities)
else()
    find_package(
            Qt6 COMPONENTS
            Core
            Widgets
            Gui
            REQUIRED)
    include_directories(${Qt6Widgets_INCLUDE_DIRS})
endif()

add_executable(su_isc_crackme
        src/main.cpp
        src/License.cpp
        src/License.h
)

if (APPLE)
    target_link_libraries(su_isc_crackme
            Qt5::Core
            Qt5::Widgets
            Qt5::Gui
    )
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES ICON isc_logo.icns)
else ()
    target_link_libraries(su_isc_crackme
            Qt6::Core
            Qt6::Widgets
            Qt6::Gui
    )
endif()

if (WIN32)
#    Add the icon to the executable
    if(EXISTS "${CMAKE_SOURCE_DIR}/isc_logo.ico")
        add_custom_command(TARGET ${EXECUTABLE_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/isc_logo.ico
                $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
        )
    endif()

    add_custom_command(TARGET su_isc_crackme POST_BUILD
        COMMAND C:/Qt/6.7.2/mingw_64/bin/windeployqt.exe --release $<TARGET_FILE:su_isc_crackme>
        COMMENT "Running windeployqt to bundle Qt dependencies")
endif()