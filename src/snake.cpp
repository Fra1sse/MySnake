#include "snake.h"

void Snake::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		
		switch (key) {
		case GLFW_KEY_A:
			Snake::instance->SetInputDirection(Snake::left);
			break;
		case GLFW_KEY_D:
			Snake::instance->SetInputDirection(Snake::right);
			break;
		case GLFW_KEY_W:
			Snake::instance->SetInputDirection(Snake::down);
			break;
		case GLFW_KEY_S:
			Snake::instance->SetInputDirection(Snake::up);
			break;
		}
	}
}


namespace {
	struct Point {
		int y, x;
	};

	//координаты красных пикселей в слове END
	Point end[34]{ {9,5}, {9,6}, {9,7}, {9,9}, {9,12}, {9,14}, {9,15}, {9,16}, 
		{13,5}, {13,6}, {13,7}, {13,9}, {13,12}, {13,14}, {13,15}, {13,16}, 
		{10, 5}, {10, 9}, {10, 12}, {10, 14}, {10, 17},
		{11, 5}, {11, 6}, {11, 9}, {11, 11}, {11, 12}, {11, 14}, {11, 17},
		{12, 5}, {12, 9}, {12, 10}, {12, 12}, {12, 14}, {12, 17} };
}


Snake* Snake::instance = nullptr;

void Snake::ShowFruit(ImVec4 Fruit_color) { //fruit
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(Fruit_color.x * Fruit_color.w, Fruit_color.y * Fruit_color.w, Fruit_color.z * Fruit_color.w, Fruit_color.w);
		glColor3f(1,0,0);
		glVertex2f(0.3f, 0.3f);
		glVertex2f(0.3f, 0.7f);
		glVertex2f(0.7f, 0.7f);
		glVertex2f(0.7f, 0.3f);
	glEnd();
}

void Snake::ShowSnake_0(ImVec4 Snake_color) { //snake 0

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, 0.9f);
		glVertex2f(0.9f, 0.9f);
		glVertex2f(0.9f, 0.1f);
	glEnd();

}

void Snake::ShowSnake_o(ImVec4 Snake_color) { //snake o
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
		glVertex2f(0.2f, 0.2f);
		glVertex2f(0.2f, 0.8f);
		glVertex2f(0.8f, 0.8f);
		glVertex2f(0.8f, 0.2f);
	glEnd();

}

void Snake::ShowField(ImVec4 Field_color) { //фон 
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f((Field_color.x * Field_color.w), (Field_color.y * Field_color.w), (Field_color.z * Field_color.w), Field_color.w);
		glVertex2f(0, 1);
	glColor4f((Field_color.x * Field_color.w) - 1, (Field_color.y * Field_color.w) - 1, (Field_color.z * Field_color.w) - 1, Field_color.w);
		glVertex2f(1, 1); glVertex2f(0, 0);
	glColor4f((Field_color.x * Field_color.w) - 2, (Field_color.y * Field_color.w) - 2, (Field_color.z * Field_color.w) - 2, Field_color.w);
		glVertex2f(1, 0);
	glEnd();
}

Snake::Snake()
{
	instance = this;
}

void Snake::ShowBorder(ImVec4 Border_color) { //граница
	glBegin(GL_TRIANGLE_STRIP);
	glColor4f((Border_color.x * Border_color.w), (Border_color.y * Border_color.w), (Border_color.z * Border_color.w), Border_color.w);
		glVertex2f(0, 1);
	glColor4f((Border_color.x * Border_color.w) + 1, (Border_color.y * Border_color.w) + 1, (Border_color.z * Border_color.w) + 1, Border_color.w);
		glVertex2f(1, 1); glVertex2f(0, 0);
	glColor4f((Border_color.x * Border_color.w) + 2, (Border_color.y * Border_color.w) + 2, (Border_color.z * Border_color.w) + 2, Border_color.w);
		glVertex2f(1, 0);
	glEnd();
}

void Snake::ShowEnd() {
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0, 1);
		glColor3f(0.9f, 0.0f, 0.0f); glVertex2f(1, 1); glVertex2f(0, 0);
		glColor3f(0.8f, 0.0f, 0.0f); glVertex2f(1, 0);
	glEnd();
}

void Snake::SetupSnake()
{
	game = true;
	dir = stop; //направление
	width = 21;
	height = 21;
	x = width / 2 + 1;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	points = 0; //очки
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

	//рисовка происходит снизу вверх

	glLoadIdentity();
	glScaled(2.0 / (width + 2), 2.0 / (height + 2), 1);
	glTranslatef(-((float)width + 2) * 0.5, -((float)height + 2) * 0.5, 0.0f);

	//нижняя граница
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef((float)i, 0.0f, 0.0f);
		ShowBorder(setup.Border_color);
		glPopMatrix();
	}

	//поле
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width + 2; i++) {
			glPushMatrix();
			glTranslatef((float)i, (float)j + 1, 0.0f);


			if (i == 0 || i == width + 1)
				ShowBorder(setup.Border_color);
			else if (j == y && i == x) {
				ShowField(setup.Field_color);
				ShowSnake_0(setup.Snake_color);
			}
			else if (j == fruitY && i == fruitX) {
				ShowField(setup.Field_color);
				ShowFruit(setup.Fruit_color);
			}
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {
					if (tailY[k] == j && tailX[k] == i) {
						ShowField(setup.Field_color);
						ShowSnake_o(setup.Snake_color);
						print = true;
					}
				}
				if (!print)
					ShowField(setup.Field_color);
			}
			glPopMatrix();
		}
	}

	//верхняя граница
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef((float)i, (float)height + 1, 0.0f);
		ShowBorder(setup.Border_color);
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

	//если попал в границу
	if (x < 1 || x > width || y < 0 || y > height - 1) {
		game = false;
	}

	//если попал в тело
	for (int i = 0; i < ntail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			game = false;
	}

	//если попал в фрукт
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
	glTranslatef(-((float)width + 2) * 0.5, -((float)height + 2) * 0.5, 0);

	//нижняя граница
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef((float)i, 0.0f, 0.0f);
		ShowBorder(setup.Border_color);
		glPopMatrix();
	}

	//поле
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width + 2; i++) {
			glPushMatrix();
			glTranslatef((float)i, (float)j + 1.0f, 0.0f);


			if (i == 0 || i == width + 1)
				ShowBorder(setup.Border_color);
			else {
				bool flag = true;
				for (int k = 0; k < 34; k++) { // 34 - кол-во точек
					if (end[k].x == i && end[k].y == j + 1) {
						ShowEnd();
						flag = false;
					}
				}
				if (flag) ShowField(setup.Field_color);
			}
			glPopMatrix();
		}
	}

	//верхняя граница
	for (int i = 0; i < width + 2; i++) {
		glPushMatrix();
		glTranslatef((float)i, (float)height + 1.0f, 0.0f);
		ShowBorder(setup.Border_color);
		glPopMatrix();
	}

}

void Snake::SetInputDirection(sides direction)
{
	dir = direction;
}


void Snake::GameBegin() {

	GLFWwindow* window;

	//SetupSnake();

	std::cout << setup.WidthWindow << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	/*window = glfwCreateWindow(setup.WidthWindow, setup.HeightWindow, "Snake", NULL, NULL);

	glfwSetKeyCallback(window, key_callback);

	if (!window)
	{
		glfwTerminate();
		return;
	}
	/*
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		/* Poll for and process events *//*
		glfwPollEvents();

		if (game.game) {
			game.Draw();
			game.Logic();
			Sleep(200);

			/* Swap front and back buffers *//*
			glfwSwapBuffers(window);

		}
		else {
			game.End();
			Sleep(200);
			glfwSwapBuffers(window);
		}
	}*/

}