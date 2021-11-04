#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Brick : public GameObject	{
	private: 
		float width;
		float height;
	public: 
		Brick(float x, float y, float width, float height);
};

Brick::Brick(float x, float y, float width, float height) : GameObject(x, y) {
	this->width = width;
	this->height = height;
	type = 2;
}