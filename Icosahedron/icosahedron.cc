// Draw an Icosahedron
// ECE4893/8893 Project 4
// YOUR NAME HERE

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932
int width, height;
char** argv2;
// These are the 12 vertices for the icosahedron
static GLfloat vdata[NVERTEX][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};

// These are the 20 faces.  Each of the three entries for each 
// vertex gives the 3 vertices that make the face.
static GLint tindices[NFACE][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

int testNumber; // Global variable indicating which test number is desired
 
// Test cases.  Fill in your code for each test case

void Triangle(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3) {
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_TRIANGLES);
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glEnd();   
}


void normalize(GLfloat v[3])
{
GLfloat length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2] * v[2]);
v[0] /= length;
v[1] /= length;
v[2] /= length;
}


void Divide(GLfloat* vertex1, GLfloat* vertex2, GLfloat* vertex3, int divisions) {
if (divisions == 0) {
   Triangle(vertex1, vertex2, vertex3);
}
else {
GLfloat vertex12[] = {vertex1[0] + vertex2[0], vertex1[1] + vertex2[1], vertex1[2] + vertex2[2]};
normalize(vertex12);
GLfloat vertex13[] = {vertex1[0] + vertex3[0], vertex1[1] + vertex3[1], vertex1[2] + vertex3[2]};
normalize(vertex13);
GLfloat vertex23[] = {vertex3[0] + vertex2[0], vertex3[1] + vertex2[1], vertex3[2] + vertex2[2]};
normalize(vertex23);
Divide(vertex1,vertex12,vertex13, divisions-1);
Divide(vertex2,vertex12,vertex23, divisions-1);
Divide(vertex3,vertex13,vertex23, divisions-1);
Divide(vertex12,vertex13,vertex23, divisions-1);

}

}

void Icosahedron(int x) {
for (int i = 0; i < NFACE; i++) {
    Divide(vdata[tindices[i][0]],vdata[tindices[i][1]], vdata[tindices[i][2]], x);
}
}


void RefreshTimer(int) {
glutPostRedisplay();
glutTimerFunc(1000.0 /10, RefreshTimer, 0);
}

void Test1()
{
Icosahedron(0);
}

void Test2()
{
static GLfloat xRot = 0.0;
static GLfloat yRot = 0.0;
glRotatef(xRot, 1.0, 0.0, 0.0);
glRotatef(yRot, 0.0, 1.0, 0.0);
xRot += 1.0;
yRot -= 1.0;
Test1();
}

void Test3()
{
Icosahedron(1);
}

void Test4()
{
static GLfloat xRot = 0.0;
static GLfloat yRot = 0.0;
glRotatef(xRot, 1.0, 0.0, 0.0);
glRotatef(yRot, 0.0, 1.0, 0.0);
xRot += 1.0;
yRot -= 1.0;
Test3();
}

void Test5(int depth)
{
Icosahedron(depth);
}

void Test6(int depth)
{
static GLfloat xRot = 0.0;
static GLfloat yRot = 0.0;
glRotatef(xRot, 1.0, 0.0, 0.0);
glRotatef(yRot, 0.0, 1.0, 0.0);
xRot += 1.0;
yRot -= 1.0;
Test5(depth);
}


void display(void) 
{
glEnable(GL_LINE_SMOOTH | GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT);
glClear(GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glLoadIdentity();
glTranslatef(width/2, height/2,0);
glScalef(200.0,200.0,200.0);
int depth;
switch (testNumber) {
case 1: Test1();
break;
case 2: Test2();
break;
case 3: Test3();
break;
case 4: Test4();
break;
case 5:
depth = atoi(argv2[2]);
Test5(depth);
break;
case 6: 
depth = atoi(argv2[2]);
Test6(depth);
break;
default :
Test1();
}
glPopMatrix();
glutSwapBuffers();
}

void ReshapeFunc(int w, int h) {
glViewport(0,0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)w *2, (GLdouble)-w *2);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
height = h;
width = w;
}


int main(int argc, char** argv)
{
  argv2 = argv;
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      exit(1);
    }
  // Set the global test number
  testNumber = atol(argv[1]);
  // Initialize glut  and create your window here
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700,700);
  glutInitWindowPosition(100,100); 
  glutCreateWindow("Ico");
  glClearColor(0.0,0.0,0.0, 0.0);
  glShadeModel(GL_FLAT);
  width = glutGet(GLUT_WINDOW_WIDTH);
  height = glutGet(GLUT_WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, (GLdouble)width, (GLdouble)0.0, height, (GLdouble)width * 2, (GLdouble)-width *2);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  
  // Set your glut callbacks here
  glutDisplayFunc(display);
  glutReshapeFunc(ReshapeFunc);
  glutTimerFunc(1000.0/10, RefreshTimer, 0);
  // Enter the glut main loop here
  glutMainLoop();
  return 0;
}

