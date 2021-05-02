#include "main.h"

#ifndef BBOX_H
#define BBOX_H


class Bbox {
public:
    Bbox() {}
    Bbox(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif
