#include <iostream>
#include <string>
#include <regex>
#include <GL/glut.h>

// rotateY and rotateX are used for rotating the view
double rotateY = 0;
double rotateX = 0;

// Stair parameters, assigned to default values
double width = 0.20;
double depth = 0.05;
double stepHeight = 0.1;
double fullHeight = 1.3;

void initGL()
{
	// Set background colour to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Set background depth to farthest
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void specialKeys(int key, int x, int y) {

	// Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotateY += 5;

	// Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotateY -= 5;

	// Up arrow - increase rotation by 5 degree
	else if (key == GLUT_KEY_UP)
		rotateX += 5;

	// Down arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_DOWN)
		rotateX -= 5;

	// Request display update
	glutPostRedisplay();

}

void drawStairs()
{
	// Clear window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Start drawing
	for (int i = 0; i < fullHeight / stepHeight; i++) {
		glTranslatef(0.0f, -fullHeight, -fullHeight * 4);
		glRotatef(rotateX, 1.0, 0.0, 0.0);
		glRotatef(rotateY, 0.0, 1.0, 0.0);

		glBegin(GL_QUADS);

		// Back
		glColor3f(0.6f, 0.6f, 0.6f);
		glVertex3f(width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);

		// Front
		glVertex3f(width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);

		// Right
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);

		// Left
		glVertex3f(-width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);

		// Top
		glColor3f(0.9f, 0.9f, 0.9f);
		glVertex3f(width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);

		// Bottom
		glVertex3f(width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);
		glVertex3f(width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, -depth + 2 * depth * i, stepHeight - 2 * stepHeight * i);
		glVertex3f(-width, -depth + 2 * depth * i, -stepHeight - 2 * stepHeight * i);

		glEnd();
		glLoadIdentity();
	}
}

void display()
{
	drawStairs();
	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

// Get user input and validate it
void getInput(std::string msg, double &param)
{
	bool valid = false;
	std::string input;
	std::regex floatNumber("[+]?([0-9]*[.])?[0-9]+");
	do
	{
		std::cout << msg;
		std::cin >> input;
		if (std::regex_match(input, floatNumber))
		{
			param = stof(input);
			valid = true;
		}
		else
		{
			std::cout << "Wrong input, should be a positive number!\n";
			std::cout << msg;
		}
	} while (!valid);
}

int main(int argc, char** argv)
{
	// Get user input through the console line
	getInput("Enter width of step: ", width);
	getInput("Enter depth of step: ", depth);
	getInput("Enter height of step: ", stepHeight);
	getInput("Enter full stair height: ", fullHeight);
	
	// Initialize windows
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Stairs");

	// Show drawing
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutReshapeFunc(reshape);
	initGL();
	glutMainLoop();
	return 0;
}