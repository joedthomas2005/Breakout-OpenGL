#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int* playerIndices;
int playerIndicesLength;
int playerVertLength;
class Player : public GameObject{
	private:
		Keys* KeyBoardIO;
		float width;
		float height;
	public:
		float getWidth();
		float getHeight();
		void move(float x, float y);
		Player(float x, float y, float color[3], float width, float height, Keys *KeyBoardIO);
		~Player();
		void update(ShaderMan shader);
};

Player::~Player() {
	
}
void Player::move(float x, float y) {
	this->x += x;
	this->y += y;
};

Player::Player(float x, float y, float color[3], float width, float height, Keys *KeyBoardIO) : GameObject(x, y){
	type = 1;
	for (int i = 0; i < playerIndicesLength; i++) {
		//indices[i] = playerIndices[i];
	}
	this->width = width;
	this->height = height;
	this->KeyBoardIO = KeyBoardIO;
}

void Player::update(ShaderMan shader) {
	//std::cout << KeyBoardIO.isKeyDown(KeyBoardIO.LEFT_ARROW) << KeyBoardIO.isKeyDown(KeyBoardIO.RIGHT_ARROW) << " ";

	if (KeyBoardIO->isKeyDown(KeyBoardIO->RIGHT) && x + width/2 < 1.0f) {
		move(0.05f, 0.0f);
	}

	if (KeyBoardIO->isKeyDown(KeyBoardIO->LEFT) && x - width/2 > -1.0f) {
		move(-0.05f, 0.0f);
	}
	shader.setVec3f("transform", x, y);
}

float Player::getHeight() {
	return height;
}
float Player::getWidth() {
	return width;
}
