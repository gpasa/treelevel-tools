# Builds the C++ engine on Windows (MSVC, x64 and ARM64): treelevel-engine.exe, the same source as the engine of
# the image and of the Mac (Backends/engine/engine.cpp). The C# host treelevel-tools.exe writes launch.json and
# runs it for Pythia and the passthrough; the other generators run in the image.
#
#   cmake -B build -S . -A ARM64
#   cmake --build build --config Release
#
# win/engine/build.ps1 does both, and win/package/release.ps1 calls it.
#
# Copyright (C) 2026 Guglielmo Pasa. GNU General Public License v3 or later.

cmake_minimum_required(VERSION 3.21)
project(treelevel-engine CXX)

set(ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/../../Backends/engine/engine.cpp")
if(NOT EXISTS "${ENGINE}")
  message(FATAL_ERROR "the engine ${ENGINE} is missing — build from a full checkout")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()
# The static runtime: the engine runs on a machine without the Visual C++ redistributable.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# utf8.manifest makes UTF-8 the code page of every narrow call — paths, arguments, environment — so that a job
# folder under a user name with accents opens like any other (Windows 10 1903 and later).
add_executable(treelevel-engine "${ENGINE}" "${CMAKE_CURRENT_SOURCE_DIR}/utf8.manifest")
target_include_directories(treelevel-engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../Backends/pythia")
if(MSVC)
  target_compile_options(treelevel-engine PRIVATE /EHsc /utf-8 /W3 $<$<CONFIG:Release>:/O2>)
  target_compile_definitions(treelevel-engine PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

install(TARGETS treelevel-engine RUNTIME DESTINATION .)
