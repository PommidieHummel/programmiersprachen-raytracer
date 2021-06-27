#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "box.hpp"
#include "sphere.hpp"


TEST_CASE("test_area", "[area]"){
  Sphere x1{{2.0f,2.0f,2.0f},5.0f};
  Sphere x2{"Hugo",{0.0f,0.0f,0.0f},{2.0f,2.0f,2.0f},10.0f};
  Box y1{{0.0f,0.0f,0.0f},{5.0f,5.0f,5.0f}};
  Box y2{"Sera",{1.0f,1.0f,1.0f},{1.0f,2.0f,1.0f},{6.0f,6.0f,6.0f}};

  REQUIRE (x1.area() == Approx(314.15927f));
  REQUIRE (x2.area() == Approx(1256.63706f));
  REQUIRE (y1.area() == Approx(150.0f));
  REQUIRE (y2.area() == Approx(130.0f));

  std::cout<<x2;
  std::cout<<y2;

}


TEST_CASE("test_volum", "[volum]"){
  Sphere x1{{2.0f,3.0f,4.0f},6.0f};
  Sphere x2{"Hugo",{0.0f,0.0f,0.0f},{2.0f,3.0f,2.0f},9.0f};
  Box y1{{1.0f,1.0f,1.0f},{5.0f,5.0f,5.0f}};
  Box y2{"Phine",{1.0f,0.3f,1.0f},{1.0f,3.0f,4.0f},{5.0f,6.0f,6.0f}};

  REQUIRE ( x1.volum() == Approx(904.77f));
  REQUIRE ( x2.volum() == Approx(3053.62806f));
  REQUIRE ( y1.volum() == Approx(64.0f));
  REQUIRE ( y2.volum() == Approx(24.0f));
}
TEST_CASE ( "intersect_ray_sphere","[intersect]")
{
// Ray
glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
//ray direction has to be normalized !
//you can use :
//v = glm::normalize(some_vector)
glm::vec3 ray_direction{0.0f , 0.0f , 1.0f };
// Sphere
Ray r1{{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f}};
Sphere x1{"Sarah",{0.0f,0.0f,0.0f},{1.0f,1.0f,1.0f},4.0f};
Hitpoint h1 =x1.intersect(r1);
glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
float sphere_radius{1.0f};
float distance = 0.0f;
auto result = glm::intersectRaySphere (
ray_origin, ray_direction,
sphere_center,
sphere_radius * sphere_radius, // squared radius !!!
distance);

REQUIRE (distance == Approx(4.0f));
REQUIRE (h1.objName == "Sarah");
REQUIRE (h1.distance == Approx(5.73205f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
