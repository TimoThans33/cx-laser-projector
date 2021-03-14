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


void PVFilemanagement::read_csv()
{
    std::ifstream file("trajectory_1_fpg_out.txt");
    
    if(!file.is_open()) throw std::runtime_error("could not open file");

    if(file.good())
    {
        int rid = 0;
        std::string line, str;
        double value;
        while(std::getline(file, line))
        {
            if (rid <11){
                info.push_back(line);
            }
            if (rid == 11){
                std::stringstream ss(line);
                while(std::getline(ss, str, ','))
                {
                    val.push_back({str, std::vector<double>{}});
                }
            }
            if (rid > 11){
                int cid = 0;
                std::stringstream ss(line);
                while(ss >> value)
                {
                    val.at(cid).second.push_back(value);
                    if(ss.peek() == ',') ss.ignore();
                    cid++;
                }
            }
            rid++;
        }
    }
}

std::vector<double> PVFilemanagement::returnxout()
{
    std::vector<double> returnvector;
    for (int i=0; i<val.at(0).second.size(); ++i)
    {
        returnvector.push_back(val.at(0).second.at(i));
    }
    return returnvector;
}

std::vector<double> PVFilemanagement::returnyout()
{
    std::vector<double> returnvector;
    for (int i=0; i<val.at(0).second.size(); ++i)
    {
        returnvector.push_back(val.at(1).second.at(i));
    }
    return returnvector;
}

std::vector<double> PVFilemanagement::returnvelocity()
{
    std::vector<double> returnvector;
    for (int i=0; i<val.at(0).second.size(); ++i)
    {
        returnvector.push_back(val.at(3).second.at(i));
    }
    return returnvector;
}

std::vector<double> PVFilemanagement::returntime()
{
    std::vector<double> returnvector;
    for (int i=0; i<val.at(0).second.size(); ++i)
    {
        returnvector.push_back(val.at(2).second.at(i));
    }
    return returnvector;
}

std::vector<double> PVFilemanagement::returntheta()
{
    std::vector<double> returnvector;
    for (int i=0; i<val.at(0).second.size(); ++i)
    {
        returnvector.push_back(val.at(6).second.at(i));
    }
    return returnvector;
}

void PVFilemanagement::print_csv()
{
    for (auto& it: info){
        std::cout<< it <<std::endl;
    }

    std::cout<<"[";
    for(int j = 0; j < val.size(); ++j)
    {
        std::cout<<val.at(j).first<<" ";
    }

    std::cout<<"]\n";
    for (int i=0; i<val.at(0).second.size(); ++i){
        for(int j=0; j<val.size(); ++j)
        {
            std::cout<<val.at(j).second.at(i)<<" ";
        }
        std::cout<<"\n";
    }
}

std::vector<std::vector<double>> PVMath::create_rotmat(PVFilemanagement pv, int time)
{
    std::vector<double> theta = pv.returntheta();
    std::vector<std::vector<double>> returnmatrix {
                                        {cos(theta[time]), sin(theta[time])},
                                        {-sin(theta[time]), cos(theta[time])}
                                     };
    return returnmatrix;
}

void rotate_kernel(PVFilemanagement pv, std::vector<std::vector<double>> rotmatrix, int height, int width)
{
    std::vector<std::vector<int>> kernel {{0, width}, {height, width}, 
                            {height, -width}, {0, -width}, {0, width}};
    

}