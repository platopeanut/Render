#include "display/win32.h"
#include "graphics/transformation.h"


CubeFrame* cubeFrame;

void init() {
    cubeFrame = new CubeFrame(Vec4(0, 0, -3, 0), 2);
    Mat4 M_modeling, M_perspToOrtho, M_ortho, M_viewport;
    M_modeling = Transformation::transform(0,0,-3)
                 * Transformation::rotateX(30)
                 * Transformation::rotateY(30)
                 * Transformation::transform(0,0,3);
    Viewing::perspToOrtho(M_perspToOrtho, -1, -10);
    Viewing::orthoProject(M_ortho, -2, 2, -2, 2, -1, -10);
    Viewing::viewport(M_viewport, WIDTH, HEIGHT);
    cubeFrame->transform(M_viewport * M_ortho * M_perspToOrtho * M_modeling);
    cubeFrame->divideW_();
    cubeFrame->show();
}

void destroy() {
    delete cubeFrame;
}

void render() {
    int k = 0;
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 0;
        }
    }
    cubeFrame->render(pFrameBuffer, WIDTH, HEIGHT);
}

bool onKeyDown(WPARAM wParam) {
    switch (wParam) {
        case 'A':
            break;
        case 'D':
            break;
        case 'W':
            break;
        case 'S':
            break;
        default:
            return false;
    }
    render();
    return true;
}