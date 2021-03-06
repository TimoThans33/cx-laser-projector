#include "socketdev.h"
#include "scene.h"

//#define DEBUG

int main(int argc, char* argv[])
{
    char *buffer_pointer;

    socket_programming socket(argc, argv);
    Scene scene;

    socket.wait_for_connection();
    /* Check if ENV variables are available */
    int main_flag = 1;
    if(getenv("GLSL_APP_VERT")!=NULL && getenv("GLSL_APP_FRAG")!=NULL){
        char* vs_direction = getenv("GLSL_APP_VERT");
        char* fs_direction = getenv("GLSL_APP_FRAG");
        // link the shaders to ;our program 
        std::cout<<"src direction vertex shader : "<<vs_direction<<std::endl;
        std::cout<<"src direction fragment shader : "<<fs_direction<<std::endl;
        main_flag = scene.link_shader(vs_direction, fs_direction);
    }
    else{
        // read the defined shaders into a char array 
        char vs_direction[] = "shaders/basic.vert";
        char fs_direction[] = "shaders/basic.frag";
        // link the shaders to our program
        std::cout<<"src direction vertex_shader : "<<vs_direction<<std::endl;
        std::cout<<"src direction fragment shader : "<<fs_direction<<std::endl;
        main_flag = scene.link_shader(vs_direction, fs_direction);
    }
    
    while(main_flag==0){
        // get json data from socket
        buffer_pointer = socket.run();
        // the draw function will return non-zero upon exit
        main_flag = scene.draw(buffer_pointer);
    }
    // do some proper clean-up
    socket.cleanup();
    return 0;
}