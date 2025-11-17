#include <GL/glut.h>
#include <cmath>

const int LADOS = 15;
const float PI = 3.14159265f;
const float RADIO_INTERNO = 4.0f;
const float RADIO_EXTERNO = 9.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Color rojo

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= LADOS; ++i) {
        float ang = 2 * PI * i / LADOS;
        float cosA = cos(ang);
        float sinA = sin(ang);

        // Punto externo
        glVertex2f(RADIO_EXTERNO * cosA, RADIO_EXTERNO * sinA);
        // Punto interno
        glVertex2f(RADIO_INTERNO * cosA, RADIO_INTERNO * sinA);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1); // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Anillo de 15 lados (polígono hueco)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
