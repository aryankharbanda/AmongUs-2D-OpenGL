#include "main.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle {
public:
    Obstacle() {}
    Obstacle(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    float len;
    bool show;
private:
    VAO *object[2];
};

#endif
