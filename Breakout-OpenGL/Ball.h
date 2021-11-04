#pragma once
#include<cmath>
const double PI = atan(1) * 4;
float sins[361] = {};
float coses[361] = {};
int* ballIndices;
int ballIndicesLength;
int ballVertLength;

class Ball : public GameObject{
private:
	float radius;
	float angle;
	float speed;
	int xMult;
	int yMult;
	GameObject** objects;
	bool* deleted;
	int maxBalls;
	int maxBricks;
public:

	float getRadius();;
	Ball(float x, float y, float radius, float startingAngle, float speed, GameObject** objects, int maxBalls, int maxBricks, bool* deleted);
	void update(ShaderMan shader);
	~Ball();
	
};

Ball::~Ball() {
	
}

float Ball::getRadius() {
	return radius;
}

Ball::Ball(float x, float y, float radius, float startingAngle, float speed, GameObject** objects, int maxBalls, int maxBricks, bool* deleted) : GameObject(x,y){
	type = 0;
	this->angle = startingAngle;
	this->objects = objects;
	this->xMult = 1;
	this->yMult = 1;
	this->speed = speed;
	this->radius = radius;
	this->maxBalls = maxBalls;
	this->maxBricks = maxBricks;
	this->deleted = deleted;
	
};


void Ball::update(ShaderMan shader) {
	
	if (x + radius>= 1.0f || x - radius <= -1.0f) {
		xMult = 0 - xMult;
	}
	if (y + radius >= 1.0f) {
		yMult = 0 - yMult;
	}
	else if (y - radius <= -1.0f) {
		isActive = false;
	}

	for (int i = 0; i < maxBricks + maxBalls + 1; i++) {
		////std::cout << "CHECKING INDEX " << i << std::endl;
		if (!deleted[i]) {
			if (objects[i]->type == 1) {   //TYPE 1 = PLAYER
				////std::cout << "CHECKING PLAYER COLLISION" << std::endl;
				Player* player = (Player*)objects[i];
				if (y - radius <= player->getY() + player->getHeight() / 2 && (x < player->getX() + player->getWidth() / 2 && x > player->getX() - player->getWidth() / 2)) {
					yMult = 0 - yMult;
					y += player->getY() + player->getHeight() - (y - radius);

				}
				//delete player;
			}

			else if (objects[i]->type == 2) {	//TYPE 2 = BRICK
				Brick* brick = (Brick*)objects[i];
				float brickLeft = brick->getX() - brick->getWidth() / 2;
				float brickRight = brick->getX() + brick->getWidth() / 2;
				float brickTop = brick->getY() + brick->getHeight() / 2;
				float brickBottom = brick->getY() - brick->getHeight() / 2;

				float ballLeft = x - radius;
				float ballRight = x + radius;
				float ballTop = y + radius;
				float ballBottom = y - radius;
				bool collisionCalculated = false;
				if (((brickLeft < ballRight && ballRight < brickRight) || 
					(brickLeft < ballLeft && ballLeft < brickRight)) &&
					((brickBottom < ballTop && ballTop < brickTop) ||
					(brickBottom < ballBottom && ballBottom < brickTop)))
				{
					std::cout << "BALL HIT BRICK" << std::endl;
					if (y - radius < brick->getY() - brick->getHeight() / 2) {
						yMult = 0 - abs(yMult);
						collisionCalculated = true;
					}
					else {
						yMult = abs(yMult);
						collisionCalculated = true;
					}
					
					if (!collisionCalculated) {
						if (x - radius < brick->getX() - brick->getWidth() / 2) {
							xMult = 0 - abs(xMult);
							collisionCalculated = true;
						}
						else {
							xMult = abs(xMult);
							collisionCalculated = true;
						}
					}
					brick->setActive(false);
				}
			}

			else if (objects[i]->type == 0) {	//TYPE 0 = BALL
				if (objects[i] != this) {
					//std::cout << "CHECKING BALL COLLISION" << std::endl;
					if (sqrt(pow(objects[i]->getX() - x, 2) + pow(objects[i]->getY() - y, 2)) < radius * 2) {
						xMult = 0 - xMult;
						yMult = 0 - yMult;
					}
				}
			}
		}
	}
	x += speed * coses[(int)angle] * xMult;
	y += speed * sins[(int)angle] * yMult;
	shader.setVec3f("transform", x, y);
}
