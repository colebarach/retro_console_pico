// Header
#include "input.h"

// Function Definitions -------------------------------------------------------------------------------------------------------

void inputGet(controller_t* controller, ship_t* playerShip, bullet_t* bulletBuffer, uint16_t bulletBufferSize)
{
    // Get controller input
    controllerRead(controller);

    // Get vertical input
    if(controller->buttonB || controller->buttonUp)
    {
        // Move forward
        playerShip->velocityX += SHIP_ACCELERATION_Y * cosf(playerShip->rotation);
        playerShip->velocityY += SHIP_ACCELERATION_Y * sinf(playerShip->rotation);
        playerShip->accelerating = true;
    }
    else
    {
        playerShip->accelerating = false;
    }

    // Get horizontal input
    if(controller->buttonLeft)
    {
        // Turn left
        playerShip->angularVelocity += SHIP_ANGULAR_ACCELERATION;
    }
    else if(controller->buttonRight)
    {
        // Turn right
        playerShip->angularVelocity -= SHIP_ANGULAR_ACCELERATION;
    }

    // Get shoot input
    if(controller->buttonA)
    {
        if(playerShip->reloaded)
        {
            playerShip->reloaded = false;
            bulletBufferSpawn(bulletBuffer, bulletBufferSize, playerShip->colliderGunX + playerShip->positionX, playerShip->colliderGunY + playerShip->positionY, playerShip->rotation, BULLET_VELOCITY);
        }
    }
    else
    {
        playerShip->reloaded = true;
    }
}
