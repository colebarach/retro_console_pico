#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

// Asteroids Game -------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Implementation of the videogame 'asteroids'.
//
// To do:
// - Give player invincibility frames on respawn.
// - Object boundaries are currently hard-coded, they should be variable for different screen sizes.
// - Asteroids of size 0 are removed, should really shift sizes down [0, 1, 2]
// - Does global data need renamed to avoid naming-collisions? If so, things are going to get weird.

// Libraries ------------------------------------------------------------------------------------------------------------------

// Controller Library
#include <controller.h>

// Entrypoint -----------------------------------------------------------------------------------------------------------------

// Asteroids Entrypoint
// - Call to start the game, using the specified controller.
// - Will return when the game has finished.
// - Requires at least 1 valid controller in the contoller array.
// - Must conform to the 'gameEntrypoint_t' form as defined in 'game.h'
int asteroidsEntrypoint(controller_t* controllers, uint16_t controllerCount);

#endif // ASTEROIDS_GAME_H
