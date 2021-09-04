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

Ray Renderer::raycast(Scene const &scene,Pixel const& p)
{
  float x = (((float)p.x / (float)width_ - 0.5f) * 2.f * (float)std::tan(scene.camera.fovx / 180.0f * M_PI));
  float y = (((float)p.y / (float)height_ - 0.5f) * 2.f * (float)std::tan(scene.camera.fovx / 180.0f * M_PI));

  glm::vec3 rightVec = glm::cross(scene.camera.dir, scene.camera.up);
  glm::vec3 direction = glm::normalize(x * rightVec + y * scene.camera.up + scene.camera.dir);
  std::cout<<direction.x<<" "<<direction.y<<" "<<direction.z<<" ";
  return Ray{scene.camera.eye,direction};
  
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
  shadow.direction = glm::normalize(scene.light_vec[0]->pos - t.hitpoint);
  for (auto i : scene.shape_vec)
  {
    auto Hit = i->intersect(shadow);
    if (Hit.intersect)
    {
      return {0, 0, 0};
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
      p.color = trace(raycast(scene,p), scene);
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
