/*
#####  JoystickDirection lib arduino #####
#          Developed by Baramex          #
### github: https://github.com/baramex ###
*/

#include "JoystickDirection.h"

String directionToString(Direction direction) {
    switch (direction) {
    case Direction::TOP: return "TOP";
    case Direction::BOTTOM: return "BOTTOM";
    case Direction::LEFT: return "LEFT";
    case Direction::RIGHT: return "RIGHT";
    case Direction::CENTER: return "CENTER";
    case Direction::TOP_LEFT: return "TOP_LEFT";
    case Direction::TOP_RIGHT: return "TOP_RIGHT";
    case Direction::BOTTOM_LEFT: return "BOTTOM_LEFT";
    case Direction::BOTTOM_RIGHT: return "BOTTOM_RIGHT";
    default: return "NOT_FOUNDED";
    }
}

JoystickDirection::JoystickDirection(uint8_t vrx, uint8_t vry, uint8_t sw, uint8_t ground = -1, uint8_t positive = -1) {
    pins.vrx = vrx;
    pins.vry = vry;
    pins.sw = sw;

    pins.ground = ground;
    pins.positive = positive;
}
void JoystickDirection::Init() {
    if (pins.ground != -1) {
        pinMode(pins.ground, OUTPUT);
        digitalWrite(pins.ground, LOW);
    }

    if (pins.positive != -1) {
        pinMode(pins.positive, OUTPUT);
        digitalWrite(pins.positive, HIGH);
    }

    pinMode(pins.vrx, INPUT);
    pinMode(pins.vry, INPUT);
    pinMode(pins.sw, INPUT);

    digitalWrite(pins.sw, HIGH);

    isInit = true;
}
Direction JoystickDirection::GetLowerDirection() {
    if (!isInit) return Direction::NOT_FOUNDED;
    float x = GetX();
    float y = GetY();

    if (between(x, -center, center) && between(y, -center, center)) {
        return Direction::CENTER;
    }

    float leftDif = x + 1;
    float rightDif = 1 - x;
    float topDif = y + 1;
    float bottomDif = 1 - y;

    if (between(x, -1, -center) && leftDif < topDif && leftDif < bottomDif) {
        return Direction::LEFT;
    }
    if (between(x, center, 1) && rightDif < topDif && rightDif < bottomDif) {
        return Direction::RIGHT;
    }
    if (between(y, -1, -center)) {
        return Direction::TOP;
    }
    if (between(y, center, 1)) {
        return Direction::BOTTOM;
    }

    return Direction::NOT_FOUNDED;
}
Direction JoystickDirection::GetFullDirection() {
    if (!isInit) return Direction::NOT_FOUNDED;
    float x = GetX();
    float y = GetY();

    if (between(x, -center, center) && between(y, -center, center)) {
        return Direction::CENTER;
    }

    String direct = "";
    if (between(x, -1, -center)) {
        direct += "left";
    }
    if (between(x, center, 1)) {
        direct += "right";
    }
    if (between(y, -1, -center)) {
        direct += "top";
    }
    if (between(y, center, 1)) {
        direct += "bottom";
    }

    if (direct == "left") {
        return Direction::LEFT;
    }
    else if (direct == "right") {
        return Direction::RIGHT;
    }
    else if (direct == "top") {
        return Direction::TOP;
    }
    else if (direct == "bottom") {
        return Direction::BOTTOM;
    }
    else if (direct == "lefttop") {
        return Direction::TOP_LEFT;
    }
    else if (direct == "leftbottom") {
        return Direction::BOTTOM_LEFT;
    }
    else if (direct == "righttop") {
        return Direction::TOP_RIGHT;
    }
    else if (direct == "rightbottom") {
        return Direction::BOTTOM_RIGHT;
    }

    return Direction::NOT_FOUNDED;
}
bool JoystickDirection::IsPressed() {
    if (!isInit) return false;
    return !digitalRead(pins.sw);
}
JoystickPins JoystickDirection::GetPins() {
    return pins;
}
float JoystickDirection::GetX() {
    if (!isInit) return 0;
    return (float)(map(analogRead(pins.vrx), 0, 1023, -1000, 1000)) / 1000 + xCorrection;
}
float JoystickDirection::GetY() {
    if (!isInit) return 0;
    return (float)(map(analogRead(pins.vry), 0, 1023, -1000, 1000)) / 1000 + yCorrection;
}
void JoystickDirection::SetXCorrection(float correction) {
    if (!isInit) return;
    xCorrection = correction;
}
void JoystickDirection::SetYCorrection(float correction) {
    if (!isInit) return;
    yCorrection = correction;
}

bool JoystickDirection::between(float val, float min, float max) {
    if (!isInit) return false;
    return val > min && val < max;
}