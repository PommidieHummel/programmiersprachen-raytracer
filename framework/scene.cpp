#include "scene.hpp"


void sdfReader(std::string const& sdfFile){
    
    std::ifstream input_file(sdfFile);
    std::string line;

        while(getline(input_file,line)){
            std::istringstream string_stream(line);
            std::string define;

            string_stream >>define;
            if(define =="define"){
                std::string name;
                Color ka;
                Color ks;
                Color kd;
                float m;
                string_stream >> name;
                string_stream >> ka.r;
                string_stream >> ka.g;
                string_stream >> ka.b;
                string_stream >> ks.r;
                string_stream >> ks.g;
                string_stream >> ks.b;
                string_stream >> kd.r;
                string_stream >> kd.g;
                string_stream >> kd.b;
                string_stream >> m;
            
        Material material{name,{ka.r,ka.g,ka.b},{ks.r,ks.g,ks.b},{kd.r,kd.g,kd.b},m};
        auto x = std::make_shared<Material>(material);
        std::shared_ptr<Material>mat = x;    
        std::vector<std::shared_ptr<Material>> mat_vector;
        mat_vector.push_back(x);



            }
        }
}

    


    