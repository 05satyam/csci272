/*
Student id: 300882882
Name: Satyam Mittal
Course: CSCI 272
Project name: Sphere Move (assignment 2)

*/

#include <iostream>

#include <string.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h> // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#include <GLUT/glut.h> // Header File For The GLut Library
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/*
below are the variable declarations for all the 4 balls which represents the x,y,z coordinates of the ball
*/
float xDir1=-3.4, xDir2=-1.0, xDir3=1.0, xDir4=0.0;   
float yDir1=0.0, yDir2=-0.5, yDir3=3.4, yDir4=-3.4;
float zDir1=0.0, zDir2=0.5, zDir3=0.5, zDir4=0.0;

//below variables are use for resizing and rotating the fram of cube using up,down,left,right arrow keys
static float rotationAngle, resizeFrame=11.0;

int it=0;
//below variables are used to decide the movement directions of balls
float ball1_Dir=1, ball2_Dir=1, ball3_Dir=1, ball4_Dir=1;

//below variables are for changing the color od the balls after collision
float ball1_colorR=1, ball1_colorG=0, ball1_colorB=0.6;
float ball4_colorR=1, ball4_colorG=1, ball4_colorB=0;


//a2=-1.0,b2=-0.5,c2=0,a3=-1.5,b3=1.0,c3=0.0,a4=3.0,b4=-1.0,c4=2.7,a5=2,b5=1.0f,c5=0.5,
static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (50.0f,1,0.1f, 100.0f);
 }
 
 

static void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,resizeFrame,0.0,0.0,0.0,0.0,1.0,0.0);     //using this method we resize the cube frame

    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        //Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);        //Toggle WIRE FRAME

   
     //using rotateAngle we rotate the cube using up down keys
     glRotatef(rotationAngle,0,1,0);               

    //creating cube using this method 
    glutWireCube(7.0);                              
   
//------------------draw ball1-----------------------
    glPushMatrix();
    //this functions decides the color of the ball
    glColor3d(ball1_colorR,ball1_colorG,ball1_colorB);  

    glTranslatef(xDir1,yDir1,zDir1);

    //this method is used for creating the sphere
    glutSolidSphere(0.5,20,20);                            
    glPopMatrix();

//------------------draw ball2-----------------------
    //this functions decides the color of the ball
    glColor3d(0,1,1);  

    glPushMatrix();
    glTranslatef(xDir2,yDir2,zDir2);

    //this method is used for creating the sphere
    glutSolidSphere(0.5,20,20);
    glPopMatrix();

//------------------draw ball3-----------------------
    //this functions decides the color of the ball
    glColor3d(1,0.2,1);  

    glPushMatrix();
    glTranslatef(xDir3,yDir3,zDir3);

    //this method is used for creating the sphere
    glutSolidSphere(0.5,20,20);
    glPopMatrix();

//------------------draw ball4-----------------------
    //this functions decides the color of the ball
    glColor3d(ball4_colorR,ball4_colorG,ball4_colorB);

    glPushMatrix();
    glTranslatef(xDir4,yDir4,zDir4);

    //this method is used for creating the sphere
    glutSolidSphere(0.5,20,20);
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
}

//method to handle the orientation of the cube
void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:               //zoom-in with 0.5 increment
        resizeFrame=resizeFrame+0.5;
        break;
    case GLUT_KEY_DOWN:             //zoom-out with 0.5 decrement.
        resizeFrame=resizeFrame-0.5;
        break;
    case GLUT_KEY_RIGHT:            //rotating wireframe left or anticlockwise in 5 degrees
        rotationAngle+=5;
        break;
    case GLUT_KEY_LEFT:             //rotating wireframe right or clockwise with 5 degrees.
        rotationAngle-=5;
        break;    
    break;
   }
  glutPostRedisplay();
}

/*
    method for handling the movements of the balls and handle the collision among balls
*/
static void idle(void)
{

/*---------------------------BALL and WALL COLLISION : code begin --------------------------------------

     Here i have considered 3.4 on x positive axis and -3.4 on x negative axis 
     similarly +3.4 and -3.4 or y axis 
     and +3.4 and -3.4 on z axis.
*/


   /*
     ball1  here we are changing the x- direction of the ball after ball hits the wall of the cubes 
     and translate the ball in opposite direction
   */
   if(xDir1 >= 3.4) ball1_Dir = -1;
   else if(xDir1 <= -3.4) ball1_Dir = 1;
   
     xDir1 = xDir1 + ball1_Dir * (0.1);


   /*
     ball2 : here we are changing the x and y direction of the ball after ball hits the wall of the cubes 
    and translate the ball in opposite direction
   */
   if(xDir2 >= 3.4) ball2_Dir = -1;
   else if(xDir2 <= -3.4) ball2_Dir = 1;
    xDir2 += ball2_Dir*(0.1);

   if(yDir2 >= 3.4)  ball2_Dir = -1;
   else if(yDir2 <= -3.4) ball2_Dir = 1;
    yDir2 += ball2_Dir*(0.1); 
 
  

    /*
      ball3 : here we are changing the x,y,z direction of the ball after ball hit the walls of cube
      and translate the ball in opposite direction
    */
   if(xDir3 >= 3.4) ball3_Dir = -1;
   else if(xDir3 <= -3.4)ball3_Dir = 1;
    xDir3 += ball3_Dir *(0.1);

   if(yDir3 >= 3.4)  ball3_Dir = -1;
   else if(yDir3 <= -3.4) ball3_Dir = 1;
    yDir3 += ball3_Dir * (0.1);
    
   if(zDir3 >= 3.4)  ball3_Dir = -1;
   else if(zDir3 <= -3.4) ball3_Dir = 1;
    zDir3 += ball3_Dir *(0.1); 


    /*
      ball4 : here we are chaing the y-direction of ball 4 after ball hit the wall of the cube
      and translate the ball in opposite direction
    */
    if(yDir4 <= -3.4) 
        ball4_Dir =1;
    else if(yDir4 >= 3.4)
        ball4_Dir = -1;
  
    yDir4 = yDir4 +  ball4_Dir *(0.1);

//-----------------------------------------BALL and WALL COLLISION : code ends -------------------------------------------------   

/* ---------------------------------------------COLLISION between balls : code begin----------------------------------------------

   Collision formula: if (distance from ball1 center to ball2 center < radius1 + radius) collision true
*/

//BALL 1 and BALL 4
 if (1 >sqrt((abs(xDir4-xDir1)*abs(xDir4-xDir1))+
        (abs(yDir4-yDir1)*abs(yDir4-yDir1))+(abs(zDir4-zDir1)*abs(zDir4-zDir1))))   
   {

     if(-3.3<xDir4<3.3 && -3.3<yDir4<3.3 && -3.3<zDir4<3.3 ){
         ball4_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir4-=0.2;
         yDir4-=0.2;
         zDir4-=0.2;
         //ball4_colorR=rand()%2; ball4_colorG=rand()%2;
      }

      if(-3.3<xDir1<3.3 && -3.3<yDir1<3.3 && -3.3<zDir1<3.3 ){
         ball1_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir1+=0.2;
        yDir1+=0.2;
        zDir1+=0.2;
        //ball1_colorR=rand()%10; ball1_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }


    //ball1 and ball3
     if (1 >sqrt((abs(xDir3-xDir1)*abs(xDir3-xDir1))+
        (abs(yDir3-yDir1)*abs(yDir3-yDir1))+(abs(zDir3-zDir1)*abs(zDir3-zDir1))))   
   {

     if(-3.3<xDir3<3.3 && -3.3<yDir3<3.3 && -3.3<zDir3<3.3 ){
         ball3_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir3-=0.2;
         yDir3-=0.2;
         zDir3-=0.2;
         //ball4_colorR=rand()%10; ball4_colorG=rand()%10;
      }

      if(-3.3<xDir1<3.3 && -3.3<yDir1<3.3 && -3.3<zDir1<3.3 ){
         ball1_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir1+=0.2;
        yDir1+=0.2;
        zDir1+=0.2;
        //ball2_colorR=rand()%10; ball2_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }

    // BALL1 and BALL 2
    if (1 >sqrt((abs(xDir2-xDir1)*abs(xDir2-xDir1))+
        (abs(yDir2-yDir1)*abs(yDir2-yDir1))+(abs(zDir2-zDir1)*abs(zDir2-zDir1))))   
   {

     if(-3.3<xDir2<3.3 && -3.3<yDir2<3.3 && -3.3<zDir2<3.3 ){
         ball2_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir2-=0.2;
         yDir2-=0.2;
         zDir2-=0.2;
         //ball4_colorR=rand()%10; ball4_colorG=rand()%10;
      }

      if(-3.3<xDir1<3.3 && -3.3<yDir1<3.3 && -3.3<zDir1<3.3 ){
         ball1_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir1+=0.2;
        yDir1+=0.2;
        zDir1+=0.2;
        //ball2_colorR=rand()%10; ball2_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }


   // ball2 and ball3
   if (1 >sqrt((abs(xDir3-xDir2)*abs(xDir3-xDir2))+
        (abs(yDir3-yDir2)*abs(yDir3-yDir2))+(abs(zDir3-zDir2)*abs(zDir3-zDir2))))   
   {

     if(-3.3<xDir3<3.3 && -3.3<yDir3<3.3 && -3.3<zDir3<3.3 ){
         ball3_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir3-=0.2;
         yDir3-=0.2;
         zDir3-=0.2;
         //ball4_colorR=rand()%10; ball4_colorG=rand()%10;
      }

      if(-3.3<xDir2<3.3 && -3.3<yDir2<3.3 && -3.3<zDir2<3.3 ){
        ball2_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir2+=0.2;
        yDir2+=0.2;
        zDir2+=0.2;
        //ball2_colorR=rand()%10; ball2_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }

   // BALL 2 and BALL 4
    if (1 >sqrt((abs(xDir4-xDir2)*abs(xDir4-xDir2))+
        (abs(yDir4-yDir2)*abs(yDir4-yDir2))+(abs(zDir4-zDir2)*abs(zDir4-zDir2))))   
   {

     if(-3.3<xDir4<3.3 && -3.3<yDir4<3.3 && -3.3<zDir4<3.3 ){
         ball4_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir4-=0.2;
         yDir4-=0.2;
         zDir4-=0.2;
         //ball4_colorR=rand()%10; ball4_colorG=rand()%10;
      }

      if(-3.3<xDir2<3.3 && -3.3<yDir2<3.3 && -3.3<zDir2<3.3 ){
         ball2_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir2+=0.2;
        yDir2+=0.2;
        zDir2+=0.2;
        //ball1_colorR=rand()%10; ball1_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }

    // BALL 3 and BALL 4
     if (1 >sqrt((abs(xDir3-xDir4)*abs(xDir3-xDir4))+
        (abs(yDir3-yDir4)*abs(yDir3-yDir4))+(abs(zDir3-zDir4)*abs(zDir3-zDir4))))   
   {

     if(-3.3<xDir3<3.3 && -3.3<yDir3<3.3 && -3.3<zDir3<3.3 ){
         ball3_Dir *= -1;  //changing the direction of ball 4 after collision
         xDir3-=0.2;
         yDir3-=0.2;
         zDir3-=0.2;
         //ball4_colorR=rand()%10; ball4_colorG=rand()%10;
      }

      if(-3.3<xDir4<3.3 && -3.3<yDir4<3.3 && -3.3<zDir4<3.3 ){
         ball4_Dir *=-1;   //changing the direction of ball 1 after collision
        xDir4+=0.2;
        yDir4+=0.2;
        zDir4+=0.2;
        //ball1_colorR=rand()%10; ball1_colorG=rand()%10;  // trying to change the color of ball 1 after every collison with ball4
       }
   }


//---------------------------------COLLISION between ball:  code ends---------------------------------

    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
