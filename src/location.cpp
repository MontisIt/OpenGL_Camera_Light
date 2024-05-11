#include <windows.h>
#include <gl/gl.h>
#include "math.h"
#include "location.h"
#include "light.h"

using namespace std;

float vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};

GLfloat normal[]={
      0.0f,1.0f,0.0f,
      0.0f,1.0f,0.0f,
      0.0f,1.0f,0.0f,
      0.0f,1.0f,0.0f};

float normal_vert[]={-1,-1,3, 1,-1,3, 1,1,3, -1,1,3};

void Scene(int n)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        glNormalPointer(GL_FLOAT,0,normal_vert);
        /*отрисовка шахматной доски*/
        for (int i = -n; i < n; i++)
        {
            for (int j = -n; j < n; j++)
            {
                glPushMatrix();

                    if ((i+j) % 2 == 0) glColor3f(0.02, 0.02, 0.02);
                    else glColor3f(1, 1, 1);
                    glTranslatef(i*2, j*2, 0);

                    glDrawArrays(GL_TRIANGLE_FAN, 0 ,4);
                glPopMatrix();
            }
        }

        /*Линии*/
        glLineWidth(5);
        glBegin(GL_LINES);
            /*Линия 1*/
            glColor3f(1,0,0);
            glVertex3f(0, 0, 1);
            glVertex3f(0, 1, 1);
            /*Линия 2*/
            glColor3f(0,1,0);
            glVertex3f(0, 0, 1);
            glVertex3f(1, 0, 1);
            /*Линия 3*/
            glColor3f(0,0,1);
            glVertex3f(0, 0, 1);
            glVertex3f(0, 0, 2);
        glEnd();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawCube(GLfloat x,GLfloat y,GLfloat z,GLfloat k,float r,float g,float b){

GLfloat vertices[] = {
 -0.5f/k+x, -0.5f/k+y, -0.5f/k+z,
 0.5f/k+x, -0.5f/k+y, -0.5f/k+z,
 0.5f/k+x, 0.5f/k+y, -0.5f/k+z,
 -0.5f/k+x, 0.5f/k+y, -0.5f/k+z,
 -0.5f/k+x, -0.5f/k+y, 0.5f/k+z,
 0.5f/k+x, -0.5f/k+y, 0.5f/k+z,
 0.5f/k+x, 0.5f/k+y, 0.5f/k+z,
 -0.5f/k+x, 0.5f/k+y, 0.5f/k+z
};

GLuint indices[] = {
 0, 1, 2,
 2, 3, 0,

 1, 5, 6,
 6, 2, 1,

 7, 6, 5,
 5, 4, 7,

 4, 0, 3,
 3, 7, 4,

 4, 5, 1,
 1, 0, 4,

 3, 2, 6,
 6, 7, 3
};
GLfloat normals[] = {
 0.0f, 0.0f, -1.0f,
 0.0f, 0.0f, -1.0f,
 0.0f, 0.0f, -1.0f,
 0.0f, 0.0f, -1.0f,

 0.0f, 0.0f, 1.0f,
 0.0f, 0.0f, 1.0f,
 0.0f, 0.0f, 1.0f,
 0.0f, 0.0f, 1.0f,

 -1.0f, 0.0f, 0.0f,
 -1.0f, 0.0f, 0.0f,
 -1.0f, 0.0f, 0.0f,
 -1.0f, 0.0f, 0.0f,

 1.0f, 0.0f, 0.0f,
 1.0f, 0.0f, 0.0f,
 1.0f, 0.0f, 0.0f,
 1.0f, 0.0f, 0.0f,

 0.0f, -1.0f, 0.0f,
 0.0f, -1.0f, 0.0f,
 0.0f, -1.0f, 0.0f,
 0.0f, -1.0f, 0.0f,

 0.0f, 1.0f, 0.0f,
 0.0f, 1.0f, 0.0f,
 0.0f, 1.0f, 0.0f,
 0.0f, 1.0f, 0.0f
//(0,0,-1) (0,0,1) (-1,0,0) (1,0,0) (0,-1,0) (0,1,0) как в методичке
//(0,-1,0) (0,1,0) (-1,0,0) (1,0,0) (0,0,-1) (0,0,1) №1 y/z
//(0,0,-1) (0,0,1) (0,-1,0) (0,1,0) (-1,0,0) (1,0,0) №2 y/x
};
Init_Material();
glColor3f(r,g,b);
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);
glVertexPointer(3, GL_FLOAT, 0, vertices);
glNormalPointer(GL_FLOAT, 0, normals);
glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
}


void DrawFigure(float radius1,float radius2, float height, int sides, float xPos, float yPos, float zPos, float transparency) {
    float angle = (2 * M_PI) / sides;  // Угол между соседними вершинами
    float halfHeight = height / 2.0f;  // Половина высоты призм
    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glBegin(GL_TRIANGLES);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat mat_diffuse[] = { 0.2f, 0.2f, 0.2f, transparency };
        GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, transparency };
        //GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        //GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        //glColor4f(0.3, 0.8, 0, transparency);
        glColor4f(0.2, 1, 1, transparency);
    for (int i = 0; i < sides; ++i) {

        // Вершины нижнего сечения
        float x1 = radius1 * cos(i * angle);
        float y1 = radius1 * sin(i * angle);
        float z1 = -halfHeight;

        float x2 = radius1 * cos((i + 1) * angle);
        float y2 = radius1 * sin((i + 1) * angle);
        float z2 = -halfHeight;

        // Вершины верхнего сечения
        float x3 = radius2 * cos(i * angle);
        float y3 = radius2 * sin(i * angle);
        float z3 = halfHeight;

        float x4 = radius2 * cos((i + 1) * angle);
        float y4 = radius2 * sin((i + 1) * angle);
        float z4 = halfHeight;


        Init_Material_transparency();
        // Боковая грань

        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(-x1, -y1, -z1);

        glVertex3f(-x3, -y3, -(z3 + height));

        glVertex3f(-x4, -y4, -(z4 + height));

        glVertex3f(-x1, -y1, -z1);

        glVertex3f(-x4, -y4, -(z4 + height));

        glVertex3f(-x2, -y2, -z2);


        // Крыша
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -(z3 + height));
        glVertex3f(-x3, -y3, -(z3 + height));
        glVertex3f(-x4, -y4, -(z4 + height));

        // Дно

        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -z1);
        glVertex3f(-x1, -y1, -z1);
        glVertex3f(-x2, -y2, -z2);

    }
    glEnd();

    glPopMatrix();
}
