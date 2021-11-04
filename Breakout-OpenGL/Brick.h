#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Brick : public GameObject	{
	private: 
		float width;
		float height;
	public: 
		Brick(float x, float y, float width, float height);
		void update(ShaderMan shader);
		float getWidth();
		float getHeight();
};

Brick::Brick(float x, float y, float width, float height) : GameObject(x, y) {
	this->width = width;
	this->height = height;
	type = 2;
}

void Brick::update(ShaderMan shader) {
	shader.setVec3f("transform", x, y);
}

float Brick::getWidth() {
	return width;
}
float Brick::getHeight() {
	return height;
}