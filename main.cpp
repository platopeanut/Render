#include "display/win32.h"
#include "graphics/common.h"

void render() {
    Camera camera(Vec3(0,0,0),
                  Vec3(0,0,-1),
                  Vec3(0,1,0), WIDTH, HEIGHT, 1.0, 0.1, 100);
    Scene scene;
    Light* pointLight = (Light*) new PointLight(Color(1, 1, 1), Vec3(-30, 15, -40));
    Light* ambientLight = (Light*) new AmbientLight(Color(0.1, 0.1, 0.1));
    scene.addLight(pointLight);
    scene.addLight(ambientLight);
    Material* material = (Material*) new BasicMaterial(Color(1,0,0));
    Surface* s1 = (Surface*) new Sphere(Vec3(-10, 0, -40), 10, material);
    scene.addSurface(s1);
    Surface* s2 = (Surface*) new Sphere(Vec3(10, 0, -40), 10, material);
    scene.addSurface(s2);
//    camera.rasterDeepImage(pFrameBuffer, scene);
    camera.shadeRay(pFrameBuffer, scene);
}