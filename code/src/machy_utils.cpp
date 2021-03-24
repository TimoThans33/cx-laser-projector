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

std::string MachyGLutils::read_shader(std::string direction)
{
    std::ifstream in(direction);
    std::string contents((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    std::string shader_text = contents.c_str();
    return shader_text;
}

GLuint MachyGLutils::link_shader(std::string vs_direction, std::string fs_direction)
{
    vertex_shader_text = read_shader(vs_direction);
    vs_text = vertex_shader_text.c_str();
    std::cout<<"using vertex shader : \n"<<vs_text<<std::endl;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vs_text, NULL);
    glCompileShader(vertex_shader);
    vertex_flag = get_compile_data(vertex_shader);
    if (vertex_flag==1){
        std::cout<<"Error when compiling"<<std::endl;
        throw;
    }
    std::cout<<"using vertex shader : \n"<<vs_text<<std::endl;

    fragment_shader_text = read_shader(fs_direction);
    fs_text = fragment_shader_text.c_str();

    std::cout<<"using the fragment shader : \n"<<fs_text<<std::endl;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs_text, NULL);
    glCompileShader(fragment_shader);

    fragment_flag = get_compile_data(fragment_shader);
    if (fragment_flag==1){
        std::cout<<"Error when compile the fragment shader"<<std::endl;
        throw;
    }

    std::cout<<"using the fragment shader : \n"<<fs_text<<std::endl;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    return program;
}

int MachyGLutils::get_compile_data(GLuint shader)
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        /* ERROR handling */
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        /* make sure we don't leak the shader */
        glDeleteShader(shader);
        for(int i=0; i<maxLength; i++){
            std::cout<<errorLog[i];
        }
        /* return 1 on error */
        return 1;
    }
    /* return 0 when succesfull */
    return 0;
}
void MachyGLutils::read_remote_csv(std::string weburl, struct Positions *positions)
{
    CURL *curl_handle;
    CURLcode res;

    struct CurlMemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_handle = curl_easy_init();
    if(curl_handle)
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, weburl);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        res = curl_easy_perform(curl_handle);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else{
            std::cout<<(unsigned long)chunk.size)<<"%lu bytes retrieved\n";
            clock_t begin_t = clock();

            std::string line, str;
            float value;
            float * data;
            while(std::getline(chunk.memory, line))
            {
                std::stringstream ss(line);
                int cid = 0;
                while(ss >> value)
                {
                    data[cid] = value;
                    if(ss.peek() == ',') ss.ignore();
                    cid++;
                    data = new int;
                }
                position.push_back({data[0], data[1]});
            }
            clock_t end_t = clock();
            printf("read file in: %lf\n", double(end_t-begin_t)/double(CLOCKS_PER_SEC));
        }
    }
}
/*
void MachyGLutils::read_csv(std::string filedir)
{
    std::ifstream file(filedir);
}
*/
static size_t MachyGLutils::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct CurlMemoryStruct *mem = (struct CurlMemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL)
    {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

std::vector<std::pair <std::string, std::vector<double>>> PVFilemanagement::read_csv()
{
    std::vector<std::pair <std::string, std::vector<double>>> val;
    std::ifstream file("trajectory_1_fpg_out.txt");
    clock_t begin_t = clock();

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
            clock_t end_t = clock();
            printf("read file in: %lf\n", double(end_t-begin_t)/double(CLOCKS_PER_SEC));
        }
        return val;
    }
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