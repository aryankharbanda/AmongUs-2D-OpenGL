#include "main.h"

#ifndef BTN_H
#define BTN_H


class Btn {
public:
    Btn() {}
    Btn(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bool vanish;
    float len;
private:
    VAO *object;
};

#endif
