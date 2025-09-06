#ifndef GAMEPAD_H
#define GAMEPAD_H


struct GamePad {
    float direction_up;
    float direction_right;
    float direction_down;
    float direction_left;
    bool button_a;
    bool button_b;

    GamePad()
        : direction_up(0),
          direction_right(0),
          direction_down(0),
          direction_left(0),
          button_a(false),
          button_b(false) {}
};


#endif //GAMEPAD_H
