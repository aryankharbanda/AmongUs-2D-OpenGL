#include "main.h"
#include "timer.h"
#include "ball.h"
#include "maze.h"
#include "bbox.h"
#include "imposter.h"
#include "btn.h"
#include "coin.h"
#include "obstacle.h"
#include "score.h"
#include "hi.h"
#include "hud.h"
#include "over.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

#define num_bbox 8
#define num_coins 10
#define num_obs 10

int score = 0;
bool powerupactive = false;
bool gameover = false;
bool win = false;

clock_t begintime = clock();

Score scorr[4];
Hi hi;
Hud hud;
Over over;

Ball playa;
Imposter imposter;
Maze maze;
Bbox bbox[num_bbox];
// Bbox bbox;
Btn btnimp;
Btn btnobs;
Coin coins[num_coins];
Obstacle obs[num_obs];

bounding_box_t player_bb;
bounding_box_t imposter_bb;
// bounding_box_t bb_bb;
bounding_box_t bb_bb[num_bbox];
bounding_box_t btnimp_bb;
bounding_box_t btnobs_bb;
bounding_box_t coins_bb[num_coins];
bounding_box_t obs_bb[num_obs];
bounding_box_t exit_bb;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

float eye_x = 0.0f;
float eye_y = 0.0f;
float eye_z = 5.0f;

float tar_x = 0.0f;
float tar_y = 0.0f;
float tar_z = 0.0f;

float speed_playa = 0.1f;
float speed_imposter = 0.03f;

int light = 1;
GLuint     lightID;

int a0, a1, a2, b0, b1, b2, c0, c1, c2, d0, d1, d2, e0, e1, e2, f0, f1, f2, g0, g1, g2;
int a3, b3, c3, d3, e3, f3, g3;
int al, bl, cl, dl, el, fl, gl;
int a4, a5;
int b4, b5;
int c4, c5;
int d4, d5;
int e4, e5;
int f4, f5;
int g4, g5;
int ones, tens, huns, thou;
int onel, tenl;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    glm::vec3 eye ( eye_x, eye_y, eye_z );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (tar_x, tar_y, tar_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(!gameover){
        playa.draw(VP);
        maze.draw(VP);

        ones = score % 10;
        tens = (score / 10) % 10;
        huns = (score / 100) % 10;
        thou = (score / 1000) % 10;

        a0 = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==7 || huns==8 || huns==9) ? 1: 0;
        a1 = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==7 || tens==8 || tens==9) ? 1: 0;
        a2 = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==7 || ones==8 || ones==9) ? 1: 0;

        b0 = (huns==0 || huns==2 || huns==3 || huns==1 || huns==4 || huns==7 || huns==8 || huns==9) ? 1: 0;
        b1 = (tens==0 || tens==2 || tens==3 || tens==1 || tens==4 || tens==7 || tens==8 || tens==9) ? 1: 0;
        b2 = (ones==0 || ones==2 || ones==3 || ones==1 || ones==4 || ones==7 || ones==8 || ones==9) ? 1: 0;

        c0 = (huns==0 || huns==1 || huns==3 || huns==4 || huns==5 || huns==6 || huns==7 || huns == 8 || huns == 9) ? 1: 0;
        c1 = (tens==0 || tens==1 || tens==3 || tens==4 || tens==5 || tens==6 || tens==7 || tens == 8 || tens == 9) ? 1: 0;
        c2 = (ones==0 || ones==1 || ones==3 || ones==4 || ones==5 || ones==6 || ones==7 || ones == 8 || ones == 9) ? 1: 0;

        d0 = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==8 || huns==9) ? 1: 0;
        d1 = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==8 || tens==9) ? 1: 0;
        d2 = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==8 || ones==9) ? 1: 0;

        e0 = (huns==0 || huns==2 || huns==6 || huns==8) ? 1 : 0;
        e1 = (tens==0 || tens==2 || tens==6 || tens==8) ? 1 : 0;
        e2 = (ones==0 || ones==2 || ones==6 || ones==8) ? 1 : 0;

        f0 = (huns==0 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
        f1 = (tens==0 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
        f2 = (ones==0 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;

        g0 = (huns==2 || huns==3 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
        g1 = (tens==2 || tens==3 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
        g2 = (ones==2 || ones==3 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;

        a3 = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==7 || thou==8 || thou==9) ? 1: 0;
        b3 = (thou==0 || thou==2 || thou==3 || thou==1 || thou==4 || thou==7 || thou==8 || thou==9) ? 1: 0;
        c3 = (thou==0 || thou==1 || thou==3 || thou==4 || thou==5 || thou==6 || thou==7 || thou == 8 || huns == 9) ? 1: 0;
        d3 = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==8 || thou==9) ? 1: 0;
        e3 = (thou==0 || thou==2 || thou==6 || thou==8) ? 1 : 0;
        f3 = (thou==0 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;
        g3 = (thou==2 || thou==3 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;

        // scorr[0].draw(VP, a0, b0, c0, d0, e0, f0, g0, 0);
        // scorr[1].draw(VP, a1, b1, c1, d1, e1, f1, g1, 0);
        // scorr[2].draw(VP, a2, b2, c2, d2, e2, f2, g2, 0);
        // scorr[3].draw(VP, a3, b3, c3, d3, e3, f3, g3, 0);

        imposter.draw(VP);
        
        if(!btnimp.vanish)
            btnimp.draw(VP);
        
        if(!btnobs.vanish)
            btnobs.draw(VP);
        
        // if(powerupactive){
        for(int i=0;i<num_coins;i++){
            if(coins[i].show)
                coins[i].draw(VP);
        }
        for(int i=0;i<num_obs;i++){
            if(obs[i].show)
                obs[i].draw(VP);
        }
        // }
        for(int i=0;i<num_bbox;i++){
            bbox[i].draw(VP);
        }
        // scorr.draw(VP,1,0,0,0,0,0,0,0);
        // hi.draw(VP);
        hud.draw(VP,btnimp.vanish,btnobs.vanish,light);
    }
    else
        over.draw(VP,win);
}

// void tick_input(GLFWwindow *window) {
//     if(glfwGetKey(window, GLFW_KEY_LEFT)){
//         playa.position.x -= speed_playa;
//         if(detect_collision(player_bb,bb_bb)){
//             playa.position.x += 2*speed_playa;
//         }
//     }
//     if(glfwGetKey(window, GLFW_KEY_RIGHT)){
//         playa.position.x += speed_playa;
//         if(detect_collision(player_bb,bb_bb)){
//             playa.position.x -= 2*speed_playa;
//         }
//     }
//     if(glfwGetKey(window, GLFW_KEY_UP)){
//         playa.position.y += speed_playa;
//         if(detect_collision(player_bb,bb_bb)){
//             playa.position.y -= 2*speed_playa;
//         }
//     }
//     if(glfwGetKey(window, GLFW_KEY_DOWN)){
//         playa.position.y -= speed_playa;
//         if(detect_collision(player_bb,bb_bb)){
//             playa.position.y += 2*speed_playa;
//         }
//     }
// }
void tick_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_LEFT)){
        if(move_playa(-speed_playa,0)){
            playa.position.x += -speed_playa;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)){
        if(move_playa(speed_playa,0)){
            playa.position.x += speed_playa;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_UP)){
        if(move_playa(0,speed_playa)){
            playa.position.y += speed_playa;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)){
        if(move_playa(0,-speed_playa)){
            playa.position.y += -speed_playa;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_1)){
        light = 0;
        // glUniform1i(lightID, 0);
    }
    if(glfwGetKey(window, GLFW_KEY_2)){
        light = 1;
        // glUniform1i(lightID, 1);
    }
}

bool move_playa(float x1, float y1){

    if(playa.position.x + x1 < -11.5 || playa.position.x + x1 > 11.5)
        return false;
    if(playa.position.y + y1 < -11.5 || playa.position.y + y1 > 11.5)
        return false;
    
    bounding_box_t temp;
    temp.x = player_bb.x + x1;
    temp.y = player_bb.y + y1;
    temp.height = player_bb.height;
    temp.width = player_bb.width;
    for(int i = 0; i <num_bbox; i++){
        if(detect_collision(temp,bb_bb[i])){
            return false;
        }
    }
    hud.position.x += x1;
    hud.position.y += y1;

    over.position.x += x1;
    over.position.y += y1;

    return true;
}

bool move_imposter(float x1, float y1){
    bounding_box_t temp;
    temp.x = imposter_bb.x + x1;
    temp.y = imposter_bb.y + y1;
    temp.height = imposter_bb.height;
    temp.width = imposter_bb.width;
    for(int i = 0; i <num_bbox; i++){
        if(detect_collision(temp,bb_bb[i])){
            return false;
        }
    }
    return true;
}

void tick_elements() {
    
    glUniform1i(lightID, light);
    
    eye_x = playa.position.x;
    eye_y = playa.position.y;
    tar_x = playa.position.x;
    tar_y = playa.position.y;

    if(!gameover){
        // eye_x = playa.position.x;
        // eye_y = playa.position.y;
        // tar_x = playa.position.x;
        // tar_y = playa.position.y;

        player_bb.x = playa.position.x;
        player_bb.y = playa.position.y;

        for(int i=0; i<num_coins; i++){
            if(detect_collision(player_bb,coins_bb[i])&&(coins[i].show))
            {
                cout << "collcoin " << i << endl;
                coins[i].show = false;
                score += 10;
            }
        }
        for(int i=0; i<num_obs; i++){
            if(detect_collision(player_bb,obs_bb[i])&&(obs[i].show))
            {
                obs[i].show = false;
                score -= 5;
            }
        }

        if(detect_collision(player_bb,btnobs_bb)&&(!btnobs.vanish))
        {
            for(int i=0; i<num_coins; i++){
                coins[i].show = true;
            }
            for(int i=0; i<num_obs; i++){
                obs[i].show = true;
            }
            powerupactive = true;
            btnobs.vanish = true;
            cout << "coll " << coins[0].show << powerupactive << endl;
        }

        if(detect_collision(player_bb,btnimp_bb)&&(!btnimp.vanish))
        {
            btnimp.vanish = true;
            imposter.vanish = true;
        }
        
        
        
        // imposter movement
        imposter_bb.x = imposter.position.x;
        imposter_bb.y = imposter.position.y;

        glm::vec3 delta = playa.position - imposter.position;
        glm::vec3 direction = glm::normalize(delta);

        // if(!xmov){
        //     if(ticks-xtick>5)
        //         xmov = true;
        // }
        // if(xmov){
        //     imposter.position.x += direction.x*speed_imposter;
        //     if(detect_collision(imposter_bb,bb_bb)){
        //         imposter.position.x -= 2*direction.x*speed_imposter;

        //         xtick = ticks;
        //         xmov = false;
        //     }
        // }

        // if(!ymov){
        //     if(ticks-ytick>5)
        //         ymov = true;
        // }
        // if(ymov){
        //     imposter.position.y += direction.y*speed_imposter;
        //     if(detect_collision(imposter_bb,bb_bb)){
        //         imposter.position.y -= 2*direction.y*speed_imposter;

        //         ytick = ticks;
        //         ymov = false;
        //     }
        // }
        if(move_imposter(direction.x*speed_imposter,0)){
            imposter.position.x += direction.x*speed_imposter;
        }
        if(move_imposter(0,direction.y*speed_imposter)){
            imposter.position.y += direction.y*speed_imposter;
        }

        // cout << score << endl;
        if(detect_collision(imposter_bb,player_bb)&&(!imposter.vanish)){
            gameover = true;
        }

        if(detect_collision(exit_bb,player_bb)){
            if(btnobs.vanish && btnimp.vanish){
                gameover = true;
                win = true;
            }
        }

        clock_t end = clock();
        float temp = (float)end - begintime;
        float elapsed_secs = temp / CLOCKS_PER_SEC;

        // cout << elapsed_secs << endl;
    }
    

}

bool checkbt1col(){
    bounding_box_t temp;
    temp.width = (1.732*btnimp.len/2);
    temp.height = (1.732*btnimp.len/2);
    temp.x = btnimp.position.x;
    temp.y = btnimp.position.y;
    for(int i=0; i<num_bbox;i++){
        if(detect_collision(temp,bb_bb[i])){
            return true;
        }
    }
    return false;
}

bool checkbt2col(){
    bounding_box_t temp;
    temp.width = (1.732*btnobs.len/2);
    temp.height = (1.732*btnobs.len/2);
    temp.x = btnobs.position.x;
    temp.y = btnobs.position.y;
    for(int i=0; i<num_bbox;i++){
        if(detect_collision(temp,bb_bb[i])){
            return true;
        }
    }
    return false;
}

bool checkimpcol(){
    bool ans = false;
    bounding_box_t temp;
    temp.width = 2/(imposter.zoom_fac);
    temp.height = 2/(imposter.zoom_fac);
    temp.x = imposter.position.x;
    temp.y = imposter.position.y;

    for(int i=0; i<num_bbox;i++){
        if(detect_collision(temp,bb_bb[i])){
            ans = true;
        }
    }
    cout << ans <<endl;
    return ans;
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // scorr = Score(0,0);
    hi = Hi(0,0);
    hud = Hud(-11,-11);
    // over = Over(0,0);
    over = Over(-11, -11);

    playa       = Ball(-11, -11, COLOR_BLUE);
    // imposter    = Imposter(-11, -5, COLOR_RED);
    imposter    = Imposter((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12, COLOR_RED);
    

    maze        = Maze(0, 0);
    // v2 = (float)rand()%400/100 + 4;
    bbox[0]     = Bbox((float)(rand()%400)/100 + 4, (float)(rand()%400)/100 + 4);
    bbox[1]     = Bbox((float)(rand()%400)/100 - 4, (float)(rand()%400)/100 + 4);
    bbox[2]     = Bbox((float)(rand()%400)/100 - 12, (float)(rand()%400)/100 + 4);
    bbox[3]     = Bbox((float)(rand()%400)/100 + 4, (float)(rand()%400)/100 - 4);
    bbox[4]     = Bbox((float)(rand()%400)/100 - 4, (float)(rand()%400)/100 - 4);
    bbox[5]     = Bbox((float)(rand()%400)/100 - 12, (float)(rand()%400)/100 - 4);
    bbox[6]     = Bbox((float)(rand()%400)/100 + 4, (float)(rand()%400)/100 - 12);
    bbox[7]     = Bbox((float)(rand()%400)/100 - 4, (float)(rand()%400)/100 - 12);
    // bbox[8]     = Bbox((float)(rand()%400)/100 - 12, (float)(rand()%400)/100 - 12);

    // check impcoll after setting blackboxes
    while(checkimpcol()!=false){
        cout << "a";
        imposter.set_position((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12);
    }
    
    // btnimp      = Btn(-11,-8, COLOR_ORANGE);
    // btnobs      = Btn(-11,-6, COLOR_SEAGREEN);
    btnimp      = Btn((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12, COLOR_ORANGE);
    btnobs      = Btn((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12, COLOR_SEAGREEN);

    while(checkbt1col()!=false){
        btnimp.set_position((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12);
    }
    while(checkbt2col()!=false){
        btnobs.set_position((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12);
    }

    for(int i=0; i<num_coins;i++){
        coins[i]    = Coin((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12);
    }
    for(int i=0; i<num_obs;i++){
        obs[i]    = Obstacle((float)(rand()%2400)/100 -12, (float)(rand()%2400)/100 -12);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    lightID = glGetUniformLocation(programID,"status");
    glUniform1i(lightID, 1);

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    player_bb.width = 2/(playa.zoom_fac);
    player_bb.height = 2/(playa.zoom_fac);

    imposter_bb.width = 2/(imposter.zoom_fac);
    imposter_bb.height = 2/(imposter.zoom_fac);

    for(int i = 0; i <num_bbox; i++){
        bb_bb[i].width = 4;
        bb_bb[i].height = 4;
        bb_bb[i].x = bbox[i].position.x + bb_bb[i].width/2;
        bb_bb[i].y = bbox[i].position.y + bb_bb[i].height/2;
    }
    

    btnimp_bb.width = (1.732*btnimp.len/2);
    btnimp_bb.height = (1.732*btnimp.len/2);
    btnimp_bb.x = btnimp.position.x;
    btnimp_bb.y = btnimp.position.y;

    btnobs_bb.width = (1.732*btnobs.len/2);
    btnobs_bb.height = (1.732*btnobs.len/2);
    btnobs_bb.x = btnobs.position.x;
    btnobs_bb.y = btnobs.position.y;

    for(int i=0; i<num_coins; i++){
        coins_bb[i].width = (1.732*coins[i].len/2);
        coins_bb[i].height = (1.732*coins[i].len/2);
        coins_bb[i].x = coins[i].position.x;
        coins_bb[i].y = coins[i].position.y;
    }
    for(int i=0; i<num_obs; i++){
        obs_bb[i].width = (1.732*obs[i].len/2);
        obs_bb[i].height = (1.732*obs[i].len/2);
        obs_bb[i].x = obs[i].position.x;
        obs_bb[i].y = obs[i].position.y;
    }

    exit_bb.x = 11;
    exit_bb.y = 11;
    exit_bb.height = 1;
    exit_bb.width = 1;
    

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // tick_elements();
            tick_input(window);
            tick_elements();

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
