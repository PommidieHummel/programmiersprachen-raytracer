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
  Material m{{"red"},{1,0,0},{1,0,0},{1,0,0},1.3f};
  Material m2{{"blue"},{0,0,1},{0,0,1},{0,0,1},1.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  std::shared_ptr<Material>materia2 =std::make_shared<Material>(m2);
  Sphere s{{"kreis"},{materia2},{0,5,-100},20};
  Sphere s2{{"kreise"},{materia},{-20,10,-140},20};
  Light l{{"Sun"},{1000,700,0},{0.2f,0.2f,0.2f},10};
  Camera camera{{"eye"},45.0f};
  Render render{{"eye"},{"image.ppm"},480,320};
  std::shared_ptr<Shape>sp=std::make_shared<Sphere>(s);
  std::shared_ptr<Shape>sp2=std::make_shared<Sphere>(s2);
  std::vector<std::shared_ptr<Shape>>box;
  box.push_back(sp);
  box.push_back(sp2);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::vector<std::shared_ptr<Light>>light;
  light.push_back(ligh);
  std::map<std::string,std::shared_ptr<Material>>material;
  material.insert(std::make_pair("red",materia));
  material.insert(std::make_pair("blue",materia2));
  Scene testScene{box,light,material,camera,{"white",{1,1,1}},render};

  //Test scene ende
  //Scene scene = sdfReader(scenefile);
  std::cout <<"\n Camera shit: "<< testScene.camera.name <<" "<< testScene.camera.fovx<<"\n renderer shit: "<<testScene.render.camName;
  Renderer renderer{image_width, image_height, file,testScene};
  renderer.render(sdfReader(scenefile));

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }
  
  return 0;
}
