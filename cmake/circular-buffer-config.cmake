# Circular buffer CMake configuration file:
# This file is meant to be placed in a cmake subfolder of CIRCULAR_BUFFER-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(CIRCULAR_BUFFER PROPERTIES
    URL "https://g10.app/status/#abstract_data_ii"
    DESCRIPTION "circular_buffer ADT"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(CIRCULAR_BUFFER_FOUND TRUE)

# For compatibility with autotools CIRCULAR_BUFFER-config.cmake, provide CIRCULAR_BUFFER_* variables.

set_and_check(CIRCULAR_BUFFER_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(CIRCULAR_BUFFER_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(CIRCULAR_BUFFER_INCLUDE_DIR  "${CIRCULAR_BUFFER_PREFIX}/include")
set(CIRCULAR_BUFFER_INCLUDE_DIRS           "${CIRCULAR_BUFFER_INCLUDE_DIR}")
set_and_check(CIRCULAR_BUFFER_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(CIRCULAR_BUFFER_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(CIRCULAR_BUFFER_LIBRARIES circular_buffer::circular_buffer)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated CIRCULAR_BUFFER-target.cmake files.

set(_CIRCULAR_BUFFER_library     "${CIRCULAR_BUFFER_LIBDIR}/circular_buffer.lib")
set(_CIRCULAR_BUFFER_dll_library "${CIRCULAR_BUFFER_BINDIR}/circular_buffer.dll")
if(EXISTS "${_CIRCULAR_BUFFER_library}" AND EXISTS "${_CIRCULAR_BUFFER_dll_library}")
    if(NOT TARGET circular_buffer::circular_buffer)
        add_library(circular_buffer::circular_buffer SHARED IMPORTED)
        set_target_properties(circular_buffer::circular_buffer
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${CIRCULAR_BUFFER_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_CIRCULAR_BUFFER_library}"
                IMPORTED_LOCATION "${_CIRCULAR_BUFFER_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "CIRCULAR_BUFFER_SHARED"
                INTERFACE_CIRCULAR_BUFFER_SHARED "ON"
        )
    endif()
    set(CIRCULAR_BUFFER_CIRCULAR_BUFFER_FOUND TRUE)
else()
    set(CIRCULAR_BUFFER_CIRCULAR_BUFFER_FOUND FALSE)
endif()
unset(_CIRCULAR_BUFFER_library)
unset(_CIRCULAR_BUFFER_dll_library)

check_required_components(CIRCULAR_BUFFER)
