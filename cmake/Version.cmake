find_package(Git)

if(Git_FOUND AND GIT_EXECUTABLE)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
        OUTPUT_VARIABLE PROJECT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

if("${PROJECT_VERSION}" STREQUAL "")
    set(PROJECT_VERSION "v0.0.0-unknown")

    message(
        WARNING
            "Failed to determine version from Git tags. Using default version \"${PROJECT_VERSION}\"."
    )
endif()

message(STATUS "Version: ${PROJECT_VERSION}")
