/*
##### exemple code JoystickDirection #####
#          Developed by Baramex         #
### github: https://github.com/baramex ###

Licence: lgpl-3.0
*/

//include library
#include <JoystickDirection.h>

//							 vrx, vry, sw, ?ground, ?positive
JoystickDirection myJoystick(A2, A3, A4, /*optional*/ A0, /*optional*/ A1);

void setup() {
	//init pinMode
	myJoystick.Init();

	//init Serial
	Serial.begin(9600);

	Serial.println("##### exemple code JoystickDirection #####\n#         Developped by Baramex          #\n### github: https://github.com/baramex ###");
}

void loop() {
	//directionToString() to get direction in string

	//GetLowerDirection() to CENTER, RIGHT, LEFT, TOP, BOTTOM
	Serial.print("Soft direction: " + directionToString(myJoystick.GetLowerDirection()) + " -- ");

	//GetFullDirection() to CENTER, RIGHT, LEFT, TOP, BOTTOM, RIGHT_BOTTOM, RIGHT_TOP, LEFT_BOTTOM, LEFT_TOP
	Serial.print("Full direction: " + directionToString(myJoystick.GetFullDirection()) + " -- ");

	//IsPressed() to get SW button
	Serial.println("Is pressed: " + (String)(myJoystick.IsPressed() ? "TRUE" : "FALSE"));

	delay(500);
}