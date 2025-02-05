#include "scene.hpp"

Scene sdfReader(std::string const &sdfFile)
{

    std::ifstream input_file;
    std::string define;
    std::string line;
    std::string ident;
    Scene s;
    std::map<std::string, int> object_map;
    int i = 0;

    input_file.open(sdfFile);
    if (input_file.is_open())
    {
        std::cout << "Hallo bin offen" << std::endl;
        while (getline(input_file, line))
        {
            std::istringstream string_stream(line);
            string_stream >> define;
            if (define == "define")
            {
                string_stream >> ident;
                if ("material" == ident)
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
                    std::cout << "\n ks.r: " << ks.r;
                    Material material{name, {ka.r, ka.g, ka.b}, {ks.r, ks.g, ks.b}, {kd.r, kd.g, kd.b}, m};
                    std::cout << "\n mat name: " << material.name << " ks.r: " << material.ka.r;
                    std::shared_ptr<Material> mat = std::make_shared<Material>(material);
                    s.material_map.insert(std::make_pair(name, mat));
                }
                if (ident == "shape")
                {
                    std::string sident;
                    string_stream >> sident;
                    if (sident == "box")
                    {
                        std::string boxName;
                        glm::vec3 min;
                        glm::vec3 max;
                        std::string matNameForBox;

                        string_stream >> boxName;
                        string_stream >> min.x;
                        string_stream >> min.y;
                        string_stream >> min.z;
                        string_stream >> max.x;
                        string_stream >> max.y;
                        string_stream >> max.z;
                        string_stream >> matNameForBox;

                        auto material = s.material_map.find(matNameForBox);
                        Box box{boxName, material->second, min, max};
                        std::shared_ptr<Shape> x = std::make_shared<Box>(box);
                        s.shape_vec.push_back(x);
                        object_map[boxName] = i;
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

                        auto material = s.material_map.find(matNameForSphere);
                        Sphere sphere{sphereName, material->second, ctr, r};
                        std::shared_ptr<Shape> x = std::make_shared<Sphere>(sphere);
                        s.shape_vec.push_back(x);
                        object_map[sphereName] = i;
                    }
                    i += 1;
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

                    Light light{nameLight, pos, color, brightness};
                    std::shared_ptr<Light> x = std::make_shared<Light>(light);
                    s.light_vec.push_back(x);
                }
                if (ident == "ambient")
                {
                    std::string ambName;
                    Color ambient;

                    string_stream >> ambName;
                    string_stream >> ambient.r;
                    string_stream >> ambient.g;
                    string_stream >> ambient.b;

                    s.ambient.ambName = ambName;
                    s.ambient.color.r = ambient.r;
                    s.ambient.color.g = ambient.g;
                    s.ambient.color.b = ambient.b;
                }
                if (ident == "camera")
                {
                    std::string cameraName;
                    float fovx;

                    string_stream >> cameraName;
                    string_stream >> fovx;
                    s.camera.name = cameraName;
                    s.camera.fovx = fovx;
                    std::cout << "\n camera name:" << s.camera.name << " " << cameraName;
                }
            }
            else if ("render" == define)
            {
                std::cout << "\n starting to render" << std::endl;
                std::string camNameForRender;
                std::string file;
                unsigned xres;
                unsigned yres;

                string_stream >> camNameForRender;
                string_stream >> file;
                string_stream >> xres;
                string_stream >> yres;

                s.render.camName = camNameForRender;
                s.render.fileName = file;
                s.render.xres = xres;
                s.render.yres = yres;
                std::cout << "\n render camera name: " << s.render.camName << s.render.fileName;
            }
            if (define == "transform")
            {
                std::string objectName;
                std::string transformType;
                float parameter1;
                float parameter2;
                float parameter3;

                string_stream >> objectName;
                string_stream >> transformType;
                string_stream >> parameter1;
                string_stream >> parameter2;
                string_stream >> parameter3;

                int index_of_name = object_map.find(objectName)->second; //gibt int "index" aus

                if (transformType == "translate")
                {
                   //index_of_name = 1
                   s.shape_vec[index_of_name]->translate(parameter1, parameter2, parameter3);
                }

                if (transformType == "scale")
                {
                    s.shape_vec[index_of_name]->scale(parameter1, parameter2, parameter3);
                }

                if (transformType == "rotate")
                {
                    float parameter4;
                    string_stream >> parameter4;
                    s.shape_vec[index_of_name]->rotate(parameter1, parameter2, parameter3, parameter4);

                }
                s.shape_vec[index_of_name]->adjustWorldMat();
                s.shape_vec[index_of_name]->adjustInvWorldMat();
            }

            //shape -> box, sphere; light -> ambient; camera; render
        }
        input_file.close();
    }
    else
    {
        std::cout << "oh nein ich bin nicht offen";
    }
    return s;
}

