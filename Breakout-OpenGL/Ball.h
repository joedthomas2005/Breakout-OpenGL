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
	int maxBalls;
	int maxBricks;
public:

	float getRadius();;
	Ball(float x, float y, float radius, float startingAngle, float speed, GameObject** objects, int maxBalls, int maxBricks, bool* deleted);
	~Ball();
	void update(ShaderMan shader);
	
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
		if (objects[i]->type == 1) {
			Player* player = (Player*) objects[i];
			if (y - radius <= player->getY() + player->getHeight() / 2 && (x < player->getX() + player->getWidth() / 2 && x > player->getX() - player->getWidth() / 2)) {
				yMult = 0 - yMult;
				y += player->getY() + player->getHeight() - (y - radius);

			}
		}
	}
	x += speed * coses[(int)angle] * xMult;
	y += speed * sins[(int)angle] * yMult;
	shader.setVec3f("transform", x, y);
}
