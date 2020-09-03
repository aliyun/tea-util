
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(darabonba_util VERSION "0.1.0")

# <<< General set up >>>
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")

message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if (CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif ()

list(APPEND flags "-fPIC" "-Wall" "-Wno-dev")
if (NOT WIN32)
    list(APPEND flags "-Wextra" "-Wpedantic")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_library(${PROJECT_NAME} SHARED "")

set(headers
        include/darabonba/util.hpp)

target_sources(${PROJECT_NAME}
        PRIVATE
        src/util.cpp
        ${headers})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        POSITION_INDEPENDENT_CODE 1
        SOVERSION ${PROJECT_VERSION_MAJOR}
        OUTPUT_NAME "util"
        DEBUG_POSTFIX "_d"
        PUBLIC_HEADER "${headers}"
        MACOSX_RPATH ON
        WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(external/libraries)
target_link_libraries(${PROJECT_NAME} PRIVATE )

message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
    set(DEF_INSTALL_CMAKEDIR CMake)
else()
    set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

foreach(p LIB BIN INCLUDE CMAKE)
    file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path )
    message(STATUS "Installing ${p} components to ${_path}")
    unset(_path)
endforeach()

# Prepare RPATH
file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
if(APPLE)
    set(_rpath "@loader_path/${_rel}")
else()
    set(_rpath "\$ORIGIN/${_rel}")
endif()
file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" install_RPATH)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        MACOSX_RPATH ON
        SKIP_BUILD_RPATH OFF
        BUILD_WITH_INSTALL_RPATH OFF
        INSTALL_RPATH "${install_RPATH}"
        INSTALL_RPATH_USE_LINK_PATH ON)

install(
        TARGETS
        ${PROJECT_NAME}
        ARCHIVE
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
        RUNTIME
        DESTINATION ${INSTALL_BINDIR}
        COMPONENT bin
        LIBRARY
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
        PUBLIC_HEADER
        DESTINATION ${INSTALL_INCLUDEDIR}/darabonba
        COMPONENT dev
)