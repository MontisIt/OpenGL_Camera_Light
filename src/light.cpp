
#include <windows.h>
#include <gl/gl.h>
#include "math.h"
#include "light.h"
#include "location.h"


using namespace std;


//��������� �����:

void Init_Light()
{
 glEnable(GL_LIGHTING); //����� ��������� ��� ����� ������������
 glEnable(GL_LIGHT0);
 glEnable(GL_COLOR_MATERIAL);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 glShadeModel(GL_SMOOTH);//�������� �����

 GLfloat light_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //���������
 GLfloat light_diffuse[] = { 1, 1, 1, 1 }; //���������
 GLfloat light_specular[] = { 0.2f, 0.2f, 0.2f, 32.0f }; //���������

 glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90); // ����� ��� ������������� ���������
 glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
 glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8.0); // ����������
 glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
 glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

//��������� ���������:
void Init_Material()
{
    glEnable(GL_COLOR_MATERIAL); //���������� �������������
    //���������
    glShadeModel(GL_SMOOTH); // ���������� �������
    GLfloat material_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat material_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 64.0f };
    GLfloat material_shininess[] = { 50.0f }; //����� ���������

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);//GL_AMBIENT ���������� ����
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);//GL_DIFFUSE ���� ���������� ����
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);//GL_SPECULAR ���������� ����
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);//GL_SHININESS ������� ����������� �����


}

//��������� ���������:
void Init_Material_transparency()
{
    glEnable(GL_COLOR_MATERIAL); //���������� �������������
    //���������
    glShadeModel(GL_SMOOTH); // ���������� �������

    GLfloat material_specular[] = { 1.0f, 1.0f, 1.0f, 64.0f };
    GLfloat material_shininess[] = { 50.0f }; //����� ���������



    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);//GL_SPECULAR ���������� ����
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);//GL_SHININESS ������� ����������� �����


}


void LightOverlord(float theta)
{
    glPushMatrix();
    //GLfloat light_position[] = { 0, 0, 1,  0 };
    GLfloat light_position[] = { 8, 8, 8,  1 }; //������� ���������//���� ���� �� �������� ����� �� ���������
    GLfloat light_spot_direction[] = {0, 0, -8}; // ������� ����
    light_position[0]=(8*cos(theta));
    light_position[1]=(8*sin(theta));
    light_position[2]=8;
    light_spot_direction[0] = 0;
    light_spot_direction[1] = 0;
    light_spot_direction[2] = -8;
    DrawCube(light_position[0],light_position[1],light_position[2],1,  1,1,1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);//��� ����� ����
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
    glPopMatrix();
}
