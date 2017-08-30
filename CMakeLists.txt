#-----------------------------------------------------------
# CMakeList for bolib
#-----------------------------------------------------------

cmake_minimum_required(VERSION 3.1)

### add exe
#macro(Make target)
#	file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.c")
#	set(MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/${target}.c")
#	set(MAIN_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
#	set(_INC "${CMAKE_CURRENT_SOURCE_DIR}/include")
#	set(MAIN_RESOURCE "")
#	if(MINGW OR MSVC)
#		set(MAIN_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/res/${target}.rc")
#	endif()
#	add_executable(${target} ${MAIN_FILE} ${SRC_FILES} ${MAIN_RESOURCE})
#	target_include_directories(${target} PRIVATE ${_INC} ${MAIN_INC} ${C_INC_COMMON} ${C_INC_ASAR} ${C_INC_FILE})
#	if(UNIX)
#	target_link_libraries(${target} "dl" "asar")
#	endif(UNIX)
#endmacro(Make)

### option putout macro
macro(putopt opt)
	message("${opt} = ${${opt}}")
endmacro(putopt)

### add common defines
macro(add_common_define target def)
	set(${target} "${${target}} ${DEFINE_PREFIX}${def}")
endmacro(add_common_define)

### specify build type
set(CMAKE_BUILD_TYPE "Release")

### Visual Studio Solution Name
project(bolib)

###### specify C and C++ compile option
### soecify unix compile option
if(UNIX OR MINGW)
	## define prefix(gcc)
	set(DEFINE_PREFIX "-D")

	## set C Release compile flags
        set(CMAKE_C_FLAGS_RELEASE "-Wall -ansi -Wconversion -O2 -ffunction-sections -fdata-sections")

	## set C Debug compile option
	set(CMAKE_C_FLAGS_DEBUG "-Wall -ansi -Wconversion -Werror -O0 -g")

	## set linker link flag
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s -Wl,--gc-sections")
	set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "-T")
endif()

if(MSVC)
	## define prefix(gcc)
	set(DEFINE_PREFIX "/D")

	# todo : define it
endif(MSVC)

### add common define
if(UNIX)
        add_common_define(CMAKE_C_FLAGS_DEBUG UNIX)
        add_common_define(CMAKE_C_FLAGS_RELEASE UNIX)
endif(UNIX)
if(MINGW OR MSVC)
        add_common_define(CMAKE_C_FLAGS_DEBUG WIN32)
        add_common_define(CMAKE_C_FLAGS_RELEASE WIN32)
endif()
if(CMAKE_BUILD_TYPE MATCHES "Debug")
	add_common_define(CMAKE_C_FLAGS_DEBUG DEBUG)
else()
	add_common_define(CMAKE_C_FLAGS_RELEASE RELEASE)
	add_common_define(CMAKE_C_FLAGS_RELEASE NDEBUG)
endif()

add_common_define(CMAKE_C_FLAGS_DEBUG ASAR_SA1ADDRMODE)
add_common_define(CMAKE_C_FLAGS_RELEASE ASAR_SA1ADDRMODE)

### set C++ option
set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

###### specify C++ command option
if(UNIX OR MINGW)
	## no exception
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
endif()

if(MSVC)
	# todo : define it
endif(MSVC)


### visual studio directory config
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "bolib")

### build
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.c")
add_library(bolib STATIC ${SRC_FILES})
set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(bolib PRIVATE  ${INCROOT} ${INCROOT}/common ${INCROOT}/file)

