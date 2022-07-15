#ifndef RENDER_DEFS_H
#define RENDER_DEFS_H

#include <windows.h>
#define WNDCLASS_NAME TEXT("Window Class")
#define WINDOW_NAME TEXT("Window Name")
#define WINDOW_POS_X CW_USEDEFAULT
#define WINDOW_POS_Y CW_USEDEFAULT
//#define WIDTH CW_USEDEFAULT
//#define HEIGHT CW_USEDEFAULT
#define WIDTH 600
#define HEIGHT 600

typedef unsigned char Byte;
extern HANDLE hConsole;
extern HDC hDC;
extern HDC hMemDC;
extern HBITMAP hBitmap;
extern HBITMAP hOldBitmap;
extern Byte* pFrameBuffer;

#define Log(info) WriteConsole(hConsole, info, sizeof(info), NULL, NULL)

/* External Interface */
void render();

#endif //RENDER_DEFS_H
