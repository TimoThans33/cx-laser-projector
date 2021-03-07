#ifndef _MACHY_UTILS_H_
#define _MACHY_UTILS_H_

#include <vector>
#include <iostream>
#include <fstream>
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

/*
class Filemanagement
{
    public:
        void read_csv(void);
};
*/
#endif /* _MACHY_UTILS_H_ */