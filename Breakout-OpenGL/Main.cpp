#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Keys.h"
#include "WindowMan.h"
#include "ShaderMan.h"
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"

float* genCircleVertices(float radius, int vertArrayLength, float color[3]);
float* genPlayerVertices(int vertArrayLength, float width, float height, float color[3]);

int main(void)
{
	playerIndices = new int[6]{ 0,1,3,1,2,3 };
	playerIndicesLength = 6;
	playerVertLength = 24;

	ballIndices = new int[108]
	{ 0,1,2,
	0,2,3,
	0,3,4,
	0,4,5,
	0,5,6,
	0,6,7,
	0,7,8,
	0,8,9,
	0,9,10,
	0,10,11,
	0,11,12,
	0,12,13,
	0,13,14,
	0,14,15,
	0,15,16,
	0,16,17,
	0,17,18,
	0,18,19,
	0,19,20,
	0,20,21,
	0,21,22,
	0,22,23,
	0,23,24,
	0,24,25,
	0,25,26,
	0,26,27,
	0,27,28,
	0,28,29,
	0,29,30,
	0,30,31,
	0,31,32,
	0,32,33,
	0,33,34,
	0,34,35,
	0,35,36,
	0,36,1 };

	ballIndicesLength = 108;
	ballVertLength = 222;
	
	float playerInitLocation[3] = { 0.0f, -0.9f, 0.0f };
	float playerColor[3] = { 1.0f,0.0f,0.0f };
	float ballInitLocation[3] = { 0.0f, -0.8f, 0.0f };
	float ballColor[3] = { 0.0f, 1.0f, 1.0f };

	const float PLAYERWIDTH = 0.3f;
	const float PLAYERHEIGHT = 0.05f;
	const float BALLRADIUS = 0.03f;

	float* ballVertices = genCircleVertices(BALLRADIUS, ballVertLength, ballColor);
	float* playerVertices = genPlayerVertices(playerVertLength, PLAYERWIDTH, PLAYERHEIGHT, playerColor);

	int numBalls = 0;
	int numBlocks = 0;

	for (int i = 0; i <= 360; i++) {
		sins[i] = sin(i * PI / 180);
		coses[i] = cos(i * PI / 180);
	}
	if (!glfwInit()) {
		return -1;
	}

	gladLoadGL();
	Window window = Window(900, 800, "Game", NULL, 1);

	Keys* input = new Keys(window.getWindow());



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	window.initViewport();

	ShaderMan shadingBlokeInMyComputer = ShaderMan("Shaders/vert.hlsl", "Shaders/fragShader.hlsl");

	const int maxBalls = 10;

	GameObject* objects[1 + maxBalls] = {};


	objects[0] = new Player(0.5f, -0.9f , playerColor, PLAYERWIDTH, PLAYERHEIGHT, input);
	//objects[1] = new Ball(ballInitLocation, ballColor, BALLRADIUS, 45, 0.03f, (Player*)objects[0]);
	//numBalls++;


	//int objectindex = 2;
	bool* deleted = new bool[1 + maxBalls];
	for (int i = 1; i <= maxBalls; i++) {
		deleted[i] = false;
	}



	float* vertices = new float[playerVertLength + maxBalls * ballVertLength];
	int* indices = new int[playerIndicesLength + maxBalls * ballIndicesLength];

	int objectVertIndex = 0;
	int objectIndicesIndex = 0;

	for (int i = 0; i < playerVertLength; i++) {
		vertices[i] = playerVertices[i];
	}

	for (int i = 0; i < maxBalls; i++) {
		for (int j = 0; j < ballVertLength; j++) {
			//std::cout << "WRITING VERTEX " << objects[1]->getVertices()[j] << " AT INDEX " << playerVertLength + i * ballVertLength + j << std::endl;
			vertices[playerVertLength + i * ballVertLength + j] = ballVertices[j];
		}
	}

	for (int i = 0; i < playerIndicesLength; i++) {
		indices[i] = playerIndices[i];
	}

	for (int i = 0; i < maxBalls; i++) {
		for (int j = 0; j < ballIndicesLength; j++) {
			//std::cout << "WRITING VALUE " << ballIndices[j] + ballVertLength / 6 * i + playerVertLength / 6 << " TO INDICES INDEX " << playerIndicesLength + i * ballIndicesLength + j << std::endl;
			indices[playerIndicesLength + i * ballIndicesLength + j] = ballIndices[j] + ballVertLength / 6 * i + playerVertLength / 6;
		}
	}


	//std::cout << "SETUP DONE" << std::endl;



	unsigned int VBO, VAO, EBO;

	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (playerVertLength + maxBalls * ballVertLength), vertices, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (playerIndicesLength + maxBalls * ballIndicesLength), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	//std::cout << "BUFFERING DONE" << std::endl;


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	bool spacePressTimer[2] = {false, false};
	double fpsTimer[2] = { 0.0f, glfwGetTime() };
	while (!window.shouldClose()) {
		fpsTimer[0] = fpsTimer[1];
		fpsTimer[1] = glfwGetTime();
		//std::cout << "CURRENT PERFORMANCE " << fpsTimer[1] - fpsTimer[0] << " m/s per frame" << std::endl;
		if (input->isKeyDown(input->SPACE)) {
			spacePressTimer[0] = spacePressTimer[1];
			spacePressTimer[1] = true;
		}
		else {
			spacePressTimer[0] = spacePressTimer[1];
			spacePressTimer[1] = false;
		}

		if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
			input->checkGamePadInput();
		}

		if (spacePressTimer[1] && !spacePressTimer[0]) {
			//std::cout << "ATTEMPTING TO CREATE NEW BALL" << std::endl;
			if (numBalls < maxBalls) {
				for (int i = 1; i < maxBalls + 1; i++) {
					if (deleted[i] || objects[i] == nullptr) {
						objects[i] = new Ball(((Player*)objects[0])->getX(), ((Player*)objects[0])->getY()+0.1f, ballColor, BALLRADIUS, 45.0f, 0.03f, (Player*)objects[0]);
						numBalls++;
						deleted[i] = false;
						//std::cout << "SUCCESS! BALL CREATED" << std::endl;
						break;
					}
				}
			}
			else {
				//std::cout << "FAILED: MAX BALLS CREATED" << std::endl;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		shadingBlokeInMyComputer.use();
		glBindVertexArray(VAO);
		//std::cout << "VERTEX ARRAY BOUND" << std::endl;


			
		
		//std::cout << "DRAWING PLAYER" << std::endl;
		objects[0]->update(shadingBlokeInMyComputer);
		glDrawElements(GL_TRIANGLES, playerIndicesLength, GL_UNSIGNED_INT, (void*)0);


		//std::cout << "DRAWING BALLS" << std::endl;
		for (int i = 1; i < maxBalls+1; i++) {
			if (!deleted[i] && objects[i]!= nullptr) {
				if(objects[i]->isActive){
					objects[i]->update(shadingBlokeInMyComputer);
					//std::cout << "DRAWING BALL WITH INDICIAL OFFSET OF " << playerIndicesLength + i * ballIndicesLength << " AND " << ballIndicesLength << " INDICIES" << std::endl;
					glDrawElements(GL_TRIANGLES, ballIndicesLength, GL_UNSIGNED_INT, (void*)((playerIndicesLength + (i * (ballIndicesLength)))*sizeof(GLuint)));
				}
				else {
					deleted[i] = true;
					std::cout << "DELETED OBJECT AT " << objects[i] << " OF TYPE " << objects[i]->type << std::endl;
					delete objects[i];
					numBalls--;
				}
			} 
		}
		window.update();

	}
	window.destroy();
	return 0;
}






float* genCircleVertices(float radius, int vertArrayLength, float color[3]) {
	float* vertices = new float[vertArrayLength];
	float pointsOnCircle[36][2] = {};
	float angle = 0.0f;
	for (int i = 0; i < 36; i++) {
		angle += 10 * float(PI / 180);
		pointsOnCircle[i][0] = (float)(radius * cos(angle));
		pointsOnCircle[i][1] = (float)(radius * sin(angle));
	}

	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 1.0f;
	vertices[3] = color[0];
	vertices[4] = color[1];
	vertices[5] = color[2];

	for (int vert = 1; vert < 37; vert++) {
		for (int index = 0; index < 6; index++) {
			switch (index) {
			case 0:
				vertices[index + vert * 6] = pointsOnCircle[vert - 1][0];
				break;
			case 1:
				vertices[index + vert * 6] = pointsOnCircle[vert - 1][1];
				break;
			case 2:
				vertices[index + vert * 6] = 1.0f;
				break;
			case 3:
				vertices[index + vert * 6] = color[0];
				break;
			case 4:
				vertices[index + vert * 6] = color[1];
				break;
			case 5:
				vertices[index + vert * 6] = color[1];
				break;
			}
			//std::cout << vertices[index + vert * 6] << ',';

		}
		//std::cout << std::endl;
	}
	return vertices;
}


float* genPlayerVertices(int vertArrayLength, float width, float height, float color[3]) {
	float* vertices = new float[vertArrayLength];
	float blVert[3] = { 0 - width / 2.0f, 0 - height / 2.0f, 1.0f };
	float tlVert[3] = { 0 - width / 2.0f, 0 + height / 2.0f, 1.0f };
	float brVert[3] = { 0 + width / 2.0f, 0 - height / 2.0f, 1.0f };
	float trVert[3] = { 0 + width / 2.0f, 0 + height / 2.0f, 1.0f };
	//first vertex at 0
	//second vertex at 6
	//third vertex at 12
	//fourth vertex at 18
	//tr, br, bl, tl
	for (int i = 0; i < 3; i++) {
		vertices[i] = trVert[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 3] = color[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 6] = brVert[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 9] = color[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 12] = blVert[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 15] = color[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 18] = tlVert[i];
	}
	for (int i = 0; i < 3; i++) {
		vertices[i + 21] = color[i];
	}
	return vertices;
}