#include <windows.h>
#include <gl/gl.h>
#include "location.h"

float vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};


void Scene(int n)
{
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        /*3 задание отрисовка шахматной доски*/
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

        /*Линии 1 задание*/
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
}
