#include <GL/glut.h>
#include <cmath>
#include <iostream>

float radio = 50.0f;  // Valor inicial (puede ser modificado desde consola)

void init() {
    glClearColor(0.8f, 1.0f, 0.8f, 1.0f); // Color de fondo verde claro
    glColor3f(1.0f, 0.0f, 0.0f);          // Color para el arco: rojo
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);     // Proyección ortogonal
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibuja la grilla
    glColor3f(0.0f, 0.8f, 0.0f);  // Verde
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i += 5) {
        glVertex2i(i, -100);
        glVertex2i(i, 100);
        glVertex2i(-100, i);
        glVertex2i(100, i);
    }
    glEnd();

    // Dibuja los ejes coordenados
    glColor3f(0.0f, 0.0f, 1.0f);  // Azul
    glBegin(GL_LINES);
        glVertex2i(-100, 0);
        glVertex2i(100, 0);
        glVertex2i(0, -100);
        glVertex2i(0, 100);
    glEnd();

    // Dibuja el arco de la circunferencia entre pi/4 y pi/2
    glColor3f(1.0f, 0.0f, 0.0f);  // Rojo
    glBegin(GL_POINTS);
    for (float theta = M_PI / 4; theta <= M_PI / 2; theta += 0.01f) {
        float x = radio * cos(theta);
        float y = radio * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    std::cout << "Ingrese la longitud del radio: ";
    std::cin >> radio;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CIRCUNFERENCIA CON REPRESENTACION PARAMETRICA DE CENTRO CERO");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
