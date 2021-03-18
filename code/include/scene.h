#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <string.h>

class Scene{
    protected:
        GLuint program, n_points;
        std::vector<std::pair <std::string, std::vector<double>>> val;
        struct Position{
            float x, y;
        };
        std::vector <Position> position;
    public:
        Scene(GLuint a, std::vector<std::pair <std::string, std::vector<double>>> b)
        {
            program = a;
            val = b;
            n_points = val.at(0).second.size();
            printf("total points: %d\n", n_points);
        }
        virtual void bind_buffer() {};
        virtual void print_data() {};
        virtual void render(GLFWwindow* win) {};
        virtual ~Scene() {};
};

class RobotPath : public Scene
{
    private:
        GLuint vertex_array_object, buffer, rot_location, vpos_location, off_location;
    public:
        RobotPath (GLuint a, std::vector<std::pair <std::string, std::vector<double>>> b) : Scene(a, b)
        {
            glCreateVertexArrays(1, &vertex_array_object);
            glBindVertexArray(vertex_array_object);

            rot_location = glGetUniformLocation(program, "ROT");
            off_location = glGetUniformLocation(program, "OFF");
            vpos_location = glGetAttribLocation(program, "position");

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            bind_buffer();
        }
        void bind_buffer();
        void render(GLFWwindow* win);
        void print_data();
        ~RobotPath()
        {
            glDeleteVertexArrays(1, &vertex_array_object);
            glDeleteProgram(program);
            glDeleteVertexArrays(1, &vertex_array_object);
        }
};
#endif