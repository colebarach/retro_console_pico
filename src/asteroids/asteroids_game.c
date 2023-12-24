// Header
#include "asteroids_game.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// X-Y Library
#include <xy_renderer.h>

// Pico Standard Library
#include <pico/stdlib.h>
#include <pico/rand.h>

// Includes -------------------------------------------------------------------------------------------------------------------

#include "gui.h"
#include "input.h"
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "collision.h"

// Game Rules -----------------------------------------------------------------------------------------------------------------

#define SIZE_BULLET_BUFFER        12     // Maximum number of bullet objects.
#define SIZE_ASTEROID_BUFFER      64     // Maximum number of asteroid objects.

#define SHIP_DEFAULT_LIFE_COUNT   4      // Number of starting lives for the ship.
#define ASTEROID_SPAWN_COUNT      7      // Number of asteroids to spawn in a wave.

#define POINT_COUNT_ASTEROID_1    100    // Number of points earned for hitting an asteroid of size 1
#define POINT_COUNT_ASTEROID_2    50     // Number of points earned for hitting an asteroid of size 2
#define POINT_COUNT_ASTEROID_3    20     // Number of points earned for hitting an asteroid of size 3

// Global Data ----------------------------------------------------------------------------------------------------------------
// - This data must be global due to the limitations of the Pico's memory. If this data is declared locally, the arrays cannot
//   exceed 4096 bytes,

ship_t         ship;                           // Ship object, controlled by player.
scoreCounter_t score;                          // Score counter object, displays current player score.
lifeCounter_t  lives;                          // Life counter object, displays current lives remaining.

asteroid_t asteroids[SIZE_ASTEROID_BUFFER];    // Array of asteroid objects, new objects are created from this buffer.
bullet_t   bullets[SIZE_BULLET_BUFFER];        // Array of bullet objects, new objects are created from this buffer.

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int asteroidsEntrypoint(controller_t* controllers, uint16_t controllerCount)
{
    // Validate controller setup
    if(controllerCount == 0)   return -1;
    if(controllers == NULL)    return -1;

    controller_t* controller = &controllers[0];

    // Play Loop --------------------------------------------------------------------------------------------------------------

    while(true)
    {
        // Game Data ----------------------------------------------------------------------------------------------------------

        int8_t   asteroidSpeed = 1;
        int8_t   playerLives   = SHIP_DEFAULT_LIFE_COUNT;
        uint32_t playerScore   = 0;

        // Objects ------------------------------------------------------------------------------------------------------------

        shipInitialize(&ship, xyScreenWidth() / 2.0f - SHIP_CENTER_OF_MASS_X, xyScreenHeight() / 2.0f - SHIP_CENTER_OF_MASS_Y);
        scoreInitialize(&score, 0x00, 0xEC);
        lifeInitialize(&lives,  0x9F, 0xEC);
        bulletBufferInitialize(bullets, SIZE_BULLET_BUFFER);
        asteroidBufferInitialize(asteroids, SIZE_ASTEROID_BUFFER);

        // Spawn initial asteroids
        for(uint16_t index = 0; index < ASTEROID_SPAWN_COUNT; ++index)
        {
            asteroidBufferSpawn(asteroids, SIZE_ASTEROID_BUFFER, -1, -1, 0.0f, xyScreenWidth(), 0.0f, xyScreenHeight());
        }

        // Event Loop ---------------------------------------------------------------------------------------------------------

        while(true)
        {
            // Get input
            inputGet(controller, &ship, bullets, SIZE_BULLET_BUFFER);

            // TODO: Clean integration
            if(controller->buttonSelect) return 0;

            // Update objects
            shipUpdate(&ship);
            scoreUpdate(&score, playerScore);
            lifeUpdate(&lives,  playerLives);
            bulletBufferUpdate(bullets, SIZE_BULLET_BUFFER);
            asteroidBufferUpdate(asteroids, SIZE_ASTEROID_BUFFER);

            // Check collisions
            int16_t bulletIndex = 0;
            int16_t asteroidIndex = 0;
            while(collideBuffersBulletAsteroid(bullets, SIZE_BULLET_BUFFER, asteroids, SIZE_ASTEROID_BUFFER, &bulletIndex, &asteroidIndex))
            {
                uint32_t playerScorePrevious = playerScore;

                // Update player score based on asteroid size
                if(asteroids[asteroidIndex].size == 1)
                {
                    playerScore += POINT_COUNT_ASTEROID_1;
                }
                else if(asteroids[asteroidIndex].size == 2)
                {
                    playerScore += POINT_COUNT_ASTEROID_2;
                }
                else
                {
                    playerScore += POINT_COUNT_ASTEROID_3;
                }

                // If score crosses 10000 mark, add a new life
                if(playerScore / 10000 > playerScorePrevious / 10000)
                {
                    ++playerLives;
                }

                // Remove offendors
                bulletBufferRemove(bullets, SIZE_BULLET_BUFFER, bulletIndex);
                asteroidBufferSplit(asteroids, SIZE_ASTEROID_BUFFER, asteroidIndex);
            }

            asteroidIndex = 0;
            if(collideBufferShipAsteroid(&ship, asteroids, SIZE_ASTEROID_BUFFER, &asteroidIndex))
            {
                // Remove the offending asteroid
                asteroidBufferRemove(asteroids, SIZE_ASTEROID_BUFFER, asteroidIndex);

                // Remove a player life
                --playerLives;

                // Reset game if out of lives
                if(playerLives < 0) break;

                // Respawn player otherwise
                shipRespawn(&ship);
            }

            // Check for no remaining asteroids
            if(asteroidBufferCountActive(asteroids, SIZE_ASTEROID_BUFFER) == 0)
            {
                for(uint16_t index = 0; index < ASTEROID_SPAWN_COUNT; ++index)
                {
                    if(asteroidSpeed < 8) ++asteroidSpeed;
                    asteroidBufferSpawn(asteroids, SIZE_ASTEROID_BUFFER, -1, asteroidSpeed, 0.0f, xyScreenWidth(), 0.0f, xyScreenHeight());
                }
            }

            // Render objects
            shipRender(&ship);
            bulletBufferRender(bullets, SIZE_BULLET_BUFFER);
            asteroidBufferRender(asteroids, SIZE_ASTEROID_BUFFER);

            // Event loop period
            sleep_ms(30);
        }

        // Clear the render stack for reset
        xyRendererClear();
    }
}
