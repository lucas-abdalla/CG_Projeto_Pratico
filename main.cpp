#include <GL/glut.h>
#include <iostream>

// Funções de callback
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void drawArm();
void drawCube();
void setupLighting();

int main(int argc, char** argv) {
    // Inicializa o FreeGLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Modelo 3D Articulado");

    // Configurações de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Configurações de OpenGL
    glEnable(GL_DEPTH_TEST);

    // Loop principal do FreeGLUT
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Configurações da câmera
    gluLookAt(0.0, 0.0, 5.0,  // Posição da câmera
              0.0, 0.0, 0.0,  // Ponto para onde a câmera está olhando
              0.0, 1.0, 0.0); // Vetor "up"

    // Desenha o modelo 3D articulado
    drawArm();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    /*if (key == 27) // Tecla ESC
        glutLeaveMainLoop();*/
}

void drawArm() {
    // Desenha a base do braço
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glScalef(0.2f, 0.5f, 0.2f);
    drawCube();
    glPopMatrix();

    // Desenha a parte superior do braço
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Rotação da articulação
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(0.2f, 0.5f, 0.2f);
    drawCube();
    glPopMatrix();
}

void drawCube() {
    glBegin(GL_QUADS);
    // Define os vértices do cubo
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // Repita para as outras faces do cubo
    glEnd();
}

// Configuração da iluminação
void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
