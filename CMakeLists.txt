cmake_minimum_required(VERSION 2.8)
project(aquestalk_wrapper_win CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32_WINNT=0x601 -fexec-charset=CP932")
add_subdirectory(src)
