cmake_minimum_required(VERSION 3.25)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(sfinae LANGUAGES CXX VERSION ${PROJECT_VERSION})

set(APP sfinae)
set(SRC ./src/sfinae.cpp)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/x64-linux)

add_executable(${APP} ${SRC})

target_compile_features(${APP} PUBLIC cxx_std_23)
target_compile_options(${APP} PUBLIC
    -Wall
    -Werror
    -Wextra
    -Wold-style-cast
    -Weffc++
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${APP} PUBLIC -Oz)
endif()

set(CPACK_GENERATOR DEB)
set(CMAKE_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "example@example.com")
include(CPack)