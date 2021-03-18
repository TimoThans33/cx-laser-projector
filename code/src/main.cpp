#include "socketdev.h"
#include "scene.h"
#include "machy_utils.h"
#include "envs.h"

//#define DEBUG

std::vector<Variables*> *variables;

void create_env(Environment *env){
    env->appendVariable( new FragShader("GLSL_APP_VERT", "shader/basic.vert"));
    env->appendVariable( new VertexShader("GLSL_APP_FRAG", "shader/basic.frag"));
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
    MachyGLutils utils;
    /* creating openGL context */
    Window win;
    /* call shader linker */
    GLuint program = utils.link_shader(env->get(0), env->get(1));
    Scene *scene;
    RobotPath robotpath(program, filemanagement.read_csv());
    scene = &robotpath;
    while(1){
        scene->render(win.window);
    }
    return 0;
}