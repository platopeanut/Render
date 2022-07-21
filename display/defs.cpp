#include "defs.h"
#include "../graphics/common.h"

HANDLE hConsole;
HDC hDC;
HDC hMemDC;
HBITMAP hBitmap;
HBITMAP hOldBitmap;
Byte* pFrameBuffer;

//void render() {
//    int i = 0;
//    for (int y = 0; y < HEIGHT; ++y) {
//        Byte r = y * 1.0 / HEIGHT * 255;
//        for (int x = 0; x < WIDTH; ++x) {
//            Byte g = x * 1.0 / WIDTH * 255;
//            pFrameBuffer[i++] = 0;
//            pFrameBuffer[i++] = g;
//            pFrameBuffer[i++] = r;
//            pFrameBuffer[i++] = 0;
//        }
//    }
//}

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