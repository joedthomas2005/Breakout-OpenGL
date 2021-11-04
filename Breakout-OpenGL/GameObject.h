class GameObject {
protected:
	float y = 0;
	float x = 0;
	bool isActive = true;


public:
	int type;

	bool getActive();
	void setActive(bool active);
	GameObject(float x, float y);
	~GameObject();
	virtual void update(ShaderMan shader);
	float getX();
	float getY();
	void move(float x, float y);
};


GameObject::GameObject(float x, float y) {
	this->x = x;
	this->y = y;

}

GameObject::~GameObject() {

}

float GameObject::getX() {
	return x;
}
float GameObject::getY() {
	return y;
}

bool GameObject::getActive() {
	return isActive;
}

void GameObject::setActive(bool active) {
	isActive = active;
}


void GameObject::move(float x, float y) {
	this->x += x;
	this->y += y;
}
void GameObject::update(ShaderMan shader) {};