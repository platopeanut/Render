#include "display/win32.h"
#include "graphics/transformation.h"


CubeFrame* cubeFrame;
Mat4 M_modeling, M_perspToOrtho, M_ortho, M_viewport;
float xAngle = 30;
float yAngle = 30;


void init() {
    cubeFrame = new CubeFrame(Vec4(0, 0, -3, 0), 2);
    Viewing::perspToOrtho(M_perspToOrtho, -1, -10);
    Viewing::orthoProject(M_ortho, -2, 2, -2, 2, -1, -10);
    Viewing::viewport(M_viewport, WIDTH, HEIGHT);
}

void destroy() {
    delete cubeFrame;
}

void render() {
    auto* transformedCubeFrame = new CubeFrame();
    M_modeling = Transformation::transform(0,0,-3)
                 * Transformation::rotateX(xAngle)
                 * Transformation::rotateY(yAngle)
                 * Transformation::transform(0,0,3);
    cubeFrame->transform(M_viewport * M_ortho * M_perspToOrtho * M_modeling, transformedCubeFrame);
    transformedCubeFrame->divideW_();
    int k = 0;
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 255;
            pFrameBuffer[k++] = 0;
        }
    }
    transformedCubeFrame->render(pFrameBuffer, WIDTH, HEIGHT);
    delete transformedCubeFrame;
}

bool onKeyDown(WPARAM wParam) {
    switch (wParam) {
        case 'A': {
            yAngle -= 2;
        }
            break;
        case 'D': {
            yAngle += 2;
        }
            break;
        case 'W': {
            xAngle -= 2;
        }
            break;
        case 'S': {
            xAngle += 2;
        }
            break;
        default:
            return false;
    }
    render();
    return true;
}