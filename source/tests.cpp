#define CATCH_CONFIG_RUNNER
#include "box.hpp"
#include "sphere.hpp"
#include "color.hpp"
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>


TEST_CASE("test_area", "[area]"){
  Material material{std::string{"test"},Color{1,0,0},Color{0,1,0},Color{0,0,1},5.0f};
  auto x = std::make_shared<Material>(material);
  std::shared_ptr<Material>mat = x;
  Sphere x1{{2.0f,2.0f,2.0f},5.0f};
  Sphere x2{"Hugo",mat,{2.0f,2.0f,2.0f},10.0f};
  Box y1{{0.0f,0.0f,0.0f},{5.0f,5.0f,5.0f}};
  Box y2{"Sera",mat,{1.0f,2.0f,1.0f},{6.0f,6.0f,6.0f}};

  REQUIRE (x1.area() == Approx(314.15927f));
  REQUIRE (x2.area() == Approx(1256.63706f));
  REQUIRE (y1.area() == Approx(150.0f));
  REQUIRE (y2.area() == Approx(130.0f));

  //std::cout<<x2<<"\n"<<y2;
  
}


TEST_CASE("test_volum", "[volum]"){
  Material material{std::string{"test"},Color{1,0,0},Color{0,1,0},Color{0,0,1},5.0f};
  auto x = std::make_shared<Material>(material);
  std::shared_ptr<Material>mat = x;
  Sphere x1{{2.0f,3.0f,4.0f},6.0f};
  Sphere x2{"Hugo",mat,{2.0f,3.0f,2.0f},9.0f};
  Box y1{{1.0f,1.0f,1.0f},{5.0f,5.0f,5.0f}};
  Box y2{"Phine",mat,{1.0f,3.0f,4.0f},{5.0f,6.0f,6.0f}};

  REQUIRE ( x1.volum() == Approx(904.77f));
  REQUIRE ( x2.volum() == Approx(3053.62806f));
  REQUIRE ( y1.volum() == Approx(64.0f));
  REQUIRE ( y2.volum() == Approx(24.0f));
}
TEST_CASE ( "intersect_ray_sphere","[intersect]")
{
  Material material{std::string{"test"},Color{1,0,0},Color{0,1,0},Color{0,0,1},5.0f};
  auto x = std::make_shared<Material>(material);
  std::shared_ptr<Material>mat = x;
// Ray
glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
//ray direction has to be normalized !
//you can use :
//v = glm::normalize(some_vector)
glm::vec3 ray_direction{0.0f , 0.0f , 1.0f };
// Sphere
Ray r1{{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}};
Ray r2{{0.0f,0.0f,0.0f},{0.0f,0.0f,1.0f}};
Ray r3{{1.0f,1.0f,15.0f},{0.0f,0.0f,10.0f}};
Sphere x1{"Sarah",mat,{1.0f,1.0f,1.0f},4.0f};
Sphere x2{"Sett",mat,{5.0f,5.0f,0.0f},4.0f};
Box y1{"Bert",mat,{0.0f,0.0f,0.0f},{10.0f,10.0f,10.0f}};
float f =1.0f;
Hitpoint h1 =x1.intersect(r1,f);
Hitpoint h2 =x2.intersect(r2,f);
Hitpoint h3 =y1.intersect(r3,f);
glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
float sphere_radius{1.0f};
float distance = 0.0f;
auto result = glm::intersectRaySphere (
ray_origin, ray_direction,
sphere_center,
sphere_radius * sphere_radius, // squared radius !!!
distance);



REQUIRE (h1.intersect);
REQUIRE (distance == Approx(4.0f));
REQUIRE (h1.objName == "Sarah");
REQUIRE (h1.distance == Approx(5.73205f));
REQUIRE (h2.intersect == false);
REQUIRE (h3.intersect);
REQUIRE (h3.objName == "Bert");

}

TEST_CASE ( "print material","[print]")
{
  Material mat{"test",{1,0,0},{0,1,0},{0,0,1},5.0f};
  //std::cout<<mat;
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}


/*Mit virtual desturctor:
erst wird der destruktor der abgeleiteten Klasse aufgerufen dann shape
Sphere->Shape->Sphere->Shape

Ohne virtual destructor:
erst wird der sphere destruktor aufgerufen und dann 2 mal der shape destruktor
Sphere->Shape->Shape 
Weil s2 ein Zeiger auf ein shape objekt ist wird der Shape destruktor aufgerufen und nicht der Sphere destructor
*/