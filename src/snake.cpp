#include "snake.h"

namespace {
	struct Point {
		int y, x;
	};

	//���������� ������� �������� � ����� END
	Point end[34]{ {9,5}, {9,6}, {9,7}, {9,9}, {9,12}, {9,14}, {9,15}, {9,16}, 
		{13,5}, {13,6}, {13,7}, {13,9}, {13,12}, {13,14}, {13,15}, {13,16}, 
		{10, 5}, {10, 9}, {10, 12}, {10, 14}, {10, 17},
		{11, 5}, {11, 6}, {11, 9}, {11, 11}, {11, 12}, {11, 14}, {11, 17},
		{12, 5}, {12, 9}, {12, 10}, {12, 12}, {12, 14}, {12, 17} };
}


Snake* Snake::instance = nullptr;

void Snake::ShowFruit() { //fruit
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1,0,0);
		glVertex2f(0.3f, 0.3f);
		glVertex2f(0.3f, 0.7f);
		glVertex2f(0.7f, 0.7f);
		glVertex2f(0.7f, 0.3f);
	glEnd();
}

void Snake::ShowSnake0() { //snake 0

	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 1, 0);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, 0.9f);
		glVertex2f(0.9f, 0.9f);
		glVertex2f(0.9f, 0.1f);
	glEnd();

}

void Snake::ShowSnake() { //snake o
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 0.8, 0);
		glVertex2f(0.2f, 0.2f);
		glVertex2f(0.2f, 0.8f);
		glVertex2f(0.8f, 0.8f);
		glVertex2f(0.8f, 0.2f);
	glEnd();

}

void Snake::ShowField() { //��� 
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.8f, 0.8f, 0.8f); glVertex2f(0, 1);
		glColor3f(0.7f, 0.7f, 0.7f); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.6f, 0.6f, 0.6f); glVertex2f(1, 0);
	glEnd();
}

Snake::Snake()
{
	instance = this;
}

void Snake::ShowBorder() { //�������
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(0, 1);
		glColor3f(0.1f, 0.1f, 0.1f); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.2f, 0.2f, 0.2f); glVertex2f(1, 0);
	glEnd();
}

void Snake::ShowEnd() {
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0, 1);
		glColor3f(0.9f, 0.0f, 0.0f); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.8f, 0.0f, 0.0f); glVertex2f(1, 0);
	glEnd();
}

void Snake::Setup()
{
	game = true;
	dir = stop; //�����������
	width = 21;
	height = 21;
	x = width / 2 + 1;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	points = 0; //����
	ntail = 0;

	if (!glfwInit())
		game = false;
}

void Snake::Fruit()
{
	fruitX = rand() % width;
	fruitY = rand() % height;

	if (fruitX == x && fruitY == y) Fruit();
	else for (int i = 0; i < ntail; i++) {
		if (tailX[i] == fruitX && tailY[i] == fruitY) Fruit();
	}
}

void Snake::Draw() {

	/* Set clear color to green */
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	/* Clear the screen */
	glClear(GL_COLOR_BUFFER_BIT);

	//������� ���������� ����� �����

	glLoadIdentity();
	glScaled(2.0 / (width + 2), 2.0 / (height + 2), 1);
	glTranslatef(-(width + 2) * 0.5, -(height + 2) * 0.5, 0);

	//������ �������
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef(i, 0, 0);
		ShowBorder();
		glPopMatrix();
	}

	//����
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width + 2; i++) {
			glPushMatrix();
			glTranslatef(i, j + 1, 0);


			if (i == 0 || i == width + 1)
				ShowBorder();
			else if (j == y && i == x) {
				ShowField();
				ShowSnake0();
			}
			else if (j == fruitY && i == fruitX) {
				ShowField();
				ShowFruit();
			}
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {
					if (tailY[k] == j && tailX[k] == i) {
						ShowField();
						ShowSnake();
						print = true;
					}
				}
				if (!print)
					ShowField();
			}
			glPopMatrix();
		}
	}

	//������� �������
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef(i, height + 1, 0);
		ShowBorder();
		glPopMatrix();
	}

}



void Snake::Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case left:
		x--;
		break;
	case right:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	default:
		break;
	}

	//���� ����� � �������
	if (x < 1 || x > width || y < 0 || y > height - 1) {
		game = false;
	}

	//���� ����� � ����
	for (int i = 0; i < ntail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			game = false;
	}

	//���� ����� � �����
	if (fruitX == x && fruitY == y) {
		points += 10;
		ntail++;
		Fruit();
	}
}


void Snake::End() {

	/* Set clear color to green */
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	/* Clear the screen */
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glScaled(2.0 / (width + 2), 2.0 / (height + 2), 1);
	glTranslatef(-(width + 2) * 0.5, -(height + 2) * 0.5, 0);

	//������ �������
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef(i, 0, 0);
		ShowBorder();
		glPopMatrix();
	}

	//����
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width + 2; i++) {
			glPushMatrix();
			glTranslatef(i, j + 1, 0);


			if (i == 0 || i == width + 1)
				ShowBorder();
			else {
				bool flag = true;
				for (int k = 0; k < 34; k++) { // 34 - ���-�� �����
					if (end[k].x == i && end[k].y == j + 1) {
						ShowEnd();
						flag = false;
					}
				}
				if (flag) ShowField();
			}
			glPopMatrix();
		}
	}

	//������� �������
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef(i, height + 1, 0);
		ShowBorder();
		glPopMatrix();
	}

}

void Snake::SetInputDirection(sides direction)
{
	dir = direction;
}
