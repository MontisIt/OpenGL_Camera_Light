
#include <windows.h>
#include <gl/gl.h>
#include "math.h"
#include "light.h"
#include "location.h"


using namespace std;


//Настройка света:

void Init_Light()
{
 glEnable(GL_LIGHTING); //общее освещения для всего пространства
 glEnable(GL_LIGHT0);
 glEnable(GL_COLOR_MATERIAL);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 glShadeModel(GL_SMOOTH);//источник света

 GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //параметры
 GLfloat light_diffuse[] = { 1, 1, 1, 1 }; //параметры
 GLfloat light_specular[] = { 0.2f, 0.2f, 0.2f, 32.0f }; //параметры

 glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90); // конус для направленного источника
 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
 glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8.0); // экспонента
 glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
 glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

//Настройка материала:
void Init_Material()
{
    glEnable(GL_COLOR_MATERIAL); //разрешения использования
    //материала
    glShadeModel(GL_SMOOTH); // сглаживает границы
    GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 64.0f };
    GLfloat material_shininess[] = { 50.0f }; //блеск материала

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);//GL_AMBIENT рассеянный свет
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//GL_DIFFUSE тоже рассеянный свет
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);//GL_SPECULAR отраженный свет
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);//GL_SHININESS степень отраженного света


}

//Настройка материала:
void Init_Material_transparency()
{
    glEnable(GL_COLOR_MATERIAL); //разрешения использования
    //материала
    glShadeModel(GL_SMOOTH); // сглаживает границы

    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 64.0f };
    GLfloat material_shininess[] = { 50.0f }; //блеск материала



    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);//GL_SPECULAR отраженный свет
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);//GL_SHININESS степень отраженного света


}


void LightOverlord(float theta)
{
    glPushMatrix();
    //GLfloat light_position[] = { 0, 0, 1,  0 };
    GLfloat light_position[] = { 8, 8, 8,  1 }; //позиция источника//свет есть но источник снизу по диагонали
    GLfloat light_spot_direction[] = {0, 0, -8}; // позиция цели
    light_position[0]=(8*cos(theta));
    light_position[1]=(8*sin(theta));
    light_position[2]=8;
    light_spot_direction[0] = 0;
    light_spot_direction[1] = 0;
    light_spot_direction[2] = -8;
    DrawCube(light_position[0],light_position[1],light_position[2],1,  1,1,1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//Где стоит свет
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
    glPopMatrix();
}
