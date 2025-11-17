#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include <iostream>
using namespace std;

int opc = 0;

void inicio() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

void menu(int value) {
    opc = value;
    glutPostRedisplay();
}

void generarCuadricula(int x0, int y0, int x1, int y1){
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(1);

    for(int x = x0; x <= x1; x++){
        glBegin(GL_LINES);
            glVertex2f(x,y0);
            glVertex2f(x,y1);
        glEnd();
    }

    for(int y = y0; y <= y1; y++){
        glBegin(GL_LINES);
            glVertex2f(x0,y);
            glVertex2f(x1,y);
        glEnd();
    }

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(0,y0);
        glVertex2f(0,y1);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(x0,0);
        glVertex2f(x1,0);
    glEnd();
}

void pintarPixel(int x, int y, int tam){
    glColor3f(1.0,0.0,0.0);
    glPointSize(tam);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void algoritmoBasico(int x0, int y0, int x1, int y1){
    int x, y;
    float dx,dy,m;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    float b = y0 - m*x0;
    y = y0;
    for(x = x0; x<=x1; x++){
        pintarPixel(x,round(y),5);
        y = m*x + b;
    }
}

void algoritmoBasicoInvertido(int x0, int y0, int x1, int y1){
    int x, y;
    float dx,dy,m;
    dx = x0 - x1;
    dy = y0 - y1;
    m = dy / dx;
    float b = y0 - m*x0;
    y = y0;
    for(x = x0; x>=x1; x--){
        pintarPixel(x,round(y),5);
        y = m*x + b;
    }
}

void bresenhamVertical(int x0, int y0, int x1, int y1){
    if (y0 > y1){
        int aux = x0;
        x0 = x1;
        x1 = aux;
        aux = y0;
        y0 = y1;
        y1 = aux;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    int dir = 0;

    if (dx < 0){
        dir = -1;
    }
    else{
        dir = 1;
    }

    dx *= dir;

    if(dy != 0){
        int x = x0;
        int p = 2*dx - dy;
        for(int i = 0; i < dy + 1; i++){
            pintarPixel(x, y0 + i, 5);
            if(p >= 0){
                x += dir;
                p -= 2*dy;
            }
            p += 2*dx;
        }
    }
}

void bresenhamHorizontal(int x0, int y0, int x1, int y1){
    if (x0 > x1){
        int aux = x0;
        x0 = x1;
        x1 = aux;
        aux = y0;
        y0 = y1;
        y1 = aux;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    int dir = 0;

    if (dy < 0){
        dir = -1;
    }
    else{
        dir = 1;
    }

    dy *= dir;

    if(dx != 0){
        int y = y0;
        int p = 2*dy - dx;
        for(int i = 0; i < dx + 1; i++){
            pintarPixel(x0 + i, y, 5);
            if(p >= 0){
                y += dir;
                p -= 2*dx;
            }
            p += 2*dy;
        }
    }
}

void bresenham(int x0, int y0, int x1, int y1){
    if (abs(x1-x0) > abs(y1-y0))
        bresenhamHorizontal(x0,y0,x1,y1);
    else
        bresenhamVertical(x0,y0,x1,y1);
}

void dda(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float pasos = max(abs(dx), abs(dy));
    float xInc = dx / pasos;
    float yInc = dy / pasos;
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= pasos; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void pantalla() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    switch (opc) {
        case 1: {
            system("cls");
            cout << "\nAlgoritmo Básico - Primer Cuadrante\n";

            // 1. Dibujar cuadrícula verde
            glColor3f(0.7f, 1.0f, 0.7f);
            for (int i = 0; i <= 400; i += 10) {
                glBegin(GL_LINES);
                    glVertex2i(i, 0);
                    glVertex2i(i, 400);
                glEnd();
                glBegin(GL_LINES);
                    glVertex2i(0, i);
                    glVertex2i(400, i);
                glEnd();
            }

            // 2. Dibujar ejes azules
            glColor3f(0.6f, 0.6f, 1.0f);
            glBegin(GL_LINES);
                glVertex2i(0, 200);
                glVertex2i(400, 200); // Eje X
                glVertex2i(200, 0);
                glVertex2i(200, 400); // Eje Y
            glEnd();

            // 3. Algoritmo básico - línea roja desde (200,200) a (260,300)
            int x0 = 200, y0 = 200;
            int x1 = 260, y1 = 300;

            float dx = x1 - x0;
            float dy = y1 - y0;
            float m = dy / dx;
            float b = y0 - m * x0;

            glColor3f(1.0f, 0.0f, 0.0f); // Rojo
            glPointSize(3);
            glBegin(GL_POINTS);
            for (int x = x0; x <= x1; x++) {
                int y = round(m * x + b);
                glVertex2i(x, y);
            }
            glEnd();

            break;
        }

        case 2: {
            generarCuadricula(0, 0, 400, 400); // Cambiar a mismo tamaño que Case 1

            // Ajustar coordenadas (multiplicar por 10)
            algoritmoBasico(120,130,240,330); // 1er cuadrante (antes 2,3 a 14,23)
            algoritmoBasicoInvertido(-120,130,-240,330); // 2do cuadrante
            algoritmoBasicoInvertido(-120,-130,-240,-330); // 3er cuadrante
            algoritmoBasico(120,-130,240,-330); // 4to cuadrante
            break;
        }

         case 3: {

             glColor3f(0.7, 1.0, 0.7);
             glBegin(GL_LINES);
             for (int i = 0; i <= 400; i += 10) {
                 glVertex2i(i, 0); glVertex2i(i, 400);
                 glVertex2i(0, i); glVertex2i(400, i);
             }
             glEnd();


             glColor3f(0.6, 0.6, 1.0); // Azul claro
             glBegin(GL_LINES);
             glVertex2i(0, 200); glVertex2i(400, 200); // eje X
             glVertex2i(200, 0); glVertex2i(200, 400); // eje Y
             glEnd();

             // Algoritmo DDA
             float x1 = 0, y1 = 0;
             float x2 = 10, y2 = 15; // línea con pendiente > 1 (solo primer cuadrante)

             float dx = x2 - x1;
             float dy = y2 - y1;
             float pasos = std::max(abs(dx), abs(dy));
             float xInc = dx / pasos;
             float yInc = dy / pasos;
             float x = x1;
             float y = y1;

             glPointSize(4.0);
             glColor3f(1.0, 0.0, 0.0); // Rojo
             glBegin(GL_POINTS);
             for (int i = 0; i <= pasos; i++) {
                 glVertex2i(round(x) * 10 + 200, round(y) * 10 + 200); // traslación al primer cuadrante
                 x += xInc;
                 y += yInc;
             }
             glEnd();
             break;
         }

        case 4: {
            const int GRID_SIZE = 100;

            // Dibujar cuadrícula verde
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_LINES);
            for (int i = -GRID_SIZE / 2; i <= GRID_SIZE / 2; ++i) {
                glVertex2f(i / (float)(GRID_SIZE / 2), -1);
                glVertex2f(i / (float)(GRID_SIZE / 2), 1);
                glVertex2f(-1, i / (float)(GRID_SIZE / 2));
                glVertex2f(1, i / (float)(GRID_SIZE / 2));
            }
            glEnd();

            // Dibujar ejes (morado)
            glColor3f(0.5, 0.0, 1.0);
            glBegin(GL_LINES);
                glVertex2f(0, -1);
                glVertex2f(0, 1);
                glVertex2f(-1, 0);
                glVertex2f(1, 0);
            glEnd();

            // Dibujar puntos con DDA (rojo)
            glColor3f(1.0, 0.0, 0.0);
            int x1, y1, x2, y2;
            float x, y, dx, dy, steps, xInc, yInc;
            int i;

            // Línea 1 (1er cuadrante)
            x1 = 2; y1 = 2; x2 = 10; y2 = 10;
            dx = x2 - x1; dy = y2 - y1;
            steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
            xInc = dx / steps; yInc = dy / steps;
            x = x1; y = y1;
            for (i = 0; i <= steps; i++) {
                float xf = x / (GRID_SIZE / 2);
                float yf = y / (GRID_SIZE / 2);
                float s = 2.0 / GRID_SIZE;
                glBegin(GL_QUADS);
                    glVertex2f(xf, yf);
                    glVertex2f(xf + s, yf);
                    glVertex2f(xf + s, yf + s);
                    glVertex2f(xf, yf + s);
                glEnd();
                x += xInc;
                y += yInc;
            }

            // Línea 2 (2do cuadrante)
            x1 = -2; y1 = 2; x2 = -10; y2 = 10;
            dx = x2 - x1; dy = y2 - y1;
            steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
            xInc = dx / steps; yInc = dy / steps;
            x = x1; y = y1;
            for (i = 0; i <= steps; i++) {
                float xf = x / (GRID_SIZE / 2);
                float yf = y / (GRID_SIZE / 2);
                float s = 2.0 / GRID_SIZE;
                glBegin(GL_QUADS);
                    glVertex2f(xf, yf);
                    glVertex2f(xf + s, yf);
                    glVertex2f(xf + s, yf + s);
                    glVertex2f(xf, yf + s);
                glEnd();
                x += xInc;
                y += yInc;
            }

            // Línea 3 (3er cuadrante)
            x1 = -2; y1 = -2; x2 = -10; y2 = -10;
            dx = x2 - x1; dy = y2 - y1;
            steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
            xInc = dx / steps; yInc = dy / steps;
            x = x1; y = y1;
            for (i = 0; i <= steps; i++) {
                float xf = x / (GRID_SIZE / 2);
                float yf = y / (GRID_SIZE / 2);
                float s = 2.0 / GRID_SIZE;
                glBegin(GL_QUADS);
                    glVertex2f(xf, yf);
                    glVertex2f(xf + s, yf);
                    glVertex2f(xf + s, yf + s);
                    glVertex2f(xf, yf + s);
                glEnd();
                x += xInc;
                y += yInc;
            }

            // Línea 4 (4to cuadrante)
            x1 = 2; y1 = -2; x2 = 10; y2 = -10;
            dx = x2 - x1; dy = y2 - y1;
            steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
            xInc = dx / steps; yInc = dy / steps;
            x = x1; y = y1;
            for (i = 0; i <= steps; i++) {
                float xf = x / (GRID_SIZE / 2);
                float yf = y / (GRID_SIZE / 2);
                float s = 2.0 / GRID_SIZE;
                glBegin(GL_QUADS);
                    glVertex2f(xf, yf);
                    glVertex2f(xf + s, yf);
                    glVertex2f(xf + s, yf + s);
                    glVertex2f(xf, yf + s);
                glEnd();
                x += xInc;
                y += yInc;
            }
            break;
        }

        case 5:{
            system("cls");
            cout << "\nAlgoritmo de Punto Medio (Bresenham) – Primer Cuadrante\n";

            // 1. Dibujar la cuadrícula celeste
            glColor3f(0.7f, 1.0f, 1.0f); // Celeste claro
            for (int i = 0; i <= 400; i += 10) {
                glBegin(GL_LINES);
                    glVertex2i(i, 0);
                    glVertex2i(i, 400);
                glEnd();
                glBegin(GL_LINES);
                    glVertex2i(0, i);
                    glVertex2i(400, i);
                glEnd();
            }

            // 2. Dibujar ejes X y Y en morado
            glColor3f(1.0f, 0.0f, 1.0f); // Morado
            glBegin(GL_LINES);
                glVertex2i(0, 200);
                glVertex2i(400, 200);
            glEnd();
            glBegin(GL_LINES);
                glVertex2i(200, 0);
                glVertex2i(200, 400);
            glEnd();

            // 3. Algoritmo de Bresenham – línea verde desde (200,200) a (260,300)
            int x0 = 200, y0 = 200;
            int x1 = 260, y1 = 300;
            int dx = x1 - x0;
            int dy = y1 - y0;
            int x = x0;
            int y = y0;

            int d = 2 * dy - dx;
            int incrE = 2 * dy;
            int incrNE = 2 * (dy - dx);

            glColor3f(0.0f, 1.0f, 0.0f); // Verde
            glPointSize(3); // Tamaño de los puntos
            glBegin(GL_POINTS);
                glVertex2i(x, y);
            glEnd();

            while (x < x1) {
                x++;
                if (d < 0) {
                    d += incrE;
                } else {
                    d += incrNE;
                    y++;
                }
                glBegin(GL_POINTS);
                    glVertex2i(x, y);
                glEnd();
            }

            break;
        }

        case 6: {
            generarCuadricula(0, 0, 400, 400); // Cambiar a mismo tamaño que Case 1

            // Ajustar coordenadas (multiplicar por 10)
            bresenham(120,130,240,330); // 1er cuadrante
            pintarPixel(180,230,10); // Punto medio

            bresenham(-120,130,-240,330); // 2do cuadrante
            pintarPixel(-180,230,10);

            bresenham(-120,-130,-240,-330); // 3er cuadrante
            pintarPixel(-180,-230,10);

            bresenham(120,-130,240,-330); // 4to cuadrante
            pintarPixel(180,-230,10);
            break;
        }

        case 7: {
                system("cls");
                cout << "\nComparativa: Básico, DDA y Bresenham\n";

                // 1. Dibujar cuadrícula verde
                glColor3f(0.7f, 1.0f, 0.7f);
                for (int i = 0; i <= 400; i += 10) {
                    glBegin(GL_LINES);
                        glVertex2i(i, 0);
                        glVertex2i(i, 400);
                    glEnd();
                    glBegin(GL_LINES);
                        glVertex2i(0, i);
                        glVertex2i(400, i);
                    glEnd();
                }

                // 2. Dibujar ejes azules
                glColor3f(0.6f, 0.6f, 1.0f);
                glBegin(GL_LINES);
                    glVertex2i(0, 200);
                    glVertex2i(400, 200); // Eje X
                    glVertex2i(200, 0);
                    glVertex2i(200, 400); // Eje Y
                glEnd();

                // 3. Dibujar las tres líneas (una con cada algoritmo)

                // Línea básica (roja) - 1er cuadrante
                glColor3f(1.0f, 0.0f, 0.0f);
                algoritmoBasico(200, 200, 300, 300);

                // Línea DDA (verde) - 2do cuadrante
                glColor3f(0.0f, 1.0f, 0.0f);
                dda(200, 200, 100, 300);

                // Línea Bresenham (azul) - 4to cuadrante
                glColor3f(0.0f, 0.0f, 1.0f);
                bresenham(200, 200, 300, 100);

                break;

        }

            default:
                cout << "USA EL CLICK DERECHO PARA ABRIR EL MENU" << endl;
                break;
        }

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(400, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Taller 2.1 - Grupo 3");
    inicio();
    glutDisplayFunc(pantalla);
    glutCreateMenu(menu);
    glutAddMenuEntry("Caso 1: Básico - Primer Cuadrante", 1);
    glutAddMenuEntry("Caso 2: Básico - Cuatro Cuadrantes", 2);
    glutAddMenuEntry("Caso 3: DDA - Primer Cuadrante", 3);
    glutAddMenuEntry("Caso 4: DDA - Cuatro Cuadrantes", 4);
    glutAddMenuEntry("Caso 5: Bresenham - Primer Cuadrante", 5);
    glutAddMenuEntry("Caso 6: Bresenham - Cuatro Cuadrantes con Puntos Medios", 6);
    glutAddMenuEntry("Caso 7: Comparativa - Básico, DDA y Bresenham", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return EXIT_SUCCESS;
}
