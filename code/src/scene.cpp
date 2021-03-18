#include "scene.h"

void RobotPath::bind_buffer()
{
    clock_t begin_t = clock();
    for(int i=0; i<val.at(0).second.size(); i++)
    {
        position.push_back({(float)val.at(0).second.at(i), (float)val.at(1).second.at(i)});
    }
    clock_t end_t = clock();
    printf("formatted data in : %lf\n", double(end_t-begin_t)/double(CLOCKS_PER_SEC));
    glBufferData(GL_ARRAY_BUFFER, position.size()*sizeof(position), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, position.size()*sizeof(position), &position[0]);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(position[0]), NULL);
    glEnableVertexAttribArray(vpos_location);
    std::cout<<position[0].x<<", "<<position[0].y<<std::endl;
}

void RobotPath::render(GLFWwindow* win)
{
    for (int i=0; i<val.at(0).second.size(); i++)
    {
        double t_begin = val.at(2).second.at(i);
        clock_t ct_begin = clock();

        const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        int width, height;
        glfwGetFramebufferSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glUseProgram(program);

        
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, -(float)val.at(6).second.at(i),
                    glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glm::vec2 offset = glm::vec2((float)val.at(0).second.at(i), 
                                        (float)val.at(1).second.at(i));
        glUniform2fv(off_location, 1, glm::value_ptr(offset));
        glUniformMatrix4fv(rot_location, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawArrays(GL_LINE_STRIP, 0 , n_points);

        double t_end = val.at(2).second.at(i+1);
        clock_t ct_end = clock();
        double cdt = double(ct_end-ct_begin)/double(CLOCKS_PER_SEC);
        double dt = double(t_end - t_begin);

        printf("fps: %lf\n", 1/cdt);
        printf("idle: %lf\n", double(dt-cdt));
        if(double(dt-cdt)>0){usleep(double(dt-cdt) * 1000000);}

        glfwSwapBuffers(win);
        glfwPollEvents();
        if (glfwWindowShouldClose(win)){
            exit(1);
        }
    }
}

void RobotPath::print_data()
{
    for (const auto &arr: position){
        std::cout<< arr.x<< ", " << arr.y <<std::endl;
    }
}
