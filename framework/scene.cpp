#include "scene.hpp"

void sdfReader(std::string const &sdfFile)
{

    std::ifstream input_file(sdfFile);
    std::string line;

    while (getline(input_file, line))
    {
        std::istringstream string_stream(line);
        std::string define;

        string_stream >> define;
        if (define == "define")
        {
            std::string ident;
            if (ident == "material")
            {
                std::string name;
                Color ka;
                Color ks;
                Color kd;
                float m;
                //reading name
                string_stream >> name;
                //reading ka
                string_stream >> ka.r;
                string_stream >> ka.g;
                string_stream >> ka.b;
                //reading ks
                string_stream >> ks.r;
                string_stream >> ks.g;
                string_stream >> ks.b;
                //reading kd
                string_stream >> kd.r;
                string_stream >> kd.g;
                string_stream >> kd.b;
                //reading m
                string_stream >> m;

                //saving shared pointer of material in file in vector
                Material material{name, {ka.r, ka.g, ka.b}, {ks.r, ks.g, ks.b}, {kd.r, kd.g, kd.b}, m};
                auto x = std::make_shared<Material>(material);
                std::shared_ptr<Material> mat = x;
                std::vector<std::shared_ptr<Material>> mat_vector;
                mat_vector.push_back(mat);
            }
            if (ident == "shape")
            {
                std::string sident;
                string_stream >> sident;
                if (sident == "box")
                {
                    std::string boxName;
                    float min;
                    float max;
                    std::string matNameForBox;

                    string_stream >> boxName;
                    string_stream >> min;
                    string_stream >> max;
                    string_stream >> matNameForBox;
                }
                if (sident == "sphere")
                {
                    std::string sphereName;
                    glm::vec3 ctr;
                    float r;
                    std::string matNameForSphere;

                    string_stream >> sphereName;
                    string_stream >> ctr.x;
                    string_stream >> ctr.y;
                    string_stream >> ctr.z;
                    string_stream >> r;
                    string_stream >> matNameForSphere;
                }
            }
            if (ident == "light")
            {
                std::string nameLight;
                glm::vec3 pos;
                Color color;
                float brightness;

                string_stream >> nameLight;
                string_stream >> pos.x;
                string_stream >> pos.y;
                string_stream >> pos.z;
                string_stream >> color.r;
                string_stream >> color.g;
                string_stream >> color.b;
                string_stream >> brightness;
            }
            if (ident == "camera")
            {
                std::string cameraName;
                float fovx;
                glm::vec3 eye;
                glm::vec3 dir;
                glm::vec3 up;

                string_stream >> cameraName;
                string_stream >> fovx;
                string_stream >> eye.x;
                string_stream >> eye.y;
                string_stream >> eye.z;
                string_stream >> dir.x;
                string_stream >> dir.y;
                string_stream >> dir.z;
                string_stream >> up.x;
                string_stream >> up.y;
                string_stream >> up.z;
            }
            if (ident == "render")
            {
                std::string camNameForRender;
                std::string file;
                int xres;
                int yres;

                string_stream >> camNameForRender;
                string_stream >> file;
                string_stream >> xres;
                string_stream >> yres;
            }
            //shape -> box, sphere; light -> ambient; camera; render
        }
    }
}
