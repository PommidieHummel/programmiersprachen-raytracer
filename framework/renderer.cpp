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

Ray raycast(Scene const& scene) {

}
Color trace(Ray const &ray, Scene const& scene)
{  
  Shape *closest_o;
  Hitpoint closest_t;
  for (int i;scene.shape_vec.size();i++)
  {
    auto object =scene.shape_vec[i].get();
    Hitpoint t = object->intersect(ray);
    float closest_t=0;
    
    if(t.distance<closest_t){
      closest_t = t.distance;
      closest_o = object;
    }
  }
  if (closest_o !=0){
    return shade(scene,ray,closest_t);
  }
  else {
    return scene.ambient.color;
  }

} 
Color shade(Scene const& scene,Ray const& ray,Hitpoint t){
  auto scenelight = scene.light_vec[1].get();
  Ray shadow;
  Map::const_iterator it =scene.material_map.begin(),
  auto material = ->second;
  shadow.direction = scenelight->pos - t.hitpoint;
  for(int i;scene.shape_vec.size();i++){
    auto object= scene.shape_vec[i].get();
    auto Hit =object->intersect(shadow);
    if( Hit.intersect){
      return {0,0,0};
    }
    return scene.material_map->second.ka * scene.light_vec[1].get()->brightness;
  }
  


}
void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y)
  {
    for (unsigned x = 0; x < width_; ++x)
    {
      Pixel p(x, y);
      p.color =trace(Scene);

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
