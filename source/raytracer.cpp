#include <renderer.hpp>
#include <window.hpp>
#include <scene.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const scenefile = "./testscene.txt";
  std::string const file;
  Scene scene = sdfReader(scenefile);
  std::cout<<scene.camera.fovx<<scene.camera.name;
  /*Renderer renderer{image_width, image_height, file};
  renderer.render(scenefile);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }
  */
  return 0;
}
