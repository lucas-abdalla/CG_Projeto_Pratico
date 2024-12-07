#include <GL/glut.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint idTextura;
float angle1 = 90.0, angle2 = 315.0, angle3 = 315.0;
float angle4 = 0.0, angle5 = 0.0, angle6 = 0.0;
float angle7 = 0.0, angle8 = 0.0, angle9 = 0.0;
float lightColor[3] = {1.0, 1.0, 1.0};
float cameraX = 0.0, cameraY = 0.0, cameraZ = 5.0;
float cameraAngleX = 0.0, cameraAngleY = 0.0;

void carregarTextura(const char* nomeArquivo)
{
    int largura, altura, canais;

    unsigned char *dados = stbi_load(nomeArquivo, &largura, &altura, &canais, 0);

    if (!dados)
    exit(1);

    // gerar textura
    glGenTextures(1, &idTextura);
    glBindTexture(GL_TEXTURE_2D, idTextura);

    // configurar parametros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, (canais == 4) ? GL_RGBA : GL_RGB, 
                largura, altura, 0, (canais == 4) ? GL_RGBA : GL_RGB,
                GL_UNSIGNED_BYTE, dados);

    // liberar a memoria da imagem
    stbi_image_free(dados);              
}

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
    glTranslatef(0.0, -0.50, 0.0); // Position the plank under the base

    glBindTexture(GL_TEXTURE_2D, idTextura);
    glBegin(GL_QUADS);
        // Top face
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, 0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        // Bottom face
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -0.25, 5.0);
        // Front face
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        // Back face
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, -5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, -5.0);
        // Left face
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, -5.0);
        // Right face
        glTexCoord2f(0.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(5.0, 0.25, -5.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
    glPopMatrix();
}

void drawLamp() {
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0); // Move the sphere to the top of the cone
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere between the cone and the first segment

    glRotatef(angle1, 0.0, 0.0, 1.0);
    glRotatef(angle4, 0.0, 1.0, 0.0);
    glRotatef(angle7, 1.0, 0.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle2, 0.0, 0.0, 1.0);
    glRotatef(angle5, 0.0, 1.0, 0.0);
    glRotatef(angle8, 1.0, 0.0, 0.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle3, 0.0, 0.0, 1.0);
    glRotatef(angle6, 0.0, 1.0, 0.0);
    glRotatef(angle9, 1.0, 0.0, 0.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Add a red sphere
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    drawSphere(0.2, 1.0, 1.0, 1.0); // Make the last sphere white and bigger

    // Add the cone shell to the last white sphere
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glTranslatef(0.3, 0.0, 0.0); // Position the cone shell below the white sphere
    glRotatef(30, 1.0, 0.0, 0.0); // Rotate the cone to point upwards
    glRotatef(-90, 0.0, 1.0, 0.0);
    glutWireCone(0.6, 0.6, 200, 200); // Draw the cone shell
    glColor3f(1.0, 1.0, 1.0); // Reset color to white
    glPopMatrix();

    GLfloat light_position[] = { 2.5, 0.25, 0.0, 1.0 };
    //GLfloat spotDirection[] = {1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glPopMatrix();
}

void setupLighting() {
    GLfloat light_diffuse[] = { lightColor[0], lightColor[1], lightColor[2], 1.0 };
    GLfloat light_specular[] = { lightColor[0], lightColor[1], lightColor[2], 1.0 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, cameraX + sin(cameraAngleY), cameraY + sin(cameraAngleX), cameraZ - cos(cameraAngleY), 0.0, 1.0, 0.0);

    glTranslatef(-1.5, 0.0, 0.0);

    drawTable(); // Draw the table
    drawBase(); // Draw the base
    drawLamp(); // Draw the lamp with the cone shell

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
    glEnable(GL_TEXTURE_2D);
    carregarTextura("texturas/madeira-hd.jpg");
}

void reset() {
    angle1 = 90.0;
    angle2 = -45.0;
    angle3 = -60.0;
    lightColor[0] = 1.0;
    lightColor[1] = 1.0;
    lightColor[2] = 1.0;
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
        case 'Q': angle1 += 5.0; break;
        case 'q': angle1 -= 5.0; break;
        case 'W': angle2 += 5.0; break;
        case 'w': angle2 -= 5.0; break;
        case 'E': angle3 += 5.0; break;
        case 'e': angle3 -= 5.0; break;
        case 'A': angle4 += 5.0; break;
        case 'a': angle4 -= 5.0; break;
        case 'S': angle5 += 5.0; break;
        case 's': angle5 -= 5.0; break;
        case 'D': angle6 += 5.0; break;
        case 'd': angle6 -= 5.0; break;
        case 'Z': angle7 += 5.0; break;
        case 'z': angle7 -= 5.0; break;
        case 'X': angle8 += 5.0; break;
        case 'x': angle8 -= 5.0; break;
        case 'C': angle9 += 5.0; break;
        case 'c': angle9 -= 5.0; break;
        case '+': cameraY += 0.1; break;
        case '-': cameraY -= 0.1; break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_PAGE_DOWN: cameraAngleX -= 0.05; break;
        case GLUT_KEY_PAGE_UP: cameraAngleX += 0.05; break;
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

    glutCreateMenu(menu);
    glutAddMenuEntry("Reset", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
