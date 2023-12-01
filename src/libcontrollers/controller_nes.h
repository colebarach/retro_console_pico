#ifndef CONTROLLER_NES_H
#define CONTROLLER_NES_H

// NES Controller -------------------------------------------------------------------------------------------------------------
//
// Author: Cole Barach
//
// Description: Bit-banging implementation of an interface for the Nintendo Entertainment System controllers. Each controller
//   has 8 buttons. The controllers use a modified version of SPI to communicate, acting as a secondary device. The layout of
//   the controller and the pinout of the connector is given below.
//
// NES Controller Button Naming Scheme:
// ___________________________________
// |                                 |   0 - 'A'       4 - Up
// |   4                             |   1 - 'B'       5 - Down
// | 6   7   Select  Start   1  0    |   2 - Select    6 - Left
// |   5       2       3     B  A    |   3 - Start     7 - Right
// |_________________________________|
//
// NES Controller Female Connector (viewed with cable facing away):
//  _______
// /    7 |    1 - VCC                   5 - Serial latch
// | 1  6 |    2 - No connection         6 - Serial clock
// | 2  5 |    3 - No connection         7 - Ground
// | 3  4 |    4 - Serial data out
// |______|
//
// NES Controller Protocol: As mentioned previously, the NES controller uses a modified version of SPI. The only difference
//   between the NES's protocol and SPI is that the communication is started using a latch signal. The latch signal is then
//   followed by 7 clock pulses. A timing diagram for the communication is listed below.
//
//   NES Controller Timing Diagram:
//              ____
//     Latch: __|  |____________________________________________
//                    ____  ____  ____  ____  ____  ____  ____
//     Clock: ________|  |__|  |__|  |__|  |__|  |__|  |__|  |__
//              ________________________________________________
//     Data:  __| D0  | D1  | D2  | D3  | D4  | D5  | D6  | D7
//
//   Each bit of the data byte indicates whether the correlating button is held down or not. If a bit is high, then the
//   corresponding button is not pressed, if the bit is low, the corresponding button is pressed. Each bit maps directly to
//   the buttons in the order they are named above (I.E. D0 ~ Button 0).
//
//   According to the datasheet for the CD4021 shift register (the IC used by the controllers), the clock frequency may vary
//   from [0Hz, 2.5MHz], although this is dependent on the supply voltage. In this implementation, 25kHz is chosen, although
//   this may be modified in the source file.
//
//   The CD4021 may be powered by any voltage in the range of [3V, 15V], in this case 3.3V was chosen for convenience.
//
// References:
// - https://www.allaboutcircuits.com/projects/nes-controller-interface-with-an-arduino-uno/

// Includes -------------------------------------------------------------------------------------------------------------------

#include "controller.h"

// Functions ------------------------------------------------------------------------------------------------------------------

// Initialize NES Controller
// - Call to initialize the required inputs and outputs for the controller.
// - Returns a handler for the controller.
controller_t controllerNesInitialize(uint16_t pinSerialData, uint16_t pinSerialClock, uint16_t pinSerialLatch);

// Read NES Controller Input
// - Call to get the input for the given NES controller.
// - Writes current input into the controllers's input parameters.
// - Will block until the input is available.
// - Must conform to the 'controllerReadFunction_t' form defined in 'controllers.h'
void controllerNesRead(controller_t* controller);

#endif // CONTROLLER_NES_H
