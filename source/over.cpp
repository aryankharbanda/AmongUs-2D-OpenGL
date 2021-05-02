#include "over.h"
#include "main.h"

Over::Over(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -4,4,0,
        -4,-4,0, 
        4,4,0,

        4,4,0,
        -4,-4,0, 
        4,4,0,
    };
    this->object[0] = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, COLOR_SEAGREEN, GL_FILL);
    
    static const GLfloat vertex_buffer_data2[] = {
        -2,1,0, 
        -1,-1,0,
        -1,-1,0,
        0,1,0,
        0,1,0,
        1,-1,0,
        1,-1,0,
        2,1,0,

    };
    this->object[1] = create3DObject(GL_LINES, 2*4, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {
        -1,1,0,
        -1,-1,0,
        -1,-1,0,
        1,-1,0,

    };
    this->object[2] = create3DObject(GL_LINES, 2*2, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);


}

void Over::draw(glm::mat4 VP, bool b1) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->object[0]);
    
    if(b1) draw3DObject(this->object[1]);
    else draw3DObject(this->object[2]);

}

void Over::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Over::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

