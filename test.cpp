#include "geometry.h"
#include <iostream>

int main()
{
    Camera camera(Vec3(0,0,0),
                  Vec3(0,0,-1),
                  Vec3(0,1,0), 600, 400, 1.0);
    Ray ray;
    std::cout << ray.origin << "\t" << ray.direction << std::endl;
    camera.generateViewingRay(0, 0, &ray);
    std::cout << ray.origin << "\t" << ray.direction << std::endl;
}