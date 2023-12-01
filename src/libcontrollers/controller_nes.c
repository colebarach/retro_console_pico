// Header
#include "controller_nes.h"

// Libraries ------------------------------------------------------------------------------------------------------------------

// Pico Standard Library
#include <pico/stdlib.h>

// Constants ------------------------------------------------------------------------------------------------------------------

#define CLOCK_PERIOD_HALF 20

#define INDEX_PIN_SERIAL_DATA  0
#define INDEX_PIN_SERIAL_CLOCK 1
#define INDEX_PIN_SERIAL_LATCH 2

// Functions ------------------------------------------------------------------------------------------------------------------

controller_t controllerNesInitialize(uint16_t pinSerialData, uint16_t pinSerialClock, uint16_t pinSerialLatch)
{
    controller_t controller;

    // Initialize GPIO
    gpio_init(pinSerialData);
    gpio_init(pinSerialClock);
    gpio_init(pinSerialLatch);

    gpio_set_dir(pinSerialData,  GPIO_IN);
    gpio_set_dir(pinSerialClock, GPIO_OUT);
    gpio_set_dir(pinSerialLatch, GPIO_OUT);

    // Default to no input
    // - Pull-up resistor is not be required for a connected controller, but is for an unconnected controller.
    gpio_pull_up(pinSerialData);

    // Set pin numbers
    controller.pins[INDEX_PIN_SERIAL_DATA]  = pinSerialData;
    controller.pins[INDEX_PIN_SERIAL_CLOCK] = pinSerialClock;
    controller.pins[INDEX_PIN_SERIAL_LATCH] = pinSerialLatch;
    controller.pinCount = 3;

    // Set functions
    controller.read = controllerNesRead;

    // Set default inputs
    controller.buttonA      = false;
    controller.buttonB      = false;
    controller.buttonLeft   = false;
    controller.buttonRight  = false;
    controller.buttonUp     = false;
    controller.buttonDown   = false;
    controller.buttonStart  = false;
    controller.buttonSelect = false;

    return controller;
}

void controllerNesRead(controller_t* controller)
{
    // Send latch signal, sample 'A' button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_LATCH], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonA = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_LATCH], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get 'B' button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonB = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get select button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonSelect = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get start button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonStart = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get up button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonUp = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get down button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonDown = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get left button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonLeft = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);

    // Get right button
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], true);
    sleep_us(CLOCK_PERIOD_HALF);
    controller->buttonRight = !gpio_get(controller->pins[INDEX_PIN_SERIAL_DATA]);
    gpio_put(controller->pins[INDEX_PIN_SERIAL_CLOCK], false);
    sleep_us(CLOCK_PERIOD_HALF);
}
