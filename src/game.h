#ifndef GAME_H
#define GAME_H

// Libraries ------------------------------------------------------------------------------------------------------------------

// Controller Library
#include <controller.h>

// Datatypes ------------------------------------------------------------------------------------------------------------------

typedef int (*gameEntrypoint_t)(controller_t* controllers, uint16_t controllerCount);

#endif // GAME_H
