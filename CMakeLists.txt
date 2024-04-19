#  @file CMakeLists.txt
#  Defination of all executable files
# 
#  @author Nisha Jagtap <jagtapnisha2001@gmail.com>
# 
#  (C)2024 Zeus Numerix Pvt. Ltd. All rights reserved.
#  http://www.zeusnumerix.com/

cmake_minimum_required( VERSION 3.28.3 )

Project( "combine_converter" )

## custom settings #############################################################

file( TO_CMAKE_PATH "$ENV{EXTRA_INCLUDE_PATHS}" EXTRA_INCLUDE_PATHS )
file( TO_CMAKE_PATH "$ENV{EXTRA_LIB_PATHS}" EXTRA_LIB_PATHS )
file( TO_CMAKE_PATH "$ENV{EXTRA_CMAKE_MODULE_PATHS}" EXTRA_CMAKE_MODULE_PATHS )
list( APPEND CMAKE_MODULE_PATH ${EXTRA_CMAKE_MODULE_PATHS} )

include_directories(
    ${EXTRA_INCLUDE_PATHS}
)

add_executable( ucon main.cpp )