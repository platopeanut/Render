#include "display/win32.h"
#include "graphics/common.h"

void render() {
    int i = 0;
    for (int y = 0; y < HEIGHT; ++y) {
        Byte r = y * 1.0 / HEIGHT * 255;
        for (int x = 0; x < WIDTH; ++x) {
            Byte g = x * 1.0 / WIDTH * 255;
            pFrameBuffer[i++] = 0;
            pFrameBuffer[i++] = g;
            pFrameBuffer[i++] = r;
            pFrameBuffer[i++] = 0;
        }
    }
}