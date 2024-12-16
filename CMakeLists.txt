cmake_minimum_required(VERSION 3.23)

project(
    egt-samples
    VERSION 1.6
    DESCRIPTION "Some examples of applications built with the EGT library."
    LANGUAGES CXX
)
#set(PROJECT_VERSION_RC 1)
if (DEFINED PROJECT_VERSION_RC)
    string(APPEND PROJECT_VERSION "-rc${PROJECT_VERSION_RC}")
endif()

include(CheckIncludeFileCXX)
include(GNUInstallDirs)

set(CMAKE_VERBOSE_MAKEFILE True)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBEGT REQUIRED libegt>=1.10)

CHECK_INCLUDE_FILE_CXX(egt/network/http.h HAVE_EGT_NETWORK_HTTP_H)
CHECK_INCLUDE_FILE_CXX(egt/video.h HAVE_EGT_VIDEO_H)

pkg_check_modules(JSONCPP jsoncpp)

add_subdirectory(external)
add_subdirectory(AngryMeatballs)
add_subdirectory(brick)
add_subdirectory(icon)
add_subdirectory(drop)
add_subdirectory(ragdoll)
add_subdirectory(water)
add_subdirectory(layout)

if (HAVE_EGT_NETWORK_HTTP_H)
    add_subdirectory(newsfeed)

    if (JSONCPP_FOUND)
        add_subdirectory(weather)
    endif()
endif()

if (HAVE_EGT_VIDEO_H)
    add_subdirectory(gallery)
endif()
