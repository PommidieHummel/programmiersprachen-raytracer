#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "color.hpp"
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "ambient.hpp"
#include "light.hpp"
#include "render.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

struct Scene
{
    std::vector<std::shared_ptr<Shape>> shape_vec;
    std::vector<std::shared_ptr<Light>> light_vec;
    std::map<std::string, std::shared_ptr<Material>> material_map;
    Camera camera;
    Ambient ambient;
    Render render;
};

Scene sdfReader(std::string const& sdfFile);

#endif