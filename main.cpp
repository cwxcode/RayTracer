#include <iostream>
//#include <vector>
#include <math.h>

#include <GL/glut.h>
#include "Vector3.h"
#include "Engine.h"

using namespace RayTracing;

#define sceneWidth 400
#define sceneHeight 400

const double PI=3.1415926;
GLubyte Image[sceneWidth][sceneHeight][3];

static GLint height;

Vector3* Camera=NULL;
Ray* ray=NULL;

double fovy=PI/3;
double fovx=PI/3;
double aspect=sceneWidth/sceneHeight;
double Znear=0;
double Zfar=10;

static double distance =0;

void Init_Object()
{
	Engine engine;

	Camera=new Vector3(0,0,10);

	ray=new Ray();
	ray->SetOrigin(*Camera);

	for(int iL1 = 0; iL1 < sceneHeight; iL1 ++)
	{
		for(int iL2 = 0; iL2 < sceneWidth; iL2 ++)
		{
			double m = iL1 - sceneWidth / 2;
			double n = iL2 - sceneHeight / 2;

			double y = tan(fovx / 2) * (Camera->m_z - Znear) * m / (sceneWidth / 2);
			double x = tan(fovy / 2) * (Camera->m_z - Znear) * n / ( sceneHeight / 2);
			double z = -1 * Znear;

			Vector3* dir = new Vector3(x - Camera->m_x, y - Camera->m_y, z - Camera->m_z);
			dir->Normalize();

			//fire rays from screen 
			ray->SetDirection(*dir);
			ray->SetOrigin(Vector3(x, y, z));

			Color color(0, 0, 0);

			double dist = -1;

			engine.RayTrace(ray, color, 0, 0, dist);

			if(color.m_x > 1)
				color.m_x = 1;
			if(color.m_y > 1)
				color.m_y = 1;
			if(color.m_z > 1)
				color.m_z = 1;


			Image[iL1][iL2][0] = (unsigned char) (color.m_x *255);
			Image[iL1][iL2][1] = (unsigned char) (color.m_y * 255); 
			Image[iL1][iL2][2] = (unsigned char) (color.m_z * 255);


		}	
	}
}

void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);

	Init_Object();

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
	glDrawPixels(sceneWidth,sceneHeight,GL_RGB,GL_UNSIGNED_BYTE,Image);
	glFlush();
}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	height=(GLint)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(sceneWidth,sceneHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}