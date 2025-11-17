#include <GL/glut.h>
#include <iostream>
#include <string> // Required for general string handling, and sometimes helps with glutBitmapString dependencies

// Global variable to keep track of the currently selected exercise
int currentExercise = 0; // 0 for no exercise selected, 1 for Exercise 1, 2 for Exercise 2, 3 for Exercise 3

// Global angle for rotation, shared across all exercises
float angle = 0.0;

// --- Function Declarations for Each Exercise ---

// Exercise 1: Colored 3D Cube (JC)
void display1();
void init1();

// Exercise 2: Wireframe Cube
void display2();
void init2();

// Exercise 3: Rotating Sphere (RAYMONDES PEÑA JESÚS)
void display3();
void init3();

// --- Common OpenGL Functions ---

// Common reshape function for all exercises
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 50.0); // Sets up a perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Common timer function for all exercises to handle animation
void timer(int value) {
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(1000 / 60, timer, 0); // Call this function again for smooth animation (approx. 60 FPS)

    angle += 0.8; // Increment the rotation angle
    if (angle > 360.0) {
        angle -= 360.0; // Keep angle within 0-360 degrees
    }
}

// Main display function that acts as a dispatcher for the selected exercise
void mainDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset the model-view matrix

    switch (currentExercise) {
        case 1:
            display1(); // Call display function for Exercise 1
            break;
        case 2:
            display2(); // Call display function for Exercise 2
            break;
        case 3:
            display3(); // Call display function for Exercise 3
            break;
        default:
            // Display a message if no exercise is selected yet
            glColor3f(1.0, 1.0, 1.0); // White color for text
            glRasterPos2f(-4.0, 0.0); // Set raster position for text drawing
            const unsigned char* message = reinterpret_cast<const unsigned char*>("Selecciona un ejercicio del menu (click derecho)");
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, message); // Draw bitmap string
            break;
    }

    glFlush(); // Ensure all commands are executed
    glutSwapBuffers(); // Swap buffers for double buffering
}

// --- Menu Handling ---

// Callback function for menu selections
void menu(int option) {
    currentExercise = option; // Set the selected exercise

    // Reinitialize OpenGL state based on the selected exercise
    switch (currentExercise) {
        case 1:
            init1();
            break;
        case 2:
            init2();
            break;
        case 3:
            init3();
            break;
        default:
            // Default initialization if no specific exercise is chosen (e.g., initial state)
            glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
            glDisable(GL_DEPTH_TEST); // Depth test might not be needed for just text
            break;
    }
    glutPostRedisplay(); // Request a redraw to show the newly selected exercise
}

// --- Main Program Entry Point ---

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GL_DOUBLE | GLUT_RGB | GL_DEPTH); // Set display mode

    glutInitWindowPosition(150, 150); // Set window position
    glutInitWindowSize(800, 600);     // Set window size
    glutCreateWindow("Menu de Ejercicios OpenGL"); // Create the window

    glutDisplayFunc(mainDisplay); // Register the main display callback
    glutReshapeFunc(reshape);     // Register the reshape callback
    glutTimerFunc(0, timer, 0);   // Start the timer for animation

    // Create the pop-up menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Ejercicio 1: Cubo 3D con Colores", 1);
    glutAddMenuEntry("Ejercicio 2: Cubo con solo aristas azules", 2);
    glutAddMenuEntry("Ejercicio 3: Esfera Rotativa", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach the menu to the right mouse button

    // Initial setup for the window
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set initial background color to black
    glEnable(GL_DEPTH_TEST);          // Enable depth testing for 3D objects

    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}

// --- Implementations of Exercise-Specific Functions ---

// Exercise 1: Colored 3D Cube (JC)
void init1() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void display1() {
    glTranslatef(0, 0, -25.0); // Move scene back
    glRotatef(angle, 1.0, 1.0, 1.0); // Rotate the cube

    glBegin(GL_QUADS); // Begin drawing quads (faces of the cube)
        // Front face (red and blue alternating colors)
        glColor3f(0.0, 0.0, 1.0); glVertex3f(-5, -5,  5);
        glColor3f(1.0, 0.0, 0.0); glVertex3f( 5, -5,  5);
        glColor3f(0.0, 0.0, 1.0); glVertex3f( 5,  5,  5);
        glColor3f(1.0, 0.0, 0.0); glVertex3f(-5,  5,  5);

        // Back face (blue)
        glColor3f(0.0, 0.0, 1.0); // Setting color for this face
        glVertex3f(-5, -5, -5);
        glVertex3f(-5,  5, -5);
        glVertex3f( 5,  5, -5);
        glVertex3f( 5, -5, -5);

        // Right face (blue)
        glVertex3f( 5, -5, -5);
        glVertex3f( 5,  5, -5);
        glVertex3f( 5,  5,  5);
        glVertex3f( 5, -5,  5);

        // Left face (blue)
        glVertex3f(-5, -5, -5);
        glVertex3f(-5, -5,  5);
        glVertex3f(-5,  5,  5);
        glVertex3f(-5,  5, -5);

        // Top face (blue)
        glVertex3f(-5,  5, -5);
        glVertex3f(-5,  5,  5);
        glVertex3f( 5,  5,  5);
        glVertex3f( 5,  5, -5);

        // Bottom face (blue)
        glVertex3f(-5, -5, -5);
        glVertex3f( 5, -5, -5);
        glVertex3f( 5, -5,  5);
        glVertex3f(-5, -5,  5);
    glEnd(); // End drawing quads
}

// Exercise 2: Wireframe Cube
void init2() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void display2() {
    glTranslatef(0, 0, -25.0); // Move scene back
    glRotatef(angle, 1.0, 1.0, 1.0); // Rotate the cube
    glColor3f(0.0, 0.0, 1.0); // Blue color for the wireframe
    glutWireCube(10.0); // Draw a wireframe cube
}

// Exercise 3: Rotating Sphere (RAYMONDES PEÑA JESÚS)
void init3() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void display3() {
    glTranslatef(0, 0, -25.0); // Move scene back
    glRotatef(angle, 1.0, 1.0, 1.0); // Rotate the sphere
    glColor3f(0.0, 0.0, 1.0); // Blue color for the sphere
    glutWireSphere(10.0, 30, 30); // Draw a wireframe sphere
}
