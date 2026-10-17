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


log_pkg("SDL3")
find_package(SDL3 3.4.18)

if(STATIC_BUILD)
    set(SDL_STATIC "SDL_STATIC ON")
else()
    set(SDL_STATIC "")
endif()

if(NOT SDL3_FOUND)
    message(WARNING "Since SDL3 wasn't found in your device, we will install it ourselves")
    CPMAddPackage(
        NAME SDL3
        VERSION 3.4.18
        URL https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/SDL3-3.4.18.tar.gz
        URL_HASH SHA256=9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3
        OPTIONS "${SDL_STATIC}"
    )
endif()

log_pkg("imgui")

CPMAddPackage(
    NAME imgui
    VERSION 1.92.9b-docking
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.92.9b-docking.zip
    URL_HASH SHA256=0434445157a575f452ff0f2d1681fdd90ea8939e0c6983e6f8e47c51fba1bccd
    DOWNLOAD_ONLY YES
)

if(imgui_ADDED)
    file(
        GLOB
        imgui_sources
        ${imgui_SOURCE_DIR}/*.cpp
        ${imgui_SOURCE_DIR}/*.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.h
    )
    add_library(imgui STATIC ${imgui_sources})

    target_compile_definitions(imgui PUBLIC "IMGUI_IMPL_API=extern \"C\"")
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

    if(STATIC_BUILD)
        target_link_libraries(imgui PUBLIC SDL3::SDL3-static)
    else()
        target_link_libraries(imgui PUBLIC SDL3::SDL3-shared)
    endif()
endif()

log_pkg("cimgui")

if(STATIC_BUILD)
    set(CIMGUI_STATIC "IMGUI_STATIC ON")
else()
    set(CIMGUI_STATIC "")
endif()

CPMAddPackage(
    NAME cimgui
    VERSION 1.92.9b
    URL https://github.com/cimgui/cimgui/archive/125f397e0982fe9466eb0a162de547be5efec849.zip
    URL_HASH SHA256=b0cb995a6bd748be4eb7b3caa3b0dc8f6bea73ff75e146c91d8af3bd0b423189
    DOWNLOAD_ONLY YES
    PATCHES patches/cimgui.patch
)

if(cimgui_ADDED)
    file(
        GLOB
        cimgui_sources
        ${cimgui_SOURCE_DIR}/*.cpp
        ${cimgui_SOURCE_DIR}/*.h
    )
    add_library(cimgui STATIC ${cimgui_sources})

    target_compile_definitions(cimgui PUBLIC CIMGUI_USE_SDL3)
    
    target_include_directories(cimgui PUBLIC ${cimgui_SOURCE_DIR})
    target_link_libraries(cimgui PUBLIC imgui)
endif()

log_pkg("cimplot")

CPMAddPackage(
    NAME implot
    VERSION 1.1
    URL https://github.com/epezent/implot/archive/851cdbdd60d1dfb64c23e987969694de0f547a6b.zip
    URL_HASH SHA256=a05d63c38adec2f6ef3ee986cd2fa12c17d4b20c617c30f361c1222b29b82511
    DOWNLOAD_ONLY YES
)

CPMAddPackage(
    NAME cimplot
    VERSION 1.1
    URL https://github.com/cimgui/cimplot/archive/1894cd216ae360e2423762cc52ea5e619abb7cec.zip
    URL_HASH SHA256=dab0d3468d596802266cfdb094491f5092e5ad510f41c6632055c66fa0eafa86
    DOWNLOAD_ONLY YES
    PATCHES patches/cimplot.patch
)

if(cimplot_ADDED)
    file(
        GLOB
        cimplot_sources
        ${cimplot_SOURCE_DIR}/cimplot.cpp
        ${implot_SOURCE_DIR}/implot.h
        ${implot_SOURCE_DIR}/implot_internal.h
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
    )
    add_library(cimplot STATIC ${cimplot_sources})

    target_include_directories(cimplot PUBLIC ${cimplot_SOURCE_DIR} ${implot_SOURCE_DIR})

    target_link_libraries(cimplot PUBLIC cimgui)
    # target_link_libraries(cimplot PUBLIC cimplot cimgui)
endif()
