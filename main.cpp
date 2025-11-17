#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

// --- Global Variables ---

// Global for Exercise 1 (Circles)
int circleRadius;

// Global for Exercise 2 (Midpoint Circle with grid and axes, 0-400 coords)
float ex2_grosor;
float ex2_r, ex2_g, ex2_b;
int ex2_radio;

// Global for Exercise 3 (Midpoint Circle arbitrary center with grid and axes, -200 to 200 coords)
GLfloat ex3_r_color, ex3_g_color, ex3_b_color; // Renamed to avoid clash with r,g,b in Ex2
GLint ex3_xc, ex3_yc, ex3_rad, ex3_t_size;

// Global for Exercise 4 (Midpoint Ellipse from snippet 4)
GLint ex4_a_major; // Semieje mayor 'a'
GLint ex4_b_minor; // Semieje menor 'b'
GLfloat ex4_grosor;
GLfloat ex4_r_col, ex4_g_col, ex4_b_col;

// Global for Exercise 5 (Midpoint Ellipse)
float ex5_rx, ex5_ry, ex5_xc, ex5_yc;
float ex5_escala = 1.5f; // Internal scale for Ex5

// Global for Exercise 6 (Triangle with circles)
GLfloat ex6_l; // Side length of triangle

// Global to control which exercise is active
// 0: Menu, 1: Exercise 1 (Circles), 2: Exercise 2 (Midpoint Circle with grid),
// 3: Exercise 3 (Midpoint Circle arbitrary center), 4: Exercise 4 (Midpoint Ellipse),
// 5: Exercise 5 (Midpoint Ellipse General), 6: Exercise 6 (Triangle with circles)
int currentExercise = 0;


// --- Helper Functions ---

// Function to draw a point (used by multiple exercises)
void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to display text on the console
void displayText(const std::string& text) {
    std::cout << text << std::endl;
}

// Function to draw text on the OpenGL window
void drawTextOnWindow(std::string text, int x, int y, void* font) {
    glRasterPos2i(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}

// Basic Bresenham line drawing function (placeholder for Exercise 6)
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    glBegin(GL_POINTS);
    while (true) {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
    glEnd();
}


// --- Exercise 1: Three Circles (Parametric, Explicit, Midpoint at 0,0) ---

// Parametric Circle Drawing Function (draws full circle using 8-way symmetry from 0 to PI/4)
void drawCircleParametric() {
    glColor3f(1.0, 0.0, 0.0); // Red color for this circle

    float x, y;
    float PI = 3.14159265358979323846;
    float theta = 0.0;
    float delta = PI / (4.0 * circleRadius);

    while (theta <= PI / 4.0 + delta) {
        x = circleRadius * cos(theta);
        y = circleRadius * sin(theta);

        plot(round(x), round(y)); plot(round(-x), round(y));
        plot(round(x), round(-y)); plot(round(-x), round(-y));
        plot(round(y), round(x)); plot(round(-y), round(x));
        plot(round(y), round(-x)); plot(round(-y), round(-x));

        theta += delta;
    }
}

// Explicit Circle Drawing Function (draws full circle using 8-way symmetry from x=0 to x=y)
void drawCircleExplicit() {
    glColor3f(0.0, 1.0, 0.0); // Green color for this circle

    for (int x = 0; x <= round(circleRadius / sqrt(2.0)); ++x) {
        float y_val = sqrt(pow(circleRadius, 2) - pow(x, 2));

        plot(round(x), round(y_val)); plot(round(-x), round(y_val));
        plot(round(x), round(-y_val)); plot(round(-x), round(-y_val));
        plot(round(y_val), round(x)); plot(round(-y_val), round(x));
        plot(round(y_val), round(-x)); plot(round(-y_val), round(-x));
    }
}

// Midpoint Circle Drawing Function (centered at 0,0, draws full circle using 8-way symmetry)
void drawCircleMidpointEx1() { // Renamed to avoid clash with Ex3's puntoMedio
    glColor3f(0.0, 0.0, 1.0); // Blue color for this circle

    int x = 0;
    int y = circleRadius;
    int d = 1 - circleRadius;

    plot(x, y); plot(-x, y); plot(x, -y); plot(-x, -y);
    plot(y, x); plot(-y, x); plot(y, -x); plot(-y, -x);

    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;

        plot(x, y); plot(-x, y); plot(x, -y); plot(-x, -y);
        plot(y, x); plot(-y, x); plot(y, -x); plot(-y, -x);
    }
}

// Display function for Exercise 1
void displayExercise1() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear buffer for each new drawing

    // Draw Parametric Circle (top-left quadrant)
    glPushMatrix();
    glTranslatef(-100.0, 100.0, 0.0); // Translate to top-left
    drawCircleParametric();
    glPopMatrix();

    // Draw Explicit Circle (top-right quadrant)
    glPushMatrix();
    glTranslatef(100.0, 100.0, 0.0); // Translate to top-right
    drawCircleExplicit();
    glPopMatrix();

    // Draw Midpoint Circle (bottom-center quadrant)
    glPushMatrix();
    glTranslatef(0.0, -100.0, 0.0); // Translate to bottom-center
    drawCircleMidpointEx1();
    glPopMatrix();

    glFlush();
}

// --- Exercise 2: Midpoint Circle with custom point size/color and grid (0-400 coords) ---

// This function needs to set its own projection to match the 0-400 coordinate system
void displayExercise2() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up 0-400 coordinate system for this exercise
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);

    // Draw Grid
    glColor3f(0.7, 1.0, 0.7); // Light green for grid
    glBegin(GL_LINES);
    for (int i = 0; i <= 400; i += 10) {
        glVertex2i(i, 0); glVertex2i(i, 400);
        glVertex2i(0, i); glVertex2i(400, i);
    }
    glEnd();

    // Draw Axes (X and Y centered at 200,200)
    glColor3f(0.6, 0.6, 1.0); // Light blue for axes
    glBegin(GL_LINES);
    glVertex2i(0, 200); glVertex2i(400, 200); // X axis
    glVertex2i(200, 0); glVertex2i(200, 400); // Y axis
    glEnd();

    int x = 0;
    int y = ex2_radio;
    int d = 1 - ex2_radio;

    glPointSize(ex2_grosor);
    glColor3f(ex2_r, ex2_g, ex2_b);
    glBegin(GL_POINTS);
    while (x <= y) {
        // Points are translated by +200 and scaled by *10 for the 0-400 grid
        glVertex2i( x * 10 + 200,  y * 10 + 200);
        glVertex2i( y * 10 + 200,  x * 10 + 200);
        glVertex2i(-x * 10 + 200,  y * 10 + 200);
        glVertex2i(-y * 10 + 200,  x * 10 + 200);
        glVertex2i(-x * 10 + 200, -y * 10 + 200);
        glVertex2i(-y * 10 + 200, -x * 10 + 200);
        glVertex2i( x * 10 + 200, -y * 10 + 200);
        glVertex2i( y * 10 + 200, -x * 10 + 200);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glEnd();

    glFlush();
}


// --- Exercise 3: Midpoint Circle with Arbitrary Center, grid, axes (-200 to 200 coords) ---

// Helper for Exercise 3's puntoMedio (called within glBegin(GL_POINTS)/glEnd())
void puntosCircunferenciaEx3(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

// Midpoint Circle Drawing Function for arbitrary center (from user's Ex3 snippet)
void puntoMedioEx3(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 1 - r; // Decision parameter for Midpoint

    glBegin(GL_POINTS);
    puntosCircunferenciaEx3(xc, yc, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        puntosCircunferenciaEx3(xc, yc, x, y);
    }
    glEnd();
}

// Display function for Exercise 3
void displayExercise3() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up -200 to 200 coordinate system for this exercise
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);


    // Cuadrícula (Grid)
    glColor3f(0.0, 1.0, 0.0); // Green grid
    for(int x = -200; x <= 200; x+=5){
        glBegin(GL_LINES);
            glVertex2f(x,-200);
            glVertex2f(x,200);
        glEnd();
    }
    for(int y = -200; y <= 200; y+=5){
        glBegin(GL_LINES);
            glVertex2f(-200,y);
            glVertex2f(200,y);
        glEnd();
    }

    // Ejes (Axes)
    glColor3f(0.0, 0.0, 1.0); // Blue axes
    glBegin(GL_LINES);
        glVertex2f(0,-200);
        glVertex2f(0,200);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(200,0);
        glVertex2f(-200,0);
    glEnd();

    // Dibujar circunferencia
    glColor3f(ex3_r_color, ex3_g_color, ex3_b_color);
    glPointSize(ex3_t_size);
    puntoMedioEx3(ex3_xc, ex3_yc, ex3_rad);

    glFlush();
}


// --- Exercise 4: Midpoint Ellipse using Symmetry (from user's Ex4 snippet, but named Ex4) ---
void displayExercise4() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up 0-400 coordinate system for this exercise, similar to Ex2 in the snippet
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);

    // Draw Grid
    glColor3f(0.7, 1.0, 0.7);
    glBegin(GL_LINES);
    for (int i = 0; i <= 400; i += 10) {
        glVertex2i(i, 0); glVertex2i(i, 400);
        glVertex2i(0, i); glVertex2i(400, i);
    }
    glEnd();

    // Draw Axes
    glColor3f(0.6, 0.6, 1.0);
    glBegin(GL_LINES);
    glVertex2i(0, 200); glVertex2i(400, 200);
    glVertex2i(200, 0); glVertex2i(200, 400);
    glEnd();

    glPointSize(ex4_grosor);
    glColor3f(ex4_r_col, ex4_g_col, ex4_b_col);

    int x = 0;
    int y = ex4_b_minor;
    int a2 = ex4_a_major * ex4_a_major;
    int b2 = ex4_b_minor * ex4_b_minor;
    float d1 = b2 - a2 * ex4_b_minor + 0.25f * a2;

    glBegin(GL_POINTS);

    while ((2 * b2 * x) <= (2 * a2 * y)) {
        // PRIMERA SIMETRIA
        glVertex2i( x * 10 + 200,  y * 10 + 200); // I
        glVertex2i(-x * 10 + 200,  y * 10 + 200); // II
        glVertex2i(-x * 10 + 200, -y * 10 + 200); // III
        glVertex2i( x * 10 + 200, -y * 10 + 200); // IV

        if (d1 < 0) {
            d1 += b2 * (2 * x + 3);
        } else {
            d1 += b2 * (2 * x + 3) + a2 * (-2 * y + 2);
            y--;
        }
        x++;
    }

    float d2 = b2 * (x + 0.5f) * (x + 0.5f) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y >= 0) {
        // AQUI HACEMOS 2DA LA SIMETRÍA
        glVertex2i( x * 10 + 200,  y * 10 + 200); // I
        glVertex2i(-x * 10 + 200,  y * 10 + 200); // II
        glVertex2i(-x * 10 + 200, -y * 10 + 200); // III
        glVertex2i( x * 10 + 200, -y * 10 + 200); // IV

        if (d2 > 0) {
            d2 += a2 * (-2 * y + 3);
        } else {
            d2 += b2 * (2 * x + 2) + a2 * (-2 * y + 3);
            x++;
        }
        y--;
    }
    glEnd();
    glFlush();
}


// --- Exercise 5: Midpoint Ellipse General (from user's Ex5 snippet) ---

// Helper for Exercise 5's dibujarElipse (called within glBegin(GL_POINTS)/glEnd())
void plotPointsEx5(float x, float y) {
    glVertex2f(ex5_xc + x * ex5_escala, ex5_yc + y * ex5_escala);
    glVertex2f(ex5_xc - x * ex5_escala, ex5_yc + y * ex5_escala);
    glVertex2f(ex5_xc + x * ex5_escala, ex5_yc - y * ex5_escala);
    glVertex2f(ex5_xc - x * ex5_escala, ex5_yc - y * ex5_escala);
}

void dibujarElipseEx5() {
    float x = 0;
    float y = ex5_ry;

    float rx2 = ex5_rx * ex5_rx;
    float ry2 = ex5_ry * ex5_ry;

    float dx = 2 * ry2 * x;
    float dy = 2 * rx2 * y;

    float p1 = ry2 - rx2 * ex5_ry + 0.25 * rx2;

    glBegin(GL_POINTS);

    // Región 1
    while (dx < dy) {
        plotPointsEx5(x, y);
        x++;
        dx = 2 * ry2 * x;
        if (p1 < 0) {
            p1 += dx + ry2;
        } else {
            y--;
            dy = 2 * rx2 * y;
            p1 += dx - dy + ry2;
        }
    }

    // Región 2
    float p2 = ry2 * (x + 0.5f) * (x + 0.5f) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        plotPointsEx5(x, y);
        y--;
        dy = 2 * rx2 * y;
        if (p2 > 0) {
            p2 += rx2 - dy;
        } else {
            x++;
            dx = 2 * ry2 * x;
            p2 += dx - dy + rx2;
        }
    }
    glEnd();
}

// Display function for Exercise 5
void displayExercise5() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Set up 0-400 coordinate system specific to this exercise (from snippet)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.1f, 0.3f, 0.9f); // Default color from snippet
    glPointSize(2.0f); // Default point size from snippet
    dibujarElipseEx5();
    glFlush();
}


// --- Exercise 6: Triangle with Circles (from user's Ex6 snippet) ---

void displayExercise6() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Use the default -200 to 200 coordinate system for this exercise
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);

    GLfloat bigR = (ex6_l * sqrt(3.0)) / 3.0;

    glColor3f(0.0,0.0,1.0); // Blue for big circle
    glPointSize(3.0);
    puntoMedioEx3(0,0,bigR); // Using puntoMedioEx3 for circles

    GLfloat th = bigR * 3.0 / 2.0;

    glColor3f(1.0,0.0,0.0); // Red for triangle
    glPointSize(3.0);
    drawLineBresenham(0, round(bigR), round(0-(ex6_l/2.0)), round(bigR-th));
    drawLineBresenham(round(0-(ex6_l/2.0)), round(bigR-th), round(0+(ex6_l/2.0)), round(bigR-th));
    drawLineBresenham(round(0+(ex6_l/2.0)), round(bigR-th), 0, round(bigR));

    GLfloat smallR = ex6_l/(2.0*(1.0+sqrt(3.0)));

    glColor3f(0.0,0.0,1.0); // Blue for small circles
    glPointSize(3.0);
    puntoMedioEx3(round(0-(ex6_l/5.45)),round(bigR-th+smallR),smallR);
    puntoMedioEx3(round(0+(ex6_l/5.45)),round(bigR-th+smallR),smallR);
    puntoMedioEx3(0,round(bigR-th+2.75*smallR),smallR);

    glFlush();
}


// --- Main Menu and GLUT Callbacks ---

// Function to draw the main menu on the OpenGL window
void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Restore default projection for menu
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200); // Consistent with init
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0, 0.0, 0.0); // Black text color

    drawTextOnWindow("MENU DE EJERCICIOS", -100, 150, GLUT_BITMAP_HELVETICA_18);
    drawTextOnWindow("1. Ejercicio 1: Circunferencias (Parametrica, Explicita, Punto Medio)", -150, 100, GLUT_BITMAP_HELVETICA_12);
    drawTextOnWindow("2. Ejercicio 2: Circunferencia Pto. Medio (Grosor/Color/Cuadricula)", -150, 70, GLUT_BITMAP_HELVETICA_12);
    drawTextOnWindow("3. Ejercicio 3: Circunferencia Pto. Medio (Centro Arbitrario/Cuadricula)", -150, 40, GLUT_BITMAP_HELVETICA_12);
    drawTextOnWindow("4. Ejercicio 4: Elipse Pto. Medio (Ejes/Cuadricula)", -150, 10, GLUT_BITMAP_HELVETICA_12); // Assuming this is Ex4 based on the code
    drawTextOnWindow("5. Ejercicio 5: Elipse General (Bresenham's Midpoint Ellipse)", -150, -20, GLUT_BITMAP_HELVETICA_12);
    drawTextOnWindow("6. Ejercicio 6: Circunferencia y Triangulo", -150, -50, GLUT_BITMAP_HELVETICA_12);

    drawTextOnWindow("Presione ESC para Salir.", -150, -110, GLUT_BITMAP_HELVETICA_12);
    drawTextOnWindow("Presione 'M' para volver al menu (desde un ejercicio).", -150, -140, GLUT_BITMAP_HELVETICA_10);

    glFlush();
}

// Main display callback function
void display() {
    if (currentExercise == 0) {
        drawMenu();
    } else if (currentExercise == 1) {
        displayExercise1();
    } else if (currentExercise == 2) {
        displayExercise2();
    } else if (currentExercise == 3) {
        displayExercise3();
    } else if (currentExercise == 4) { // This corresponds to the user's "EJERCICIO 4" snippet
        displayExercise4();
    } else if (currentExercise == 5) { // This corresponds to the user's "EJERCICIO 5" snippet
        displayExercise5();
    } else if (currentExercise == 6) { // This corresponds to the user's "EJERCICIO 6" snippet
        displayExercise6();
    }
}

// Keyboard function to handle menu navigation and exit
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key (always exits)
        exit(0);
    }

    if (currentExercise == 0) { // If currently in menu
        switch (key) {
            case '1':
                currentExercise = 1;
                // --- Ask for Exercise 1 radius when selected ---
                std::cout << "\n--- Iniciando Ejercicio 1: Circunferencias ---\n";
                std::cout << "Por favor, ingrese el radio de la circunferencia para el Ejercicio 1 (ej. 50, 80, 100): ";
                std::cin >> circleRadius;
                std::cout << "***** CIRCUNFERENCIA EN REPRESENTACION PARAMETRICA CON CENTRO CERO *****\n";
                std::cout << "Radio = " << circleRadius << std::endl;
                std::cout << "***** CIRCUNFERENCIA EN REPRESENTACION EXPLICITA CON CENTRO CERO *******\n";
                std::cout << "Radio = " << circleRadius << std::endl;
                std::cout << "***** CIRCUNFERENCIA DEL PUNTO MEDIO CON CENTRO CERO *****\n";
                std::cout << "Radio = " << circleRadius << std::endl;
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
            case '2': // Exercise 2
                currentExercise = 2;
                std::cout << "\n--- Iniciando Ejercicio 2: Circunferencia Pto. Medio (Grosor/Color/Cuadricula) ---\n";
                std::cout << "Ingrese el grosor del punto (ej. 2.0): "; std::cin >> ex2_grosor;
                std::cout << "Ingrese el color (valores entre 0 y 1):\n";
                std::cout << "Rojo (R): "; std::cin >> ex2_r;
                std::cout << "Verde (G): "; std::cin >> ex2_g;
                std::cout << "Azul (B): "; std::cin >> ex2_b;
                std::cout << "Ingrese el radio: "; std::cin >> ex2_radio;
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
            case '3': // Exercise 3
                currentExercise = 3;
                std::cout << "\n--- Iniciando Ejercicio 3: Circunferencia Pto. Medio (Centro Arbitrario/Cuadricula) ---\n";
                std::cout << "**** CIRCUNFERENCIA CON CENTRO (X0,Y0) POR PUNTO MEDIO ****\n\n";
                std::cout << "Ingrese el x central: "; std::cin >> ex3_xc;
                std::cout << "Ingrese el y central: "; std::cin >> ex3_yc;
                std::cout << "Ingrese el radio: "; std::cin >> ex3_rad;
                std::cout << "Ingrese el tamano de cada punto: "; std::cin >> ex3_t_size;
                std::cout << "Ingrese la intensidad de ROJO (0 - 1): "; std::cin >> ex3_r_color;
                std::cout << "Ingrese la intensidad de VERDE (0 - 1): "; std::cin >> ex3_g_color;
                std::cout << "Ingrese la intensidad de AZUL (0 - 1): "; std::cin >> ex3_b_color;
                std::cout << "\nHAGA CLIC EN LA FIGURA PARA CREAR UNA NUEVA (funcionalidad no implementada en este menu)\n"; // Acknowledge this
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
            case '4': // Exercise 4 (User's snippet named EJERCICIO 4 for ellipse)
                currentExercise = 4;
                std::cout << "\n--- Iniciando Ejercicio 4: Elipse Pto. Medio (Ejes/Cuadricula) ---\n";
                std::cout << "\nELIPSE POR METODO DEL PUNTO MEDIO USANDO SIMETRIA\n";
                std::cout << "Ingrese el semieje mayor (a): "; std::cin >> ex4_a_major; // Assuming new globals for Ex4
                std::cout << "Ingrese el semieje menor (b): "; std::cin >> ex4_b_minor;
                std::cout << "Ingrese el grosor del punto (ej. 2.0): "; std::cin >> ex4_grosor;
                std::cout << "Ingrese el color (valores entre 0 y 1):\n";
                std::cout << "Rojo (R): "; std::cin >> ex4_r_col;
                std::cout << "Verde (G): "; std::cin >> ex4_g_col;
                std::cout << "Azul (B): "; std::cin >> ex4_b_col;
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
            case '5': // Exercise 5 (User's snippet named EJERCICIO 5 for ellipse)
                currentExercise = 5;
                std::cout << "\n--- Iniciando Ejercicio 5: Elipse General (Bresenham's Midpoint Ellipse) ---\n";
                std::cout << "Centro de la elipse (por ejemplo 100 100): "; std::cin >> ex5_xc >> ex5_yc;
                std::cout << "Radio (rx ry por ejemplo 40 60): "; std::cin >> ex5_rx >> ex5_ry;
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
            case '6': // Exercise 6
                currentExercise = 6;
                std::cout << "\n--- Iniciando Ejercicio 6: Circunferencia y Triangulo ---\n";
                std::cout << "Ingrese el largo de los lados del triangulo: "; std::cin >> ex6_l;
                std::cout << "Presione 'M' para volver al menu.\n";
                glutPostRedisplay();
                break;
        }
    } else { // If currently in an exercise
        if (key == 'm' || key == 'M') { // 'M' to return to menu
            currentExercise = 0;
            std::cout << "\n--- Volviendo al Menu ---\n";
            glutPostRedisplay();
        }
    }
}

// Initialization function (sets up a common coordinate system for the menu)
void init() {
    glClearColor(0.9, 0.9, 0.9, 1.0); // Light gray background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200); // Standard range for menu and some exercises
    glMatrixMode(GL_MODELVIEW);
    glPointSize(4.0); // Default point size for Ex1
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutCreateWindow("Taller de Computacion Visual - Menu Principal");

    init();

    // Initial message before showing the menu
    std::cout << "--- Bienvenida ---\n";
    std::cout << "El programa ha iniciado. Presione un numero para seleccionar un ejercicio.\n";
    std::cout << "Presione ESC para salir en cualquier momento.\n";
    std::cout << "Presione 'M' para volver al menu desde un ejercicio.\n";


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
