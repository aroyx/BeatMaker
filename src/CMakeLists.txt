add_executable(${PROJECT_NAME} 
    main.c
    global.c
    global.h
    ui.c
    ui.h
    time.c
    time.h
    files.c
    files.h
    log.c
    log.h
    window/window.c
    window/window.h
)

if(STATIC_BUILD)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-shared)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE cimgui cimplot)
target_compile_definitions(${PROJECT_NAME}  PUBLIC CIMGUI_DEFINE_ENUMS_AND_STRUCTS)

if(WIN32)
    if(MSVC)
        set_property(
            DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME}
        )

        # no console in windows
        set_target_properties(
            ${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS
                                               "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
        )
    endif()

    if(!STATIC_BUILD)
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        )
    endif()
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

if(STATIC_BUILD)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_link_options(${PROJECT_NAME} PRIVATE "-static-libstdc++" "-static-libgcc")
    endif()
endif()
