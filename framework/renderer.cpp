// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include "renderer.hpp"
#include "scene.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const &file, Scene const &scene)
    : width_(w), height_(h), color_buffer_(w * h, Color{0.0, 0.0, 0.0}), filename_(file), ppm_(width_, height_), scene_(scene)
{
}

Ray Renderer::raycast(Scene const &scene)
{

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      glm::vec3 origin = scene.camera.eye;
      float dir_x = scene.camera.dir.x + x - (width_ * 0.5f);
      float dir_y = scene.camera.dir.y + y - (height_ * 0.5f);
      float dir_z = scene.camera.dir.z + (width_ / 2.0f) / tan((scene.camera.fovx / 2.0f) * M_PI / 180);
      glm::vec3 direction{dir_x, dir_y, dir_z};

      glm::vec4 u = glm::vec4(glm::normalize(glm::cross(direction, scene.camera.up)), 0.0f);
      glm::vec4 v = glm::vec4(glm::normalize(glm::cross({u.x, u.y, u.z}, direction)), 0.0f);
      glm::mat4 c{u, v, glm::vec4{glm::normalize(-direction), 0}, glm::vec4{origin, 1}};
      Ray ray{origin, glm::normalize(direction)};
      glm::vec4 org = c * glm::vec4(ray.origin, 1.0f);
      glm::vec4 dir = c * glm::vec4(ray.direction, 0.0f);
      Ray c_ray{{org.x, org.y, org.z}, {dir.x, dir.y, dir.z}};
      return c_ray;
    }
  }
}
Color trace(Ray const &ray, Scene const &scene)
{

  std::shared_ptr<Shape> closest_o = nullptr;
  Hitpoint closest_t;
  for (auto i : scene.shape_vec)
  {
    Hitpoint t = i->intersect(ray);
    if (t.intersect == true)
    {
      std::cout << "Hit ";
      closest_t = t;
      closest_o = i;
    }
    if (closest_o != nullptr)
    {
      std::cout << "hallo";
      return shade(ray, closest_t, scene);
    }
    else
    {
      return scene.ambient.color;
    }
  }
}
Color shade(Ray const &ray, Hitpoint t, Scene const &scene)
{
  Ray shadow;
  std::map<std::string, std::shared_ptr<Material>>::const_iterator it = scene.material_map.begin();
  auto Material = it->second;
  shadow.direction = glm::normalize(scene.light_vec[0]->pos -t.hitpoint);
  for (auto i: scene.shape_vec)
  {
    auto Hit = i->intersect(shadow);
    if (Hit.intersect)
    {
      return {0,0,0};
    }
    else
    {
      Color mka = {Material->ka.r * scene.light_vec[0]->brightness, Material->ka.g * scene.light_vec[0]->brightness, Material->ka.b * scene.light_vec[0]->brightness};
      return mka;
    }
  }
}
void Renderer::render(Scene const &scene)
{

  std::cout << "starting to render";
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x, y);
      p.color = trace(raycast(scene), scene);
      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const &p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_ * p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0)
  {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
              << "pixel out of ppm_ : "
              << (int)p.x << "," << (int)p.y
              << std::endl;
  }
  else
  {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
