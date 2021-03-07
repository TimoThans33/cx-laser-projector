#include "machy_utils.h"

void Environment::appendVariable(Variables *variable){
    variables->push_back ( variable );
}

void Environment::print()
{
    std::vector<Variables*>::iterator it;
    
    for (it = variables->begin (); it < variables->end (); it++)
    {
        std::string str = (*it)->get_var();
        std::cout<<str<<std::endl;
    }
}

std::string Environment::get(int varNum)
{
    std::vector<Variables*>::iterator it = variables->begin () + varNum;
    return (*it)->get_var();
}

/*
void Filemanagement::read_csv()
{
    std::ifstream file("trajectory_1_fpg_out.txt");
    
    if(!file.isopen()) throw std::runtime_error("could not open file")
    std::string value;

    std::cout<<"reading csv file...\n";
    while (file.good())
    {
        getline ( file, value, ',' );
        std::cout<< std::string( value, 1, value.length()-2 );
    }

}
*/