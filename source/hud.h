#include "main.h"

#ifndef HUD_H
#define HUD_H


class Hud {
public:
    Hud() {}
    Hud(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, bool b1, bool b2, int light);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object[8];
};

#endif
