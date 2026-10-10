include(cmake/CPM.cmake)

set(CMAKE_MESSAGE_LOG_LEVEL WARNING) # because useless log stuff

# prints the pkg name to console
function(log_pkg)
    set(CMAKE_MESSAGE_LOG_LEVEL STATUS)
    message(STATUS "Installing - ${ARGV}")
    set(CMAKE_MESSAGE_LOG_LEVEL WARNING)
endfunction()

# I use tar.gz archives and sha256 instead of git because when I need to test my code in windows git
# clone drains all my internet. I have limited daily. Also GIT_SHALLOW doesn't work how it sould
# even after I give it proper tags or even commit.


# ############################ SDL ###############################
log_pkg("SDL3")

find_package(SDL3 3.2.8)

if(NOT SDL3_FOUND)
    message(WARNING "Since SDL3 wasn't found in your device, we will install it ourselves")
    CPMAddPackage(
        NAME SDL3
        VERSION 3.2.8
        URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.8/SDL3-3.2.8.tar.gz
        URL_HASH SHA256=13388fabb361de768ecdf2b65e52bb27d1054cae6ccb6942ba926e378e00db03
    )
endif()
