#include "imposter.h"
#include "main.h"

Imposter::Imposter(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->zoom_fac = 2;
    this->vanish = false;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.8/zoom_fac,.2/zoom_fac,0,
        -1/zoom_fac,.2/zoom_fac,0,
        -1/zoom_fac,-0.8/zoom_fac,0,
        -0.8/zoom_fac,.2/zoom_fac,0,
        -0.8/zoom_fac,-0.8/zoom_fac,0,
        -1/zoom_fac,-0.8/zoom_fac,0,

        // L1
        -0.8/zoom_fac,-0.8/zoom_fac,0,
        -0.8/zoom_fac,-1/zoom_fac,0,
        -0.4/zoom_fac,-0.8/zoom_fac,0,
        -0.4/zoom_fac,-1/zoom_fac,0,
        -0.8/zoom_fac,-1/zoom_fac,0,
        -0.4/zoom_fac,-0.8/zoom_fac,0,

        // L2
        .4/zoom_fac,-0.8/zoom_fac,0,
        .8/zoom_fac,-0.8/zoom_fac,0,
        .4/zoom_fac,-1/zoom_fac,0,
        .8/zoom_fac,-1/zoom_fac,0,
        .8/zoom_fac,-0.8/zoom_fac,0,
        .4/zoom_fac,-1/zoom_fac,0,
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.8/zoom_fac,0.5/zoom_fac,0,
        -0.8/zoom_fac,0.5/zoom_fac,0,
        -0.8/zoom_fac,-0.8/zoom_fac,0,
        0.8/zoom_fac,0.5/zoom_fac,0,
        0.8/zoom_fac,-0.8/zoom_fac,0,
        -0.8/zoom_fac,-0.8/zoom_fac,0,



        // head
        -0.8/zoom_fac,0.5/zoom_fac,0,
        -0.7/zoom_fac,0.8/zoom_fac,0,
        0.8/zoom_fac,0.5/zoom_fac,0,

        -0.7/zoom_fac,0.8/zoom_fac,0,
        -0.3/zoom_fac,0.95/zoom_fac,0,
        0.8/zoom_fac,0.5/zoom_fac,0,

        -0.3/zoom_fac,0.95/zoom_fac,0,
        0.3/zoom_fac,0.95/zoom_fac,0,
        0.8/zoom_fac,0.5/zoom_fac,0,

        0.3/zoom_fac,0.95/zoom_fac,0,
        0.7/zoom_fac,0.8/zoom_fac,0,
        0.8/zoom_fac,0.5/zoom_fac,0,
        
    };
    static const GLfloat goggle[] = {
        0.5/zoom_fac,0.4/zoom_fac,0,
        0.5/zoom_fac,0.65/zoom_fac,0,
        1/zoom_fac,0.65/zoom_fac,0,
    };
    static const GLfloat goggle2[] = {
        1/zoom_fac,0.65/zoom_fac,0,
        1/zoom_fac,0.4/zoom_fac,0,
        0.5/zoom_fac,0.4/zoom_fac,0,
    };

    this->object[0] = create3DObject(GL_TRIANGLES, 3*6, vertex_buffer_data, COLOR_DARKRED, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 3*6, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 3, goggle, COLOR_LIGHTGREY, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 3, goggle2, COLOR_GREY, GL_FILL);
}

void Imposter::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    if(!vanish){
        draw3DObject(this->object[0]);
        draw3DObject(this->object[1]);
        draw3DObject(this->object[2]);
        draw3DObject(this->object[3]);
    }
    
}

void Imposter::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Imposter::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

