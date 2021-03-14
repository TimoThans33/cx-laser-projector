#ifndef _MACHY_UTILS_H_
#define _MACHY_UTILS_H_

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


class PVFilemanagement
{
    std::vector<std::string> info;
    std::vector<std::pair <std::string, std::vector<double>>> val;

    public:
        void read_csv(void);
        void print_csv(void);
        std::vector<double> returnxout(void);
        std::vector<double> returnyout(void);
        std::vector<double> returntime(void);
        std::vector<double> returnvelocity(void);
        std::vector<double> returntheta(void);
};

class PVMath
{
    public:
        std::vector<double> x_trans, y_trans, v;
    public:
        std::vector<std::vector<double>> create_rotmat(PVFilemanagement pv, int time);
        void rotate_kernel(PVFilemanagement pv, int height, int width);
        void line_intersect(PVFilemanagement pv);
        void rotate_coord(int time, int n_steps, PVFilemanagement pv);
        void transform_xyv();
    private:
        int t, n;
        std::vector<double> rot_mat;
};

#endif /* _MACHY_UTILS_H_ */