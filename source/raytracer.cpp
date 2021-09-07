#include <renderer.hpp>
#include <window.hpp>
#include <scene.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <memory>
#include <vector>
#include <map>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 800;
  std::string scenefile = "./testscene.txt";
  std::string const file;

  //Test scene ohne Parser
  //Material
  Material m{{"rosa"},{1,0.1,1},{1,0.1,1},{1,1,1},810.0f};
  Material m2{{"blue"},{0.1,1,1},{0.1,1,1},{10,10,10},810.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  std::shared_ptr<Material>materia2 =std::make_shared<Material>(m2);

  //Shapes
  Sphere s{{"kreis"},{materia},{20,-15,-70},20};
  Sphere s2{{"kreise"},{materia2},{0,40,-150},50};
  Box b{{"box"},materia,{-100,-80,-200},{50,40,-100}};
  std::shared_ptr<Shape>sp=std::make_shared<Sphere>(s);
  std::shared_ptr<Shape>sp2=std::make_shared<Sphere>(s2);
  std::shared_ptr<Shape>bo=std::make_shared<Box>(b);

  //Light
  Light li{{"Sun2"},{0,0,0},{0.2f,0.2f,0.2f},100};
  Light l{{"Sun"},{500,700,0},{0.2f,0.2f,0.2f},100};
  Light la{{"Moon"},{1000,-70,0},{0.2f,0.1f,0.2f},100};
  std::shared_ptr<Light>ligh3=std::make_shared<Light>(li);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::shared_ptr<Light>ligh2=std::make_shared<Light>(la);

  //Camera
  Camera camera{{"eye"},45.0f};

  //Render
  Render render{{"eye"},{"image.ppm"},480,320};

  //Container
  std::vector<std::shared_ptr<Light>>light;
  std::vector<std::shared_ptr<Shape>>box;
  std::map<std::string,std::shared_ptr<Material>>material;

  //Objekte in Container stopfen
  //box.push_back(sp);
  box.push_back(sp2);
  box.push_back(bo);
  
  //light.push_back(ligh);
  //light.push_back(ligh2);
  light.push_back(ligh3);
  
  material.insert(std::make_pair("red",materia));
  material.insert(std::make_pair("blue",materia2));

  //Testobjekt
  Scene testScene{box,light,material,camera,{"white",{1,1,1}},render};

  //Test scene ende
  Renderer renderer{image_width, image_height, file,testScene};
  //render mit sdfFile
  renderer.render(sdfReader(scenefile));

  //render mit Sceneobjekt
  //renderer.render(testScene);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }
  
  return 0;
}
