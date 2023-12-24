#ifndef PONG_GAME_H
#define PONG_GAME_H

// Pong Game ------------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Implementation of the videogame 'pong'.
//
// To do:
// - Ball freaks out when paddle moves into it from top / bottom.

// Libraries ------------------------------------------------------------------------------------------------------------------

// Controller Library
#include <controller.h>

// Entrypoint -----------------------------------------------------------------------------------------------------------------

// Pong Entrypoint
// - TODO:
// - Must conform to the 'gameEntrypoint_t' form defined in 'game.h'
int pongEntrypoint(controller_t* controllers, uint16_t controllerCount);

#endif // PONG_GAME_H
