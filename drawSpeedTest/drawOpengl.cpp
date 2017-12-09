#include"lib.h"
#include"myUtils.h"
#include<Windows.h>
#include<opencv2\opencv.hpp>
#include"RealsenseAPI.h"
#include<GL\freeglut.h>

RealsenseAPI* realsenseAPI = nullptr;

void display();

void keyboard(unsigned char key, int x, int y);

void idle();

void idle2();

int main(int argc, char *argv[])
{
	int width = 640;
	int height = 480;
	int fps = 60;

	//RealsenseAPI realsenseAPI;
	realsenseAPI = new RealsenseAPI(width, height, fps);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("RealsenseImg");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, height, 0.0);
	glViewport(0, 0, width, height);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle2);

	glutMainLoop();
	
	delete realsenseAPI;
	return 0;
}


void display()
{
	cv::Mat img;
	realsenseAPI -> getColorImage(img);
	cv::flip(img, img, 0);
	cv::cvtColor(img,img, CV_BGR2RGB);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(img.cols, img.rows,
		GL_RGB, GL_UNSIGNED_BYTE, img.data);
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
	case '\033':
		glutLeaveMainLoop();
	default:
		break;
	}
}

void idle()
{
	cv::Mat mat = cv::imread("test.jpg");
	//realsenseAPI->getColorImage(mat);
	cv::flip(mat, mat, 0);
	cv::cvtColor(mat, mat, CV_BGR2RGB);

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(mat.cols, mat.rows,
		GL_RGB, GL_UNSIGNED_BYTE, mat.data);
	glFlush();
	printFPS();
}

void idle2()
{
	static cv::Mat mat = cv::imread("test.jpg");
	static bool first = true;
	if (first)
	{
		first = false;
		cv::resize(mat, mat, cv::Size(realsenseAPI->getWidth(), realsenseAPI->getHeight()));
		//realsenseAPI->getColorImage(mat);
		cv::flip(mat, mat, 0);
		cv::cvtColor(mat, mat, CV_BGR2RGB);
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(mat.cols, mat.rows,
		GL_RGB, GL_UNSIGNED_BYTE, mat.data);
	glFlush();
	printFPS();
}
