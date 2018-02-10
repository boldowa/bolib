#-----------------------------------------------------------
# CMakeList for bolib
#-----------------------------------------------------------

cmake_minimum_required(VERSION 3.1)
include (CheckIncludeFiles)

if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "No build type selected, default to Release")
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING 
                "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(MSVC)
	option(UNICODE "Use UNICODE" OFF)
endif()

### Visual Studio Solution Name
project(bolib C)

###### specify C and C++ compile option
### soecify unix compile option
if(UNIX OR MINGW)
	## define prefix(gcc)
	set(CMAKE_C_FLAGS "-Wall -fpic -ansi -Wconversion")

	## set C Release compile flags
        set(CMAKE_C_FLAGS_RELEASE "-O2 -ffunction-sections -fdata-sections")

	## set C Debug compile option
	#set(CMAKE_C_FLAGS_DEBUG "-Werror -O0 -g")
	set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")

	## set linker link flag
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections")
	set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "-T")
endif()

if(MSVC)
	# todo : define it
endif(MSVC)

### add common define
if(UNIX)
	add_definitions(-DUNIX)
endif(UNIX)

if(MINGW OR MSVC)
	add_definitions(-DWIN32)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_definitions(-DDEBUG)
	add_definitions(-DASAR_SA1ADDRMODE)
else()
	add_definitions(-DRELEASE -DNDEBUG)
	add_definitions(-DASAR_SA1ADDRMODE)
endif()

### visual studio directory config
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "bolib")

### Check include files
check_include_files(cstdint HAVE_CSTDINT)
check_include_files(stdbool.h HAVE_STDBOOL_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(sys/types.h.h HAVE_SYS_TYPES_H)

### Generate compiler.h
set(BUILD_DIR "${CMAKE_CURRENT_LIST_DIR}/build")
if(UNIX OR MINGW)
	execute_process(
		COMMAND sh "${BUILD_DIR}/ccname.sh" "${CMAKE_C_COMPILER}"
		OUTPUT_VARIABLE BO_C_COMPILER
		)
elseif(MSVC)
	execute_process(
		COMMAND "${BUILD_DIR}/ccname.bat" "${CMAKE_C_COMPILER}"
		OUTPUT_VARIABLE BO_C_COMPILER
		)
endif()
set(BO_C_COMPILER_VERSION ${CMAKE_C_COMPILER_VERSION})
configure_file("${PROJECT_SOURCE_DIR}/include/compiler.h.in" "${PROJECT_BINARY_DIR}/compiler.h")
configure_file("${PROJECT_SOURCE_DIR}/include/int_type.h.in" "${PROJECT_BINARY_DIR}/int_type.h")

### build
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.c")
add_library(bolib STATIC ${SRC_FILES})
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(bolib PRIVATE  ${INCROOT} ${INCROOT}/common ${INCROOT}/file "${PROJECT_BINARY_DIR}")

