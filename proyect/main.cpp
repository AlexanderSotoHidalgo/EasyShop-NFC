#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.6f, 0.6f, 1.0f); // Color de los triángulos

        glVertex2f(-0.6f, 0.4f);  // v0
        glVertex2f(-0.5f, -0.3f); // v1
        glVertex2f(-0.2f, 0.5f);  // v2
        glVertex2f(0.0f, -0.4f);  // v3
        glVertex2f(0.3f, 0.3f);   // v4
        glVertex2f(0.6f, -0.2f);  // v5
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
    glColor3f(0.0f, 0.0f, 0.0f);         // Color de dibujo
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);    // Proyección 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Triangle Strip Example");
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
