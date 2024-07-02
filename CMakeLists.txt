# Need CMake 3.28.0
cmake_minimum_required (VERSION 3.28.0)

# This is the name of the repository
project ("circular buffer")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Set compiler warnings
if(MSVC)
    # TODO
else()

    # For clang
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic -Weverything -Wno-declaration-after-statement -Ofast")

    # For GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic -Wno-declaration-after-statement -O3")
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()
# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()


# Add the circular buffer project
if ( NOT "${HAS_CIRCULAR_BUFFER}")

    # Log
    message("[circular buffer] Adding circular buffer project")

    set (CIRCULAR_BUFFER_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the circular buffer project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_CIRCULAR_BUFFER true PARENT_SCOPE)
        set(CIRCULAR_BUFFER_INCLUDE_DIR ${CIRCULAR_BUFFER_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to the example program.
add_executable (circular_buffer_example "main.c")
add_dependencies(circular_buffer_example circular_buffer)
target_include_directories(circular_buffer_example PUBLIC ${CIRCULAR_BUFFER_INCLUDE_DIR})
target_link_libraries(circular_buffer_example circular_buffer)

# Add source to the tester program.
add_executable (circular_buffer_test "circular_buffer_test.c")
add_dependencies(circular_buffer_test circular_buffer sync log)
target_include_directories(circular_buffer_test PUBLIC ${CIRCULAR_BUFFER_INCLUDE_DIR} ${LOG_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(circular_buffer_test circular_buffer sync log)

# Add source to this project's library
add_library (circular_buffer SHARED "circular_buffer.c")
add_dependencies(circular_buffer sync)
target_include_directories(circular_buffer PUBLIC ${CIRCULAR_BUFFER_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(circular_buffer sync)
