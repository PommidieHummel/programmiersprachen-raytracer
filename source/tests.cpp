#define CATCH_CONFIG_RUNNER
#include "scene.hpp"
#include <catch.hpp>
#include <memory>
#include <iostream>

TEST_CASE("SDFreader", "[Scene]")
{
  /*Material material{std::string{"red"}, Color{1, 0, 0}, Color{1, 0, 0}, Color{1, 0, 0}, 1.0f};
  Material material2{std::string{"blue"}, Color{0, 0, 1}, Color{0, 0, 1}, Color{0, 0, 1}, 1.0f};
  std::shared_ptr<Material> x = std::make_shared<Material>(material);
  std::shared_ptr<Material> y = std::make_shared<Material>(material2);

 
  Sphere x2{"bsphere", y, {0.0f, 0.0f, -100.0f}, 50.0f};
  Box y2{"rbottom", x, {-100.0f, -80.0f, -200.0f}, {100.0f, 80.0f, -100.0f}};
*/
  Scene test = sdfReader("testscene.txt");
  std::cout<<test.camera.name;
  auto a1 = test.camera.name;
  auto a2 = test.camera.fovx;

  auto b1 = test.render.fileName;
  

  REQUIRE( a1 == "eye");
  REQUIRE( a2 == 45.0);
  REQUIRE(b1 == "easyscene.txt");
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
