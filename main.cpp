#include <GL/glut.h>
#include <math.h>

float angle1 = 90.0, angle2 = -45.0, angle3 = -60.0;
float lightIntensity = 1.0;
float cameraX = 0.0, cameraY = 0.0, cameraZ = 5.0;
float cameraAngleX = 0.0, cameraAngleY = 0.0;

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
    glTranslatef(0.0, -0.50, 0.0); // Position the plank under the base
    glBegin(GL_QUADS);
        // Top face
        glVertex3f(-5.0, 0.25, -5.0);
        glVertex3f(5.0, 0.25, -5.0);
        glVertex3f(5.0, 0.25, 5.0);
        glVertex3f(-5.0, 0.25, 5.0);
        // Bottom face
        glVertex3f(-5.0, -0.25, -5.0);
        glVertex3f(5.0, -0.25, -5.0);
        glVertex3f(5.0, -0.25, 5.0);
        glVertex3f(-5.0, -0.25, 5.0);
        // Front face
        glVertex3f(-5.0, -0.25, 5.0);
        glVertex3f(5.0, -0.25, 5.0);
        glVertex3f(5.0, 0.25, 5.0);
        glVertex3f(-5.0, 0.25, 5.0);
        // Back face
        glVertex3f(-5.0, -0.25, -5.0);
        glVertex3f(5.0, -0.25, -5.0);
        glVertex3f(5.0, 0.25, -5.0);
        glVertex3f(-5.0, 0.25, -5.0);
        // Left face
        glVertex3f(-5.0, -0.25, -5.0);
        glVertex3f(-5.0, -0.25, 5.0);
        glVertex3f(-5.0, 0.25, 5.0);
        glVertex3f(-5.0, 0.25, -5.0);
        // Right face
        glVertex3f(5.0, -0.25, -5.0);
        glVertex3f(5.0, -0.25, 5.0);
        glVertex3f(5.0, 0.25, 5.0);
        glVertex3f(5.0, 0.25, -5.0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
    glPopMatrix();
}

void setupLighting() {
    GLfloat light_diffuse[] = { lightIntensity, lightIntensity, lightIntensity, 1.0 };
    GLfloat light_specular[] = { lightIntensity, lightIntensity, lightIntensity, 1.0 };

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

    gluLookAt(cameraX, cameraY, cameraZ, cameraX + sin(cameraAngleY), cameraY + sin(cameraAngleX), cameraZ - cos(cameraAngleY), 0.0, 1.0, 0.0);

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

void reset() {
    angle1 = 90.0;
    angle2 = -45.0;
    angle3 = -60.0;
    lightIntensity = 1.0;
    cameraX = 0.0;
    cameraY = 0.0;
    cameraZ = 5.0;
    cameraAngleX = 0.0;
    cameraAngleY = 0.0;
    setupLighting();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': angle1 += 5.0; break;
        case 'a': angle1 -= 5.0; break;
        case 'w': angle2 += 5.0; break;
        case 's': angle2 -= 5.0; break;
        case 'e': angle3 += 5.0; break;
        case 'd': angle3 -= 5.0; break;
        case '+': cameraY += 0.1; break;
        case '-': cameraY -= 0.1; break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_PAGE_UP: cameraAngleX -= 0.05; break;
        case GLUT_KEY_PAGE_DOWN: cameraAngleX += 0.05; break;
        case GLUT_KEY_UP:
            cameraX += sin(cameraAngleY) * 0.1;
            cameraZ -= cos(cameraAngleY) * 0.1;
            break;
        case GLUT_KEY_DOWN:
            cameraX -= sin(cameraAngleY) * 0.1;
            cameraZ += cos(cameraAngleY) * 0.1;
            break;
        case GLUT_KEY_LEFT: cameraAngleY -= 0.05; break;
        case GLUT_KEY_RIGHT: cameraAngleY += 0.05; break;
    }
    glutPostRedisplay();
}

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        lightIntensity += 0.1;
    } else {
        lightIntensity -= 0.1;
    }
    if (lightIntensity < 0.0) lightIntensity = 0.0;
    if (lightIntensity > 1.0) lightIntensity = 1.0;
    setupLighting();
    glutPostRedisplay();
}

void menu(int option) {
    if (option == 0) {
        reset();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mechanical Arm");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseWheel);

    glutCreateMenu(menu);
    glutAddMenuEntry("Reset", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
