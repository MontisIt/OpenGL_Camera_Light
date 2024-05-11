#include <windows.h>
#include <gl/gl.h>
#include <iostream>
#include "math.h"
#include "camera.h"
#include "location.h"
#include "light.h"

using namespace std;

float theta = 0.0f;


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);



void MoveCamera(){
    Camera_MoveDirectional(
    GetKeyState('W')< 0 ? 1 : GetKeyState('S')< 0 ? -1 : 0,
    GetKeyState('D')< 0 ? 1 : GetKeyState('A')< 0 ? -1 : 0,
    0.1);
    Camer_AutoMoveByMouse(400,400,0.1);
    Camera_Rotation(0, 0);
    Camera_Apply();
}

void WndResize(int x, int y){
    glViewport(0,0,x,y); //перестраивает размеры окна
    float k=x/(float)y; //соотношение сторон
    float sz = 0.1; //единица размера

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//загрузка единичной матрицы
    glFrustum(-k*sz, k*sz, -sz, sz, sz*2, 100); //установка перспективной проэкции
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          700,
                          500,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    RECT rct;
    GetClientRect(hwnd,&rct);
    WndResize(rct.right,rct.bottom);



    //glFrustum(-1,1, -1,1, 2,80);
    glEnable(GL_DEPTH_TEST); /*тест глубины*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //Init_Material();
    Init_Light();



    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/*тест глубины*/



            glPushMatrix();

            if (GetForegroundWindow()==hwnd) MoveCamera();
                glPushMatrix();

                    LightOverlord(theta);
                    DrawCube(0,-8,1, 0.5, 0.5,0.5,1);
                    Scene(10);
                        //glRotatef(45,0,0,1);
                        //drawPrism(1,1, 2, 4,  0,5,1, 1);
                        //glRotatef(45*2,0,0,1);
                        //drawPrism(1,1, 2, 4,  2,4.5,1, 0.9);
                        //drawPrism(1,1, 2, 4,  4,4,1, 0.8);
                       // drawPrism(1,1, 2, 4, 2,3.5,1, 0.7);
                        //drawPrism(1,1, 2, 4, 8,3,1, 0.6);
                        //drawPrism(1,1, 2, 4, 10,2.5,1, 0.5);
                        //drawPrism(1,1, 2, 4, 12,2,1, 0.4);
                        //drawPrism(1,1, 2, 4, 14,1.5,1, 0.3);
                        //DrawFigure(1,1, 1, 4, 15.5,5.5,1, 1);
                        //DrawFigure(1,1, 2, 4, 16,0.5,1, 0.1);
                        //DrawFigure(1,1, 2, 4, 18,0,1, 0);
                        GLint a=5;
                        GLint b=1;
                        GLfloat alfa=(45*M_PI)/180;
                        float k=1;
                        for(int i=0;i<7;i++){
                           //glRotatef(45*i,0,0,1);
                           DrawFigure(1,1, 1, 9,  a*sin(M_PI_4*i)+b,a*cos(M_PI_4*i)+b,1, k);
                           k-=0.1;
                           //cout<<a*cos(M_PI_4*i)+b<<endl;
                           //cout<<a*sin(M_PI_4*i)+b<<endl;
                        }
                        //cout<<"--------------------"<<endl;


                glPopMatrix();
            glPopMatrix();

            SwapBuffers(hDC);

            theta += -0.01;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}


