#include "display/win32.h"
#include "graphics/common.h"

Camera* camera;
Scene* scene;
PointLight* pointLight;

void init() {
    camera = new Camera(Vec3(0,0,0),
                        Vec3(0,0,-1),
                        Vec3(0,1,0), WIDTH, HEIGHT, 1.0, 0.1, 100);
    scene = new Scene;
    pointLight = new PointLight(Color(1, 1, 1), Vec3(-30, 15, -40));
    Light* ambientLight = (Light*) new AmbientLight(Color(0.1, 0.1, 0.1));
    scene->addLight((Light*)pointLight);
    scene->addLight(ambientLight);
    Material* red = (Material*) new BasicMaterial(Color(1, 0, 0));
    Material* white = (Material*) new BasicMaterial(Color(1, 1, 1));
    Surface* s1 = (Surface*) new Sphere(Vec3(-10, 0, -40), 10, red);
    Surface* s2 = (Surface*) new Sphere(Vec3(10, 0, -40), 10, red);
    Surface* ground1 = (Surface*) new Triangle(Vec3(-50,-10,-1), Vec3(50,-10,-1), Vec3(-50,-10,-100), white);
    Surface* ground2 = (Surface*) new Triangle(Vec3(-50,-10,-100), Vec3(50,-10,-1), Vec3(50,-10,-100), white);
    scene->addSurface(s1);
    scene->addSurface(s2);
    scene->addSurface(ground1);
    scene->addSurface(ground2);
}

void destroy() {
    delete camera;
    delete scene;
}

void render() {
//    camera.rasterDeepImage(pFrameBuffer, scene);
    camera->shadeRay(pFrameBuffer, *scene);
}

bool onKeyDown(WPARAM wParam) {
    switch (wParam) {
        case 'A':
            pointLight->p.x -= 1;
            break;
        case 'D':
            pointLight->p.x += 1;
            break;
        case 'W':
            pointLight->p.z += 1;
            break;
        case 'S':
            pointLight->p.z -= 1;
            break;
        case 'Q':
            pointLight->p.y -= 1;
            break;
        case 'E':
            pointLight->p.y += 1;
            break;
        default:
            return false;
    }
    render();
    return true;
}