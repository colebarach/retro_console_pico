// Pico Retro Console ---------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description:

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy.h>

// Controller Library
#include <controller_nes.h>

// Pico Standard Library
#include <pico/stdlib.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "game.h"

#include "pong/pong_game.h"
#include "asteroids/asteroids_game.h"

// Input / Output -------------------------------------------------------------------------------------------------------------

#define CONTROLLER_0_PIN_SERIAL_DATA  22
#define CONTROLLER_0_PIN_SERIAL_CLOCK 26
#define CONTROLLER_0_PIN_SERIAL_LATCH 27

#define CONTROLLER_1_PIN_SERIAL_DATA  16
#define CONTROLLER_1_PIN_SERIAL_CLOCK 17
#define CONTROLLER_1_PIN_SERIAL_LATCH 18

// Global Data ----------------------------------------------------------------------------------------------------------------

#define GAME_COUNT 2
gameEntrypoint_t games[GAME_COUNT] =
{
    pongEntrypoint,
    asteroidsEntrypoint
};

#define CONTROLLER_COUNT 2
controller_t controllers[CONTROLLER_COUNT];

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main()
{
    // Initialize X-Y library
    xyRendererInitialize();

    // Initialize Controllers
    controllers[0] = controllerNesInitialize(CONTROLLER_0_PIN_SERIAL_DATA, CONTROLLER_0_PIN_SERIAL_CLOCK, CONTROLLER_0_PIN_SERIAL_LATCH);
    controllers[1] = controllerNesInitialize(CONTROLLER_1_PIN_SERIAL_DATA, CONTROLLER_1_PIN_SERIAL_CLOCK, CONTROLLER_1_PIN_SERIAL_LATCH);

    // Select game
    while(true)
    {
        controllerRead(&controllers[0]);

        if(controllers[0].buttonA)
        {
            // Start game
            games[0](controllers, CONTROLLER_COUNT);

            // Clear memory after end
            xyRendererClearStack();
        }
        else if(controllers[0].buttonB)
        {
            // Start game
            games[1](controllers, CONTROLLER_COUNT);

            // Clear memory after end
            xyRendererClearStack();
        }
    }
}
