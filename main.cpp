#include <GL/glut.h>
#include <math.h>

float angle1 = 0.0, angle2 = 0.0, angle3 = 0.0;

void drawSegment() {
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2); // Set color to dark gray
    glScalef(1.0, 0.2, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawSphere(float size, float r, float g, float b) {
    glColor3f(r, g, b); // Set color
    glutSolidSphere(size, 20, 20);
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
}

void drawBase() {
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2); // Set color to dark gray
    glTranslatef(0.0, -0.25, 0.0); // Adjust position to be closer to the first segment
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.25, 0.5, 20, 20); // Make the cone smaller
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
    glPopMatrix();
}

void drawTable() {
    glPushMatrix();
    glColor3f(0.6, 0.3, 0.0); // Set color to brown
    glTranslatef(0.0, -0.75, 0.0); // Position the table under the base
    glScalef(10.0, 0.5, 10.0); // Scale the cube to make it look like a table
    glutSolidCube(1.0);
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
    glPopMatrix();
}

void setupLighting() {
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void updateLightPosition() {
    GLfloat light_position[] = { 1.5 + 0.5 * cos(angle1 * M_PI / 180.0), 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(-1.5, 0.0, 0.0);

    drawTable(); // Draw the table
    drawBase(); // Draw the base

    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0); // Move the sphere to the top of the cone
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere between the cone and the first segment
    glRotatef(angle1, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle2, 0.0, 0.0, 1.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle3, 0.0, 0.0, 1.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    drawSphere(0.2, 1.0, 1.0, 1.0); // Make the last sphere white and bigger
    GLfloat light_position[] = { 1.5 + 0.5 * cos(angle1 * M_PI / 180.0), 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Update the light position to move with the sphere
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0); // Set clear color to gray
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    setupLighting();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': angle1 += 5.0; break;
        case 'a': angle1 -= 5.0; break;
        case 'w': angle2 += 5.0; break;
        case 's': angle2 -= 5.0; break;
        case 'e': angle3 += 5.0; break;
        case 'd': angle3 -= 5.0; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mechanical Arm");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
