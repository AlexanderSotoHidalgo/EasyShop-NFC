#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

// === VARIABLES ===
const float PI = 3.14159265359f;

// === FUNCIONES COMUNES ===
void LINEA(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
    glEnd();
}

// === EJERCICIO 1: DDA con cuadrantes ===
void display1() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    glColor3f(1, 0, 0); LINEA(0, 0, 100, 100);     // Primer cuadrante
    glColor3f(0, 1, 0); LINEA(0, 0, -100, 100);    // Segundo cuadrante
    glColor3f(0, 0, 1); LINEA(0, 0, -100, -100);   // Tercer cuadrante
    glColor3f(1, 1, 0); LINEA(0, 0, 100, -100);    // Cuarto cuadrante
    glEnd();

    glutSwapBuffers();
}

void init1() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

// === EJERCICIO 2: Polígono estrella de 7 lados salto 2 ===
void display2() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(0, 200); glVertex2i(400, 200); // eje X
    glVertex2i(200, 0); glVertex2i(200, 400); // eje Y
    glEnd();

    const int N = 7;
    const int K = 2;
    const float R = 150.0f;
    const float centroX = 200.0f;
    const float centroY = 200.0f;

    glColor3f(0.5, 0.0, 0.5);
    float angulo_inicial = PI / 2 + PI / 3;
    float x[N], y[N];

    for (int i = 0; i < N; ++i) {
        float ang = angulo_inicial + 2 * PI * i / N;
        x[i] = centroX + R * cos(ang);
        y[i] = centroY + R * sin(ang);
    }

    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    int idx = 0;
    for (int i = 0; i < N; ++i) {
        glVertex2f(x[idx], y[idx]);
        idx = (idx + K) % N;
    }
    glEnd();

    glutSwapBuffers();
}

void init2() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
}

// === EJERCICIO 3: Polígono estrellado normalizado ===
const int N = 9;
const int STEP = 4;
const float RADIUS = 0.9f;

void display3() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
        glVertex2f(0.0f, -1.0f); glVertex2f(0.0f, 1.0f);
    glEnd();

    float x[N], y[N];
    for (int i = 0; i < N; ++i) {
        float angle = 2 * PI * i / N;
        x[i] = RADIUS * cos(angle);
        y[i] = RADIUS * sin(angle);
    }

    glColor3f(0.6f, 0.1f, 0.4f);
    glBegin(GL_LINE_LOOP);
        int index = 0;
        do {
            glVertex2f(x[index], y[index]);
            index = (index + STEP) % N;
        } while (index != 0);
    glEnd();

    glColor3f(0, 0, 0);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < N; ++i)
        glVertex2f(x[i], y[i]);
    glEnd();

    glutSwapBuffers();
}

void init3() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.2, 1.2, -1.2, 1.2);
}

// === EJERCICIO 4: Eneágono con salto 2 ===
void drawSkipOnePolygon(int n, int radius, int centerX, int centerY) {
    if (n < 3) return;
    int step = 2;
    std::vector<std::pair<int,int>> V;
    for (int i = 0; i < n; ++i) {
        float ang = 2*PI*i/n - PI/2;
        int x = centerX + int(radius * cos(ang));
        int y = centerY + int(radius * sin(ang));
        V.emplace_back(x,y);
    }

    glColor3f(0.6f, 0.1f, 0.4f);
    for (int i = 0, cur = 0; i < n; ++i) {
        int nxt = (cur + step) % n;
        LINEA(V[cur].first, V[cur].second, V[nxt].first, V[nxt].second);
        cur = nxt;
    }

    glPointSize(6.0f);
    glColor3f(0.4f, 0.0f, 0.3f);
    glBegin(GL_POINTS);
    for (auto &p : V) glVertex2i(p.first, p.second);
    glEnd();
}

void display4() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.6f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2i(50, 50);
        glVertex2i(750, 50);
        glVertex2i(750, 550);
        glVertex2i(50, 550);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
        glVertex2i(50, 300); glVertex2i(750, 300);
        glVertex2i(400, 50); glVertex2i(400, 550);
    glEnd();

    drawSkipOnePolygon(9, 200, 400, 300);

    glFlush();
}

void init4() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
}

// === CONTROLADOR DE TECLADO ===
void keyboard(unsigned char key, int, int) {
    switch (key) {
        case '1': init1(); glutDisplayFunc(display1); break;
        case '2': init2(); glutDisplayFunc(display2); break;
        case '3': init3(); glutDisplayFunc(display3); break;
        case '4': init4(); glutDisplayFunc(display4); break;
        case '5': init4(); glutDisplayFunc(display4); break;
        case 27:  exit(0); break; // ESC
    }
    glutPostRedisplay();
}

// === MAIN ===
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Menu de Ejercicios OpenGL (1-5)");

    std::cout << "=== OPCIONES ===\n"
              << "1: DDA con cuadrantes\n"
              << "2: Poligono estrella 7 lados (salto 2)\n"
              << "3: Poligono estrellado normalizado\n"
              << "4: Eneagono con salto 2\n"
              << "5: Eneagono con salto 2 (repetido)\n"
              << "ESC: Salir\n";

    init1();
    glutDisplayFunc(display1);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

