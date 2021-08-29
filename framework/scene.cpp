#include "scene.hpp"

Scene sdfReader(std::string const &sdfFile)
{

    std::ifstream input_file;
    input_file.open(sdfFile);
    std::string define;
    std::string line;
    std::string ident;
    Scene s;

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
                Material material{name, {ka.r, ka.g, ka.b}, {ks.r, ks.g, ks.b}, {kd.r, kd.g, kd.b}, m};
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
            }
        }
        if (define == "render")
        {
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

            std::cout << s.render.camName << "\n"<<s.render.fileName<<"\n";
        }
        //shape -> box, sphere; light -> ambient; camera; render
    }
    std::cout << s.camera.fovx << "\n"
              << s.render.fileName << "\n";
    return s;
}
