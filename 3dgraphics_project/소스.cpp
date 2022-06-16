#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#define width 600
#define height 800

#define	PI 3.1415
#define	polygon_num 50

class Point {
public:
	float x;
	float y;

	Point(float a, float b) {
		this->x = a;
		this->y = b;
	}

	Point() {
		this->x = 0;
		this->y = 0;
	}
};

int ball_radius = 30.0;
int big_ball_radius = 70.0;
int ball_speed = 0.5;


float a = 0.05;

int ball_x(0), ball_y(0);
Point ball(300, 200);
bool move = false;

bool back = false;

float velocity = 0.05;
float plus = 0.05;

void draw_ball() {
	double delta;

	delta = 2 * PI / polygon_num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(ball.x + ball_radius * cos(delta * i), ball.y + ball_radius * sin(delta * i));
	glEnd();
}

void draw_big_ball() {
	double delta;

	Point big_ball(300, 500);

	delta = 2 * PI / polygon_num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(big_ball.x + big_ball_radius * cos(delta * i), big_ball.y + big_ball_radius * sin(delta * i));
	glEnd();
}

void draw_rectangle() {
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.3, 0.7);
	glVertex2f(250, 100);
	glVertex2f(250, 170);
	glVertex2f(350, 170);
	glVertex2f(350, 100);
	glEnd();
}

void rendering(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glColor3f(1.0, 0.5, 0.7);

	draw_ball();

	if (move) {
		ball.y += velocity;
		velocity += plus;
		//printf("%lf %lf %d\n", ball.x, ball.y, move);
		if (ball.y >= 510 - big_ball_radius - ball_radius) {
			// ball.y = 200;
			a += 0.05;
			move = false;
			back = true;

			velocity = 0.1;
		}
	}

	if (back) {
		ball.y -= velocity;
		velocity += plus;
		//printf("%lf %lf %d\n", ball.x, ball.y, back);
		if (ball.y <= 200) {
			ball.y = 200;
			back = false;

			velocity = 0.1;
		}
	}

	draw_rectangle();

	glColor3f(a, a, a);
	if (a >= 1) {
		printf("¼º°ø!\n");
		glClearColor(0, 0, 0, 0);
	}
	draw_big_ball();

	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
}

void SpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		move = true;
		break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("To The Light");

	glutReshapeFunc(reshape);
	glutDisplayFunc(rendering);
	glutIdleFunc(rendering);
	glutSpecialFunc(SpecialKey);
	glutMainLoop();
}