#include "hud.h"
#include "main.h"

Hud::Hud(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -4,4,0,
        -4,3.5,0, 
        4,3.5,0,

        -4,4,0,
        4,4,0, 
        4,3.5,0,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, COLOR_GREY, GL_FILL);
    
    static const GLfloat vertex_buffer_data2[] = {
        // S
        -3.4,3.9,0, 
        -3.7,3.9,0, 
        -3.7,3.9,0, 
        -3.7,3.75,0, 
        -3.7,3.75,0, 
        -3.4,3.75,0, 
        -3.4,3.75,0, 
        -3.4,3.6,0, 
        -3.4,3.6,0, 
        -3.7,3.6,0, 

        // T1
        -2.5,3.9,0,
        -2.2,3.9,0,
        -2.35,3.9,0,
        -2.35,3.6,0,

        -2.1,3.9,0,
        -2.1,3.6,0,

        // T2
        -0.8,3.9,0,
        -0.5,3.9,0,
        -0.65,3.9,0,
        -0.65,3.6,0,

        -0.4,3.9,0,
        -0.4,3.6,0,
        -0.3,3.9,0,
        -0.3,3.6,0,

        // L
        1,3.9,0,
        1,3.6,0,
        1,3.6,0,
        1.2,3.6,0,

        // T
        2.5,3.9,0,
        2.8,3.9,0,
        2.65,3.9,0,
        2.65,3.6,0,

    };
    this->object[1] = create3DObject(GL_LINES, 2*16, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {
        -1.6,3.9,0,
        -1.3,3.9,0,
        -1.6,3.6,0,
        
        -1.3,3.6,0,
        -1.3,3.9,0,
        -1.6,3.6,0,
    };
    this->object[2] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data3, COLOR_GREEN, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data3, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data4[] = {
        0.2,3.9,0,
        0.5,3.9,0,
        0.2,3.6,0,
        
        0.5,3.6,0,
        0.5,3.9,0,
        0.2,3.6,0,
    };
    this->object[4] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data4, COLOR_GREEN, GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data4, COLOR_RED, GL_FILL);

    static const GLfloat vertex_buffer_data5[] = {
        1.5,3.9,0,
        1.8,3.9,0,
        1.5,3.6,0,
        
        1.8,3.6,0,
        1.8,3.9,0,
        1.5,3.6,0,
    };
    this->object[6] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data5, COLOR_GREEN, GL_FILL);
    this->object[7] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data5, COLOR_RED, GL_FILL);

}

void Hud::draw(glm::mat4 VP, bool b1, bool b2, int light) {
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
    
    if(b1) draw3DObject(this->object[2]);
    else draw3DObject(this->object[3]);

    if(b2) draw3DObject(this->object[4]);
    else draw3DObject(this->object[5]);

    if(light) draw3DObject(this->object[6]);
    else draw3DObject(this->object[7]);
}

void Hud::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Hud::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

