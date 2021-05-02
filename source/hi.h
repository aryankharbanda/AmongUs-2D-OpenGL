#include "main.h"

#ifndef HI_H
#define HI_H


class Hi {
public:
    Hi() {}
    Hi(float x, float y);
    glm::vec3 position;
    float rotation;
    int slab;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double radius;
private:
    VAO *object;
};

#endif 