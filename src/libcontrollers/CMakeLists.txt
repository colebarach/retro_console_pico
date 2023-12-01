# Source
add_library(controllers
    controller.c
    controller_nes.c
)

# Linkage
target_link_libraries(controllers
    pico_stdlib
)
