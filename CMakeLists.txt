cmake_minimum_required(VERSION 3.0)

project(caps2return)

add_executable(caps2return caps2return.c)
target_compile_options(caps2return PRIVATE -Wall -Wextra)

install(TARGETS caps2return RUNTIME DESTINATION bin)
