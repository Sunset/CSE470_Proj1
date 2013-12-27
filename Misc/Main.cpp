#include <iostream>
#include <cmath>
#include <time.h>
#include <sstream>
#include "glut.h"
#define PI 3.14
using namespace std;

float posX = 0.0f,posY=0.0f,posZ=0.0f;/*rotating first shape*/
float angleX = 0.0f,angleY=0.0f,angleZ=0.0f;
float angleSecondShape = 0.0f;/*rotating the second shape*/

float paddleAngle = 0.0f;
float paddlePosX = 0.0f, paddlePosY = 0.0f, paddlePosZ=0.0f;

float ballOnPaddlePosX = 0.0f, ballOnPaddlePosY = 0.0f, ballOnPaddlePosZ=0.0f;
int ballPressedFlag=0;
bool filled = false;

int window_width = 0, window_height = 0;

clock_t SystemTime;
clock_t SystemCurTime;
int duration;
enum {
  MENU_FILLED= 1,
  MENU_UNFILLED=2,
  MENU_RESTART=3,
  MENU_EXIT
};
void drawRectangle(double height, double width)
{
	if(filled == false)
	{
		/* draw a rectangle*/
	glBegin(GL_LINE_LOOP);
	glColor3f(0.2,0.3,0.3);
		glVertex2f(0+height, 0-width);
		glVertex2f(0-height, 0-width);
		glVertex2f(0-height, 0+width);
		glVertex2f(0+height, 0+width);
	glEnd();
	}
	else
	{
		/* draw a rectangle*/
	glBegin(GL_POLYGON);
	glColor3f(0.2,0.3,0.3);
		glVertex2f(0+height, 0-width);
		glVertex2f(0-height, 0-width);
		glVertex2f(0-height, 0+width);
		glVertex2f(0+height, 0+width);
	glEnd();
	}
}
void drawCircle(double radius, int samplePoints)
{
	if(filled==false){
		/*Draw a circle*/
		glBegin(GL_LINE_LOOP);
		glColor3f(0.2,0.3,0.3);
		for(int i =0; i <= samplePoints; i++)
		{
			double angle = 2* 3.14* i / samplePoints;
			double x = cos(angle)*radius;
			double y = sin(angle)*radius;
			glVertex2d(x,y);
		}
	glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glColor3f(0.2,0.3,0.3);
		for(int i =0; i <= samplePoints; i++)
		{
			double angle = 2* 3.14* i / samplePoints;
			double x = cos(angle)*radius;
			double y = sin(angle)*radius;
			glVertex2d(x,y);
		}
	glEnd();
	}
}
void drawTriangle(double input1, double input2, double input3)
{
	if(filled==false)
	{
		/* draw a triangle*/
	glBegin(GL_LINE_LOOP);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0-input1, 0-input2);
		glVertex2f(0+input2, 0-input3);
		glVertex2f(0,0+input3);
	glEnd();
	}
	else
	{
		/* draw a triangle*/
	glBegin(GL_POLYGON);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0-input1, 0-input2);
		glVertex2f(0+input2, 0-input3);
		glVertex2f(0,0+input3);
	glEnd();
	}
}
void drawArrow(double input1, double input2,double arrowScale)
{
	if(filled==false)
	{
		/*draw arrow/house*/
	glBegin(GL_LINE_LOOP);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0*arrowScale,(0+input1)*arrowScale);
		glVertex2f((0-input1)*arrowScale,(0-input1)*arrowScale);
		glVertex2f((0-input1)*arrowScale,(0-input2)*arrowScale);
		glVertex2f((0+input1)*arrowScale,(0-input2)*arrowScale);
		glVertex2f((0+input1)*arrowScale,(0-input1)*arrowScale);
	glEnd();
	}
	else
	{
		/*draw arrow/house*/
	glBegin(GL_POLYGON);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0*arrowScale,(0+input1)*arrowScale);
		glVertex2f((0-input1)*arrowScale,(0-input1)*arrowScale);
		glVertex2f((0-input1)*arrowScale,(0-input2)*arrowScale);
		glVertex2f((0+input1)*arrowScale,(0-input2)*arrowScale);
		glVertex2f((0+input1)*arrowScale,(0-input1)*arrowScale);
	glEnd();
	}
}
void drawStar(double scaleInput)
{
	if(filled==false)
	{
		/*draw star*/
	glBegin(GL_LINE_LOOP);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0*scaleInput,0.5*scaleInput);
		glVertex2f(-0.13*scaleInput,0.25*scaleInput);
		glVertex2f(-0.5*scaleInput,0.25*scaleInput);
		glVertex2f(-0.25*scaleInput,0*scaleInput);
		glVertex2f(-0.5*scaleInput,-0.25*scaleInput);
		glVertex2f(-0.13*scaleInput,-0.25*scaleInput);
		glVertex2f(0*scaleInput,-0.5*scaleInput);
		glVertex2f(0.13*scaleInput,-0.25*scaleInput);
		glVertex2f(0.5*scaleInput,-0.25*scaleInput);
		glVertex2f(0.25*scaleInput,0*scaleInput);
		glVertex2f(0.5*scaleInput,0.25*scaleInput);
		glVertex2f(0.13*scaleInput,0.25*scaleInput);
	glEnd();
	}
	else
	{
			/*draw star*/
	glBegin(GL_POLYGON);
		glColor3f(0.2,0.3,0.3);
		glVertex2f(0.0*scaleInput,0.0*scaleInput);
		glVertex2f(0.0*scaleInput,0.5*scaleInput);
		glVertex2f(-0.13*scaleInput,0.25*scaleInput);
		glVertex2f(-0.5*scaleInput,0.25*scaleInput);
		glVertex2f(-0.25*scaleInput,0*scaleInput);
		glVertex2f(-0.5*scaleInput,-0.25*scaleInput);
		glVertex2f(-0.13*scaleInput,-0.25*scaleInput);
		glVertex2f(0*scaleInput,-0.5*scaleInput);
		glVertex2f(0.13*scaleInput,-0.25*scaleInput);
		glVertex2f(0.5*scaleInput,-0.25*scaleInput);
		glVertex2f(0.25*scaleInput,0*scaleInput);
		glVertex2f(0.5*scaleInput,0.25*scaleInput);
		glVertex2f(0.13*scaleInput,0.25*scaleInput);
		glVertex2f(0.0*scaleInput,0.5*scaleInput);
	glEnd();
	}
}
void myIdle()
{
	angleX+=0.05;
	angleSecondShape+=0.1;
	if(ballPressedFlag==1)
	{
		ballOnPaddlePosY +=0.005;
	}	
	glutPostRedisplay();
}
void paddleControl(int key,int x, int y)
{	 
	switch(key){
	case GLUT_KEY_RIGHT://right
		paddlePosX=paddlePosX+0.03;	
		break;
	case GLUT_KEY_LEFT://left
		paddlePosX=paddlePosX-0.03;
		break;
	case GLUT_KEY_UP://up
		paddleAngle+=1.0;
		if(paddleAngle>360)
			paddleAngle=paddleAngle-360;
		break;
	case GLUT_KEY_DOWN://down
		paddleAngle-=1.0;
		if(paddleAngle>360)
			paddleAngle=paddleAngle-360;	 
		break;
	}
	glutPostRedisplay();
}
void ballShoot(unsigned char key, int x, int y)
{
	switch(key)
	{
	case ' ':
		ballOnPaddlePosX = paddlePosX, ballOnPaddlePosY = 0.0f, ballOnPaddlePosZ=0.0f;
		ballPressedFlag=1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void myReshape(int width, int height)
{
	window_width = width;
	window_height = height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 0.8, -0.8, 1.0);
	glViewport(0,.2*window_height,width,.8*height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
void drawingCircleOnScreen(double angleModifier, double distance)
{
	glPushMatrix();
	glRotatef(-angleX+angleModifier,posX,posY,1);
	//glTranslatef(cos(angleX+angleModifier)*distance,sin(angleX+angleModifier)*distance,0);
	glTranslatef(distance,0,0);
	glRotatef(angleX+angleModifier,posX,posY,1);
	drawCircle(0.04,360);
	glPopMatrix();
}
void drawingTriangleOnScreen(double angleModifier, double distance)
{
	glPushMatrix();
	glRotatef(angleX+angleModifier,posX,posY,1);
	//glTranslatef(0+pos1,0+pos2,0);
	glTranslatef(distance,0,0);
	glRotatef(-angleX+angleModifier,posX,posY,1);
	drawTriangle(0.05,0.05,0.05);
	glPopMatrix();
}
void SelectFromMenu(int idCommand)
{
  switch (idCommand)
    {
    case MENU_FILLED:
      filled = true;
	  
      break;

    case MENU_UNFILLED:
      filled = false;
	 
      break;     
	case MENU_RESTART:
		SystemTime =clock();

		break;
    case MENU_EXIT:
      exit (0);
      break;
    }

  // Almost any menu selection requires a redraw
  glutPostRedisplay();
}
int BuildPopupMenu (void)
{
	int submenu = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("FILL",MENU_FILLED);
	glutAddMenuEntry("WIRE",MENU_UNFILLED);
	int menu= glutCreateMenu (SelectFromMenu);
	glutAddSubMenu ("POLYGON", submenu);
	glutAddMenuEntry("Restart", MENU_RESTART);
	glutAddMenuEntry ("Exit", MENU_EXIT);

  return menu;
}
void drawText()
{
		/*drawing text on screens*/
	int score = 0;
	int lives = 10;

	glRasterPos2f(-0.3,0.7);
	SystemCurTime = clock();

	SystemCurTime=(SystemCurTime-SystemTime);

	duration=(SystemCurTime)/(int)CLOCKS_PER_SEC;
	stringstream ss;
	ss<<"Time Elapsed: " << duration << " Score: " << score<< " Lives Left: " << lives;
	string time = ss.str();
	for(int i =0;i<time.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,time[i]);
	}
}
void display()
{
	/* clear the screen*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,window_width,window_height-100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	drawRectangle(0.1,0.1);
	/*rotating stuff*/
	glPushMatrix();
	glRotatef(angleX,posX,posY,1);
	glTranslatef(.5,.5,0);
	glRotatef(-angleX,posX,posY,1);
	drawArrow(0.2,0.5,0.1);
	
	glRotatef(-angleSecondShape,posX,posY,1);
	glTranslatef(.07,.07,0);
	glRotatef(angleSecondShape,posX,posY,1);
	drawStar(0.08);
	glPopMatrix();

	/*large mass*/
	drawingCircleOnScreen(0,0.6);
	drawingCircleOnScreen(30,0.6);
	drawingCircleOnScreen(60,0.6);
	drawingCircleOnScreen(90,0.6);
	drawingCircleOnScreen(120,0.6);
	drawingCircleOnScreen(150,0.6);
	drawingCircleOnScreen(180,0.6);
	drawingCircleOnScreen(210,0.6);
	drawingCircleOnScreen(240,0.6);
	drawingCircleOnScreen(270,0.6);
	drawingCircleOnScreen(300,0.6);
	drawingCircleOnScreen(330,0.6);
	
	drawingTriangleOnScreen(0,0.3);
	drawingTriangleOnScreen(30,0.3);
	drawingTriangleOnScreen(60,0.3);
	drawingTriangleOnScreen(90,0.3);
	drawingTriangleOnScreen(120,0.3);
	drawingTriangleOnScreen(150,0.3);
	drawingTriangleOnScreen(180,0.3);
	drawingTriangleOnScreen(210,0.3);
	drawingTriangleOnScreen(240,0.3);
	drawingTriangleOnScreen(270,0.3);
	drawingTriangleOnScreen(300,0.3);
	drawingTriangleOnScreen(330,0.3);

	/*drawing paddle*/
	glPushMatrix();
	glTranslatef(paddlePosX,paddlePosY-0.8,paddlePosZ);
	glRotatef(paddleAngle,0,0,1);
	drawRectangle(0.5,0.03);
	glPopMatrix();
	
	/*draw ballon paddle*/
	glPushMatrix();
	glTranslatef(paddlePosX,ballOnPaddlePosY -0.7,ballOnPaddlePosZ );
	drawCircle(0.06,360);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,window_height-100, window_width,window_height/10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	drawText();

	glutSwapBuffers();
}

/* Initialize states -- called before */

void init()
{
	/* set background clear color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* set current color to white */
	glColor3f(1.0, 1.0, 1.0);

	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

/* The main program */

int main(int argc, char** argv)
{
	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("basics");
	BuildPopupMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	/* init some states */
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(paddleControl);
	glutKeyboardFunc(ballShoot);
	glutReshapeFunc(myReshape);
	/* entering the event loop */
	glutIdleFunc(myIdle);
	glutMainLoop();
	
	/* code here will not be executed */
}
