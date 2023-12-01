# Source
add_library(pong
    pong_game.c
)

# Linkage
target_link_libraries(pong
    controllers

    pico_stdlib
    pico_multicore
)
