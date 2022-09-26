/* Name: Ashutosh More
ID: 300713817
CSCI 272
Project 2. Moving spheres.
Note: Initially when project file is run, the wireframe is zoomed in and not visible.
Please press down arrow key to zoom out and make the frame visible. */
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>
using namespace std;

bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f }; //
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

float angle,b,a2=-1.0,b2=-0.5,c2=0,a3=-1.5,b3=1.0,c3=0.0,a4=3.0,b4=-1.0,c4=2.7,a5=2,b5=1.0f,c5=0.5,dir1=1,dir2=1,dir3=1,dir4=1,dir5=1,dir6=1,dir7=1,dir8=1,dir9=1,dir10=1,dir11=1,dir12=1;



/* GLUT callback Handlers */

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

    gluLookAt(0,5,b,0.0,0.0,0.0,0.0,1.0,0.0);    //using variable in lookat for zoom in and zoom-out.

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code
    glPushMatrix ();
    glRotatef(angle,0,1,0);         //using angle variable for rotating the frame.
    glutWireCube(8);                //declaring size of the wireframe

   glColor3d(1,1,0);                //translating first sphere with yellow color.
   glTranslatef (a5,b5,c5);
   glutSolidSphere(0.5,20,20);

   glPopMatrix ();

   glPushMatrix ();
   glColor3d(0,1,1);            //translating second sphere in teal or light-blue color.
   glTranslatef (a2,b2,c2);
   glutSolidSphere(0.5,20,20);
   glPopMatrix ();

   glPushMatrix ();
   glColor3d(0,0,1);            //translating third sphere in blue color.
   glTranslatef (a3,b3,c3);
   glutSolidSphere (0.5,20,20);
   glPopMatrix ();

   glPushMatrix ();
   glColor3d(1,1,1);            //translating fourth sphere in white color.
   glTranslatef (a4,b4,c4);
   glutSolidSphere(0.5,20,20);
   glPopMatrix ();

   glPopMatrix ();
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

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:               //zoom-in with 0.5 increment
        b=b+0.5;
        break;
    case GLUT_KEY_DOWN:             //zoom-out with 0.5 decrement.
        b=b-0.5;
        break;
    case GLUT_KEY_RIGHT:            //rotating wireframe left or anticlockwise in 5 degrees
        angle+=5;
        break;
    case GLUT_KEY_LEFT:             //rotating wireframe right or clockwise with 5 degrees.
        angle-=5;
        break;
    }
  glutPostRedisplay();

}

void timer(int)
{

    if(3.5-a2<0.2 || a2+3.5 <0.2)               //checking wall collision for ball 1...
    dir4*=-1;

    a2=a2-(dir4*0.2);

    if(3.5-b2<0.2 || b2+3.5 <0.2)
    dir5*=-1;

    b2=b2-(dir5*0.2);

    if(3.5-c2<0.2 || c2+3.5 <0.2)
    dir6*=-1;

    c2=c2-(dir6*0.2);                              //end


    if(3.5-a3<0.2 || a3+3.5 <0.2)                  //checking wall collision for ball 2...
    dir7*=-1;

    a3=a3-(dir7*0.2);

    if(3.5-b3<0.2 || b3+3.5 <0.2)
    dir8*=-1;

    b3=b3-(dir8*0.2);

    if(3.5-c3<0.2 || c3+3.5 <0.2)
    dir9*=-1;

    c3=c3-(dir9*0.2);                               //end


    if(3.5-a4<0.2 || a4+3.5 <0.2)                   //checking wall collision for ball 3...
    dir10*=-1;

    a4=a4-(dir10*0.2);

    if(3.5-b4<0.2 || b4+3.5 <0.2)
    dir11*=-1;

    b4=b4-(dir11*0.2);

    if(3.5-c4<0.2 || c4+3.5 <0.2)
    dir12*=-1;

    c4=c4-(dir12*0.2);                              //end

     if(3.5-a5<0.2 || a5+3.5 <0.2)               //checking wall collision for ball 4...
    dir1*=-1;

    a5=a5-(dir1*0.2);

    if(3.5-b5<0.2 || b5+3.5 <0.2)
    dir2*=-1;

    b5=b5-(dir2*0.2);

    if(3.5-c5<0.2 || c5+3.5 <0.2)
    dir3*=-1;

    c5=c5-(dir3*0.2);                           //end
/*
     if (1 >sqrt(((a5-a2)*(a5-a2))+((b5-b2)*(b5-b2))+((c5-c2)*(c5-c2))))        //checking for collision condition of ball 1 and ball 4
   {

     if(-3.3<a5<3.3 && -3.3<b5<3.3 && -3.3<c5<3.3 )
      {

         a5+=0.2;
         b5+=0.2;
         c5+=0.2;
      }
      if(-3.3<a2<3.3 && -3.3<b2<3.3 && -3.3<c2<3.3 )
       {

       a2-=0.2;
       b2-=0.2;
       c2-=0.2;
       }
   }

   if (1 >sqrt(((a5-a3)*(a5-a3))+((b5-b3)*(b5-b3))+((c5-c3)*(c5-c3))))      //checking collision condition for ball 2 and 4
   {

       if(-3.3<a5<3.3 && -3.3<b5<3.3 && -3.3<c5<3.3 )
      {

         a5+=0.2;
         b5+=0.2;
         c5+=0.2;
      }
      if(-3.3<a3<3.3 && -3.3<b3<3.3 && -3.3<c3<3.3 )
       {

       a3-=0.2;
       b3-=0.2;
       c3-=0.2;
       }

   }


   if (1 >sqrt(((a5-a4)*(a5-a4))+((b5-b4)*(b5-b4))+((c5-c4)*(c5-c4))))      //checking collision condition for ball 3 and 4
   {

        if(-3.3<a5<3.3 && -3.3<b5<3.3 && -3.3<c5<3.3 )
      {

         a5+=0.2;
         b5+=0.2;
         c5+=0.2;
      }
       if(-3.3<a4<3.3 && -3.3<b4<3.3 && -3.3<c4<3.3 )
       {

       a4-=0.2;
       b4-=0.2;
       c4-=0.2;
       }

   }

   if (1 >sqrt(((a3-a2)*(a3-a2))+((b3-b2)*(b3-b2))+((c3-c2)*(c3-c2))))      //checking collision condition for ball 1 and 2
   {

        if(-3.3<a3<3.3 && -3.3<b3<3.3 && -3.3<c3<3.3 )
      {

       a3+=0.2;
       b3+=0.2;
       c3+=0.2;
      }
      if(-3.3<a2<3.3 && -3.3<b2<3.3 && -3.3<c2<3.3 )
       {

       a2-=0.2;
       b2-=0.2;
       c2-=0.2;
       }

   }

   if (1 >sqrt(((a4-a2)*(a4-a2))+((b4-b2)*(b4-b2))+((c4-c2)*(c4-c2))))      //checking collision condition for ball 1 and 3
   {

        if(-3.3<a4<3.3 && -3.3<b4<3.3 && -3.3<c4<3.3 )
      {

       a4+=0.2;
       b4+=0.2;
       c4+=0.2;
      }
      if(-3.3<a2<3.3 && -3.3<b2<3.3 && -3.3<c2<3.3 )
       {

       a2-=0.2;
       b2-=0.2;
       c2-=0.2;
       }

   }

   if (1 >sqrt(((a4-a3)*(a4-a3))+((b4-b3)*(b4-b3))+((c4-c3)*(c4-c3))))      //checking collision condition for ball 2 and 3
   {

       if(-3.3<a4<3.3 && -3.3<b4<3.3 && -3.3<c4<3.3 )
      {

       a4+=0.2;
       b4+=0.2;
       c4+=0.2;
      }
      if(-3.3<a3<3.3 && -3.3<b3<3.3 && -3.3<c3<3.3 )
       {

       a3-=0.2;
       b3-=0.2;
       c3-=0.2;
       }

   }
*/
     glutPostRedisplay();
     glutTimerFunc(150,timer,0);

}

static void idle(void)
{

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
    glutTimerFunc(0,timer,0);
    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
