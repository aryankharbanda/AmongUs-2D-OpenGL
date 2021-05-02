#include "obstacle.h"
#include "main.h"

Obstacle::Obstacle(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    float r = 0.4;
    float root2 = 1.414;
    this->show = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0,0,0,
        r,0,0,
        r/root2,r/root2,0,
        
        0,0,0,
        r/root2,r/root2,0,
        0,r,0,
        
        0,0,0,
        0,r,0,
        -r/root2,r/root2,0,

        0,0,0,
        -r/root2,r/root2,0,
        -r,0,0,

        0,0,0,
        r,0,0,
        r/root2,-r/root2,0,
        
        0,0,0,
        r/root2,-r/root2,0,
        0,-r,0,
        
        0,0,0,
        0,-r,0,
        -r/root2,-r/root2,0,

        0,0,0,
        -r/root2,-r/root2,0,
        -r,0,0,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 3*8, vertex_buffer_data, COLOR_BLACK, GL_FILL);

    float len = 0.06;
    static const GLfloat vertex_buffer_data2[] = {
        r/(root2*2),r/(root2*2),0,
        3*r/(root2*2)-len,3*r/(root2*2),0,
        3*r/(root2*2)+len,3*r/(root2*2),0,
    };
    this->object[1] = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_GOLD, GL_FILL);

}

void Obstacle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Obstacle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Obstacle::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

