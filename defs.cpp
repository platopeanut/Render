#include "defs.h"
#include "geometry.h"

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
    std::vector<Surface*> geometries;
    Surface* s1 = (Surface*) new Sphere(Vec3(0, 0, -50), 20);
    geometries.push_back(s1);
    Surface* s2 = (Surface*) new Sphere(Vec3(10, 10, -30), 20);
    geometries.push_back(s2);
    camera.rasterDeepImage(pFrameBuffer, geometries);
}