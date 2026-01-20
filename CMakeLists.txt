cmake_minimum_required(VERSION 3.10.0)
project(Hospital VERSION 0.1.0 LANGUAGES C)
# Set the C standard to GNU11 for the entire project
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON) # This enables gnu11 extensions


add_executable(Hospital Main.c TempMenu.c pLine.c pTree.c)


