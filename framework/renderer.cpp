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

Ray Renderer::raycast(Scene const &scene, Pixel const &p)
{
  float x = (((float)p.x / (float)width_ - 0.5f) * 2.0f * (float)std::tan(scene.camera.fovx / 180.0f * M_PI));
  float y = (((float)p.y / (float)height_ - 0.5f) * 2.0f * (float)std::tan(scene.camera.fovx / 180.0f * M_PI));

  glm::vec3 Vec1 = glm::cross(scene.camera.dir, scene.camera.up);
  glm::vec3 direction = glm::normalize(x * Vec1 + y * scene.camera.up + scene.camera.dir);
  return Ray{scene.camera.eye, direction};
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

      closest_t = t;
      closest_o = i;
    }
  }
  if (closest_o != nullptr)
  {
    return shade(ray, closest_t, scene, closest_o);
  }
  else
  {
    return scene.ambient.color;
  }
}

Color toneMap(Color const &col)
{
  float r = (col.r / (col.r + 1.0f));
  float g = (col.g / (col.g + 1.0f));
  float b = (col.b / (col.b + 1.0f));
  return {r, g, b};
}
Color shade(Ray const &ray, Hitpoint t, Scene const &scene, std::shared_ptr<Shape> shape)
{
  Color theShade{0.0f, 0.0f, 0.0f};
  for (auto i : scene.shape_vec)
  {
    Color ambient = ambientLight(scene, shape);
    Color difuss = diffuseLight(scene, shape, t);
    Color spec = specularLight(scene, shape, t);
    theShade = ambient + difuss + spec;

    return theShade;
  };
}

Color ambientLight(Scene const &scene, std::shared_ptr<Shape> shape)
{
  Color kaColor = shape->material_->ka;
  Color ambColor = scene.ambient.color;
  return (kaColor * ambColor);
}
Color diffuseLight(Scene const &scene, std::shared_ptr<Shape> shape, Hitpoint const &hitpoint)
{
  Color end{0,0,0};
  for (auto i : scene.light_vec)
  {

    glm::vec3 LightV{i->pos - hitpoint.hitpoint};
    Ray rayLight{hitpoint.hitpoint + 0.1f * hitpoint.normalized, glm::normalize(LightV)};
    Color in = i->color * i->brightness;
    Color kdColor = shape->material_->kd;
    float phi = -(glm::dot(hitpoint.normalized, glm::normalize(LightV)));
    end=end+(in * kdColor) * phi;
    }
    return end;
  }

Color specularLight(Scene const &scene, std::shared_ptr<Shape> shape, Hitpoint const &hitpoint)
{
  Color end{0,0,0};
  for (auto i : scene.light_vec){
  glm::vec3 LightV{i->pos - hitpoint.hitpoint};
  Ray rayLight{hitpoint.hitpoint + 0.1f * hitpoint.normalized, glm::normalize(LightV)};
    glm::vec3 v = glm::normalize(scene.camera.eye - hitpoint.hitpoint);
    float r = 2 * (glm::dot(hitpoint.normalized, glm::normalize(LightV) * hitpoint.normalized - glm::normalize(LightV)));
    float O = glm::dot(glm::vec3(r), v);
    Color ksColor = shape->material_->ks;
    Color in = i->color * i->brightness;
    float mFaktor = shape->material_->m;
    float faktor = ((mFaktor + 2) / 2 * M_PI);
    end=end+ (((in * ksColor) * faktor) * pow(O, mFaktor));
    
}
return end;
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
      p.color = toneMap(trace(raycast(scene, p), scene));
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
