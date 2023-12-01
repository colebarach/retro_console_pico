#ifndef CONTROLLER_H
#define CONTROLLER_H

// Controller -----------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Basic library for implementing a variety of controllers as input devices. Uses a basic controller object which
//   a variety of devices may use, mimicing polymorphism.

// Libraries ------------------------------------------------------------------------------------------------------------------

// C Standard Libraries
#include <stdint.h>
#include <stdbool.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define CONTROLLER_PIN_COUNT_MAX 8       // Maximum number of pins a single controller may use.

// Datatypes ------------------------------------------------------------------------------------------------------------------

// Controller forward declaration and typedef
struct controllerObject;
typedef struct controllerObject controller_t;

// Controller Read Function
// - Function used to read input into the controller
typedef void (*controllerReadFunction_t)(controller_t* controller);

// Controller Object
struct controllerObject
{
    // Inputs
    bool buttonA;                        // Indicates whether the 'A' button is held down.
    bool buttonB;                        // Indicates whether the 'B' button is held down.
    bool buttonLeft;                     // Indicates whether the left button is held down.
    bool buttonRight;                    // Indicates whether the right button is held down.
    bool buttonUp;                       // Indicates whether the up button is held down.
    bool buttonDown;                     // Indicates whether the down button is held down.
    bool buttonStart;                    // Indicates whether the start button is held down.
    bool buttonSelect;                   // Indicates whether the select button is held down.

    // Functions
    controllerReadFunction_t read;       // Function to read input into the controller's input parameters.

    // Pin mapping
    uint8_t pins[CONTROLLER_PIN_COUNT_MAX];                    // Array of utilized pin numbers (specific to device type).
    uint16_t pinCount;                                         // Number of elements being used in the 'pins' array.
};

// Functions ------------------------------------------------------------------------------------------------------------------

void controllerRead(controller_t* controller);

#endif // CONTROLLER_H
