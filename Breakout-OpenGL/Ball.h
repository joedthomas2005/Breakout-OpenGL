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
	Player *pPlayer;
public:

	float getRadius();;
	Ball(float x, float y, float color[3], float radius, float startingAngle, float speed, Player* player);
	~Ball();
	void update(ShaderMan shader);
	
};

Ball::~Ball() {
	
}

float Ball::getRadius() {
	return radius;
}

Ball::Ball(float x, float y, float color[3], float radius, float startingAngle, float speed, Player *player) : GameObject(x,y){
	type = 0;
	this->angle = startingAngle;
	this->pPlayer = player;
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

	if (y - radius <= pPlayer->getY() + pPlayer->getHeight() / 2 && (x < pPlayer->getX() + pPlayer->getWidth() / 2 && x > pPlayer->getX() - pPlayer->getWidth() / 2)) {
		yMult = 0 - yMult;
		y += pPlayer->getY()+pPlayer->getHeight() - (y - radius);

	}
	x += speed * coses[(int)angle] * xMult;
	y += speed * sins[(int)angle] * yMult;
	shader.setVec3f("transform", x, y);
}
