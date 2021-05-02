#include "main.h"

#ifndef OVER_H
#define OVER_H


class Over {
public:
    Over() {}
    Over(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, bool b1);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object[3];
};

#endif
