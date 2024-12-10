#include <GL/glut.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GLuint idTextura;
float angle1 = 90.0, angle2 = 315.0, angle3 = 315.0;
float angle4 = 0.0, angle5 = 0.0, angle6 = 0.0;
float angle7 = 0.0, angle8 = 0.0, angle9 = 0.0;
float lightColor[3] = {1.0, 1.0, 1.0};
float cameraX = 0.0, cameraY = 2.0, cameraZ = 9.0;
float cameraAngleX = 0.0, cameraAngleY = -0.1;
bool lightOn = true;
int color = 4;

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
    glColor3f(0.2, 0.2, 0.2); // Cinza escuro
    glScalef(1.0, 0.2, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawSphere(float size, float r, float g, float b) {
    glColor3f(r, g, b); // Cor da esfera
    glutSolidSphere(size, 20, 20);
    glColor3f(1.0, 1.0, 1.0); // Reseta cor para branco
}

void drawBase() {
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2); // Cinza escuro
    glTranslatef(-2.0, -0.25, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.5, 0.5, 20, 20);
    glColor3f(1.0, 1.0, 1.0); // Reseta cor para branco
    glPopMatrix();
}

void drawTable() {
    glPushMatrix();
    glTranslatef(0.0, -0.50, 0.0); // Posicionar mesa embaixo da base

    glBindTexture(GL_TEXTURE_2D, idTextura);
    glBegin(GL_QUADS);
        // Face superior
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, 0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        // Face inferior
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, -0.25, 5.0);
        // Face frontal
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        // Face traseira
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, -5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, -5.0);
        // Face esquerda
        glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(-5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(-5.0, 0.25, -5.0);
        // Face direita
        glTexCoord2f(0.0, 0.0); glVertex3f(5.0, -0.25, -5.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(5.0, -0.25, 5.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 0.25, 5.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(5.0, 0.25, -5.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Desvincula textura
    glColor3f(1.0, 1.0, 1.0); // Reseta cor para branco
    glPopMatrix();
}

void drawLamp() {
    glPushMatrix();
    glTranslatef(-2.0, 0.25, 0.0); // Move esfera para o topo do cone
    drawSphere(0.1, 1.0, 0.0, 0.0); // Adiciona esfera entre o cone e o primeiro segmento

    glRotatef(angle1, 0.0, 0.0, 1.0);
    glRotatef(angle4, 0.0, 1.0, 0.0);
    glRotatef(angle7, 1.0, 0.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle2, 0.0, 0.0, 1.0);
    glRotatef(angle5, 0.0, 1.0, 0.0);
    glRotatef(angle8, 1.0, 0.0, 0.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Outra esfera
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(angle3, 0.0, 0.0, 1.0);
    glRotatef(angle6, 0.0, 1.0, 0.0);
    glRotatef(angle9, 1.0, 0.0, 0.0);
    drawSphere(0.1, 1.0, 0.0, 0.0); // Outra esfera
    glTranslatef(0.5, 0.0, 0.0);
    drawSegment();

    glTranslatef(0.5, 0.0, 0.0);
    drawSphere(0.2, 1.0, 1.0, 1.0); // Esfera da lâmpada

    // Casca de cone em volta da lâmpada
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); // Preto
    glTranslatef(0.3, 0.0, 0.0); // Posiciona o cone
    glRotatef(30, 1.0, 0.0, 0.0); // Rotaciona o cone
    glRotatef(-90, 0.0, 1.0, 0.0);
    glutWireCone(0.6, 0.6, 250, 250); // Desenha o cone
    glColor3f(1.0, 1.0, 1.0); // Reseta cor para branco
    glPopMatrix();

    GLfloat light_position[] = { 2.5, 0.25, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void drawTeapot() {
    glPushMatrix();
    glTranslatef(1.5, 0.5, 0.0); // Posiciona o bule na mesa
    glColor3f(0.5, 0.5, 0.5); // Cinza
    glutSolidTeapot(1.0); // Desenha o bule
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

    drawTable(); // Desenha a mesa
    drawBase(); // Desenha a base
    drawLamp(); // Desenha a lâmpada
    drawTeapot(); // Desenha o bule

    glutSwapBuffers();
}

void init() {
    glClearColor(0.5, 0.5, 0.5, 1.0); // Muda a cor de fundo para ciano
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
    angle2 = 315.0;
    angle3 = 315.0;
    angle4 = 0.0;
    angle5 = 0.0;
    angle6 = 0.0;
    angle7 = 0.0;
    angle8 = 0.0;
    angle9 = 0.0;
    lightColor[0] = 1.0;
    lightColor[1] = 1.0;
    lightColor[2] = 1.0;
    cameraX = 0.0;
    cameraY = 2.0;
    cameraZ = 9.0;
    cameraAngleX = 0.0;
    cameraAngleY = -0.1;
    lightOn = true;
    color = 4;
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

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lightOn = !lightOn; // Liga ou desliga luz
        if (!lightOn) {
            lightColor[0] = 0.0;
            lightColor[1] = 0.0;
            lightColor[2] = 0.0;
        }
        else if (color == 1) {
            lightColor[0] = 1.0;
            lightColor[1] = 0.0;
            lightColor[2] = 0.0;
        }
        else if (color == 2) {
            lightColor[0] = 0.0;
            lightColor[1] = 1.0;
            lightColor[2] = 0.0;
        }
        else if (color == 3) {
            lightColor[0] = 0.0;
            lightColor[1] = 0.0;
            lightColor[2] = 1.0;
        }
        else if (color == 4) {
            lightColor[0] = 1.0;
            lightColor[1] = 1.0;
            lightColor[2] = 1.0;
        }
        setupLighting();
        glutPostRedisplay();
    }
}

void menu(int option) {
    if (option == 0) {
        reset();
    } else if (option == 1) {
        lightColor[0] = 1.0; // Vermelho
        lightColor[1] = 0.0;
        lightColor[2] = 0.0;
        color = option;
    } else if (option == 2) {
        lightColor[0] = 0.0; // Verde
        lightColor[1] = 1.0;
        lightColor[2] = 0.0;
        color = option;
    } else if (option == 3) {
        lightColor[0] = 0.0; // Azul
        lightColor[1] = 0.0;
        lightColor[2] = 1.0;
        color = option;
    } else if (option == 4) {
        lightColor[0] = 1.0; // Branco
        lightColor[1] = 1.0;
        lightColor[2] = 1.0;
        color = option;
    }
    setupLighting();
    glutPostRedisplay();
}

void createMenu() {
    int submenu = glutCreateMenu(menu);
    glutAddMenuEntry("Vermelho", 1);
    glutAddMenuEntry("Verde", 2);
    glutAddMenuEntry("Azul", 3);
    glutAddMenuEntry("Branco", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Reset", 0);
    glutAddSubMenu("Mudar cor da luz", submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lampada mecanica");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    createMenu();

    glutMainLoop();
    return 0;
}