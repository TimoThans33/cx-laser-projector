#ifndef _MACHY_UTILS_H_
#define _MACHY_UTILS_H_

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <math.h>
#include <glm/glm.hpp>
#include "envs.h"

class Environment
{
    std::vector<Variables*> *variables;
    public:
        Environment(){
            variables = new std::vector<Variables*>;
        }
        ~Environment(){
            std::vector<Variables*>::iterator it;

            for (it = variables->begin(); it < variables->end(); it++)
            {
                delete *it;
            }
            delete variables;
        };
        void appendVariable(Variables*);
        std::string get(int varNum);
        void print();
};

class MachyGLutils
{
    private:
        std::string vertex_shader_text;
        std::string fragment_shader_text;
        
        int vertex_flag, fragment_flag;

        const char* fs_text;
        const char* vs_text;

        std::vector<std::string> info;
    public:
        GLuint vertex_shader, fragment_shader;
        std::string read_shader(std::string direction);
        int get_compile_data(GLuint shader);
        GLuint link_shader(std::string vs_direction, std::string fs_direction);
};

class Window
{
    public:
        GLFWwindow* window;
        Window(void)
        {
            if (!glfwInit())
                exit(EXIT_FAILURE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

            window = glfwCreateWindow(640, 360, "MachyTech", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            glfwMakeContextCurrent(window);
            gladLoadGL();
            glfwSwapInterval(1);
        }
        ~Window(void)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }

};

class PVFilemanagement
{
    std::vector<std::string> info;
    std::vector<std::pair <std::string, std::vector<double>>> val;

    public:
        std::vector<std::pair <std::string, std::vector<double>>> read_csv(void);
        void print_csv(void);
};

#endif /* _MACHY_UTILS_H_ */