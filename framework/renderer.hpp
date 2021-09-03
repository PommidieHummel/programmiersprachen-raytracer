// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "scene.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include <string>
#include <glm/glm.hpp>
#include <map>
#include <vector>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render(Scene const& scene);
  Ray raycast(Scene const& scene);
  
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  Scene scene_;
  PpmWriter ppm_;
};

Color trace(Ray const& ray,Scene const& scene);
Color shade(Ray const& r,Hitpoint t,Scene const& scene);
#endif // #ifndef BUW_RENDERER_HPP
