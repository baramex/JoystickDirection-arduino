#ifndef JOYSTICKDIRECTION_H
#define JOYSTICKDIRECTION_H

#include <Arduino.h>

static const float center = 0.5f;

class JoystickPins {
public:
    uint8_t ground;
    uint8_t positive;
    uint8_t vrx;
    uint8_t vry;
    uint8_t sw;
};

enum class Direction {
    TOP = 1,
    BOTTOM = 2,
    LEFT = 3,
    RIGHT = 4,
    CENTER = 5,
    TOP_LEFT = 6,
    TOP_RIGHT = 7,
    BOTTOM_LEFT = 8,
    BOTTOM_RIGHT = 9,
    NOT_FOUNDED = NULL
};

String directionToString(Direction direction);

class JoystickDirection {
public:
    JoystickDirection(uint8_t vrx, uint8_t vry, uint8_t sw, uint8_t ground, uint8_t positive);
    Direction GetLowerDirection();
    Direction GetFullDirection();
    bool IsPressed();
    JoystickPins GetPins();
    float GetX();
    float GetY();
    void SetXCorrection(float correction);
    void SetYCorrection(float correction);
    void Init();

private:
    float xCorrection = 0.0f;
    float yCorrection = 0.0f;
    bool between(float val, float min, float max);
    JoystickPins pins;
    bool isInit = false;
};

#endif