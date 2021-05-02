#include "hi.h"
#include "main.h"

Hi::Hi(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.5;
    this->slab = 0;
    float r = 0.5;
    const double PI=3.14159265358979323846;
    int numPoints=360;

    static GLfloat g_vertex_buffer_data[] = 
    {
        1.0f, 0.0f, 0.0f, 
        1.2f, 0.0f, 0.0f, 
        1.0f, -2.0f, 0.0f,

        1.0f, -2.0f, 0.0f,
        1.2f, 0.0f, 0.0f,
        1.2f, -2.0f, 0.0f,

        -2.2f, 0.0f, 0.0f, 
        -2.0f, 0.0f, 0.0f, 
        -2.2f, -2.0f, 0.0f,

        -2.0f, 0.0f, 0.0f,
        -2.2f, -2.0f, 0.0f,
        -2.0f, -2.0f, 0.0f, 

        -2.0f, -0.8f, 0.0f, 
        -0.5f, -0.8f, 0.0f, 
        -2.0f, -1.0f, 0.0f,

        -0.5f, -1.0f, 0.0f, 
        -0.5f, -0.8f, 0.0f,
        -2.0f, -1.0f, 0.0f,

        -0.5f, 0.0f, 0.0f, 
        -0.3f, 0.0f, 0.0f,
        -0.5f, -2.0f, 0.0f, 

        -0.3f, 0.0f, 0.0f,
        -0.5f, -2.0f, 0.0f,
        -0.3f, -2.0f, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, g_vertex_buffer_data, COLOR_ORANGE, GL_FILL);
}

void Hi::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Hi::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Hi::tick() {
    // this->position.x -= this->speed;
    // if(this->position.x>20)
    //     this->position.x = -10;
    // this->position.y -= speed;
}



