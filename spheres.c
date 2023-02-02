#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

static GLfloat x_1 = 0.0;
static GLfloat y_1 = 0.0;
static GLfloat x_2 = 0.5;
static GLfloat y_2 = 0.5;
static GLfloat angle = 0.0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(x_1, y_1, 0.0);
    glutSolidSphere(0.1, 20, 16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x_2, y_2, 0.0);
    glutSolidSphere(0.1, 20, 16);
    glPopMatrix();
    glutSwapBuffers();
}

void animate(void)
{
    angle += 0.01;
    x_1 = cos(angle) * 0.5;
    y_1 = sin(angle) * 0.5;
    x_2 = cos(angle + PI) * 0.5;
    y_2 = sin(angle + PI) * 0.5;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Two Spheres");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();
    return 0;
}

