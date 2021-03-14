#include "socketdev.h"
#include "scene.h"
#include "machy_utils.h"
#include "envs.h"

//#define DEBUG

std::vector<Variables*> *variables;

void create_env(Environment *env){
    env->appendVariable( new FragShader("GLSL_APP_VERT", "shaders/basic.vert"));
    env->appendVariable( new VertexShader("GLSL_APP_FRAG", "shaders/basic.frag"));
    env->appendVariable( new IPaddress("IP_ADDR", "127.0.0.1"));
    env->appendVariable( new Portaddress("PORT_ADDR", "8000"));
}

int main()
{
    char *buffer_pointer;

    /* creating the environment */
    Environment *env = new Environment ();
    create_env(env);
    env->print();

    PVFilemanagement filemanagement;
    filemanagement.read_csv();
    std::vector<double> x_out = filemanagement.returnxout();
    for (auto& it : x_out){std::cout<< it <<" ";}
    /* opening the socket */
    socket_programming socket(env->get(2), env->get(3));
    socket.wait_for_connection();
    /* start openGL context */
    Scene scene;
    /* link to the shaders */
    int main_flag = 1;
    main_flag = scene.link_shader(env->get(0), env->get(1));

    while(main_flag==0){
        // get json data from socket
        buffer_pointer = socket.run();
        // the draw function will return non-zero upon exit
        main_flag = scene.draw(buffer_pointer);
    }
    return 0;
}