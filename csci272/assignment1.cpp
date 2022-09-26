#include <iostream>

#include <string.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h> // Header File For The OpenGL32 Library
#include <OpenGL/glu.h> // Header File For The GLu32 Library
#include <GLUT/glut.h> // Header File For The GLut Library
#include <stdlib.h>
#include <stdio.h>

float x,y,oldX,oldY,a,b,c,d,e,f, num;       //declare the necessary variables
int n=0;
void resize(int width, int height)
{
    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);

    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-2.5,2.75,10.5,0, -1.0, 1.0);      // adjusted for suitable viewport
oldX=oldY=1.0;
 n=200000;

}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);       
  // your code here
                
  for(int i=0;i<n;i++){             
    num=rand() % 100;              
    if(num<7){                          //condition for ƒ4
        a= -0.15; b =0.26; c =0.28; d =0.24; e =0; f=0.44;
    }
    else if(num<14){            //condition for ƒ3
        a= 0.2; b =0.23; c =-0.26; d =0.22; e =0; f=1.6;
    }
    else if(num<99){        //condition for ƒ2
        a= 0.85; b = -0.04; c =0.04; d =0.85; e =0; f=1.6;
    }
    else{                   //condition for ƒ1
        a= 0; b =0; c =0; d =0.16; e =0; f=0;
    }
    x=a*oldX + c*oldY + e;
    y=b*oldX + d*oldY + f;

    glColor3f(0,1,0);           
    glBegin(GL_POINTS);
    glVertex2f(x,y);          
    glEnd();
    oldX=x;
    oldY=y;

  }
  glFlush ();                           // clear buffer
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

 
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (600, 800);                //window screen
   
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Program1");                //program title
   init();
   glutDisplayFunc(display);                     //callback function for display
   
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   
   glutMainLoop();                               //loop

    return EXIT_SUCCESS;
}