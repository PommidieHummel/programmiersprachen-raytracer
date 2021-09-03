// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const &file)
    : width_(w), height_(h), color_buffer_(w * h, Color{0.0, 0.0, 0.0}), filename_(file), ppm_(width_, height_)
{
}

Ray raycast()
{
  Material m{{"red"},{1,0,0},{1,0,0},{1,0,0},1.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  Box b{{"rbottom"},{materia},{-100,-80,-200},{100,80,-100}};
  Light l{{"Sun"},{1000,700,0},{0.2f,0.2f,0.2f},100};
  Camera camera{{"eye"},45.0f};
  Render render{{"eye"},{"image.ppm"},480,320};
  std::shared_ptr<Shape>bo=std::make_shared<Box>(b);
  std::vector<std::shared_ptr<Shape>>box;
  box.push_back(bo);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::vector<std::shared_ptr<Light>>light;
  light.push_back(ligh);
  std::map<std::string,std::shared_ptr<Material>>material;
  material.insert(std::make_pair("red",materia));
  Scene scene{box,light,material,camera,{"white",{1,1,1}},render};

  auto ndir = glm::normalize(scene.camera.dir);
  return {scene.camera.eye, ndir};
}
Color trace(Ray const &ray)
{
  Material m{{"red"},{1,0,0},{1,0,0},{1,0,0},1.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  Box b{{"rbottom"},{materia},{-100,-80,-200},{100,80,-100}};
  Light l{{"Sun"},{1000,700,0},{0.2f,0.2f,0.2f},100};
  Camera camera{{"eye"},45.0f};
  Render render{{"eye"},{"image.ppm"},480,320};
  std::shared_ptr<Shape>bo=std::make_shared<Box>(b);
  std::vector<std::shared_ptr<Shape>>box;
  box.push_back(bo);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::vector<std::shared_ptr<Light>>light;
  light.push_back(ligh);
  std::map<std::string,std::shared_ptr<Material>>material;
  material.insert(std::make_pair("red",materia));
  Scene scene{box,light,material,camera,{"white",{1,1,1}},render};
  
  std::shared_ptr<Shape>closest_o=nullptr;
  Hitpoint closest_t;
  for (auto i: scene.shape_vec)
  {
    Hitpoint t = i->intersect(ray);
    if(t.intersect)
    {
      std::cout<<"Hit";
     
    if (t.distance < closest_t.distance && t.intersect)
    {
      closest_t = t;
      closest_o = i;
    }
  }
  if (closest_o != nullptr)
  {
    return shade(ray,closest_t);
  }
  else
  {
    return scene.ambient.color;
  }}
}
Color shade(Ray const &ray, Hitpoint t){
  Material m{{"red"},{1,0,0},{1,0,0},{1,0,0},1.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  Box b{{"rbottom"},{materia},{-100,-80,-200},{100,80,-100}};
  Light l{{"Sun"},{1000,700,0},{0.2f,0.2f,0.2f},100};
  Camera camera{{"eye"},45.0f};
  Render render{{"eye"},{"image.ppm"},480,320};
  std::shared_ptr<Shape>bo=std::make_shared<Box>(b);
  std::vector<std::shared_ptr<Shape>>box;
  box.push_back(bo);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::vector<std::shared_ptr<Light>>light;
  light.push_back(ligh);
  std::map<std::string,std::shared_ptr<Material>>material;
  material.insert(std::make_pair("red",materia));
  Scene scene{box,light,material,camera,{"white",{1,1,1}},render};

  auto scenelight = scene.light_vec[1].get();
  Ray shadow;
  std::map<std::string, std::shared_ptr<Material>>::const_iterator it = scene.material_map.begin();
  auto Material = it->second;
  shadow.direction = scenelight->pos - t.hitpoint;
  for (int i; scene.shape_vec.size(); i++)
  {
    auto object = scene.shape_vec[i].get();
    auto Hit = object->intersect(shadow);
    if (Hit.intersect)
    {
      return {0, 0, 0};
    }
    Color mka = {Material->ka.r * scene.light_vec[1].get()->brightness, Material->ka.g * scene.light_vec[1].get()->brightness, Material->ka.b * scene.light_vec[1].get()->brightness};
    return mka;
  }
}
void Renderer::render()
{
  std::cout<<"Hallo?";
  Material m{{"red"},{1,0,0},{1,0,0},{1,0,0},1.0f};
  std::shared_ptr<Material>materia =std::make_shared<Material>(m);
  Box b{{"rbottom"},{materia},{-100,-80,-200},{100,80,-100}};
  Light l{{"Sun"},{1000,700,0},{0.2f,0.2f,0.2f},100};
  Camera camera{{"eye"},45.0f};
  Render render{{"eye"},{"image.ppm"},480,320};
  std::shared_ptr<Shape>bo=std::make_shared<Box>(b);
  std::vector<std::shared_ptr<Shape>>box;
  box.push_back(bo);
  std::shared_ptr<Light>ligh=std::make_shared<Light>(l);
  std::vector<std::shared_ptr<Light>>light;
  light.push_back(ligh);
  std::map<std::string,std::shared_ptr<Material>>material;
  material.insert(std::make_pair("red",materia));
  Scene scene{box,light,material,camera,{"white",{1,1,1}},render};

  std::cout<<"starting to render";
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x, y);
      p.color = trace(raycast());
      //std::cout<<p.color.r;
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
