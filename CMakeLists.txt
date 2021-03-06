cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

project(corecommon)

find_package(PkgConfig REQUIRED)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_library(corecommon ${SRC})

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_compile_definitions(BUILD_DEBUG)
endif ()

enable_testing()

file(GLOB TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

foreach(TEST ${TESTS})
	get_filename_component(NAME ${TEST} NAME_WLE)
	add_executable(${NAME} ${TEST})
	add_test(${NAME} ${NAME})

	add_dependencies(${NAME} corecommon)
	target_link_libraries(${NAME} corecommon)
endforeach()

if (graphics)
    add_library(graphics ${CMAKE_CURRENT_SOURCE_DIR}/graphics/graphics.cpp)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/graphics)
    add_dependencies(graphics corecommon)

    find_package(OpenGL REQUIRED)
    find_package(Freetype REQUIRED)

    pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

    target_include_directories(graphics PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(graphics PUBLIC PkgConfig::SDL2 ${OPENGL_LIBRARY} ${FREETYPE_LIBRARY})
endif()

if (server)
    add_library(server ${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/server)
    add_dependencies(server corecommon)

    find_library(LIBEVENT libevent.a)
    find_library(LIBEVENT_PTHREADS libevent_pthreads.a)

    find_package(OpenSSL REQUIRED)

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    target_link_libraries(server PUBLIC corecommon ${LIBEVENT} ${LIBEVENT_PTHREADS} ${OPENSSL_CRYPTO_LIBRARY} Threads::Threads)
    target_include_directories(server PUBLIC ${OPENSSL_INCLUDE_DIR})
endif()
