cmake_minimum_required(VERSION 4.0...4.4)

project(BeatMaker 
    DESCRIPTION "An application to generate simulation from musical notes"
    LANGUAGES C
)

include(cmake/Initialise.cmake)

message(STATUS "Installing Dependencies...")
include(cmake/InstallDependencies.cmake)

add_subdirectory(src)
