# Source
add_library(asteroids
    asteroids_game.c
    asteroid.c
    bullet.c
    collision.c
    gui.c
    input.c
    ship.c
)

# Linkage
target_link_libraries(asteroids
    controllers

    pico_stdlib
    pico_multicore
    pico_rand
)
