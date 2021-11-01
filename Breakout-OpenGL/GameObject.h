class GameObject {
protected:
	float y = 0;
	float x = 0;
//	float* vertices = NULL;
//	int* indices = NULL; 

public:
	int type;
//	int numVerts;
//	int numIndicies;
	bool isActive = true;
	GameObject(float x, float y);
	~GameObject();
	virtual void update(ShaderMan shader);
	float getX();
	float getY();
};


GameObject::GameObject(float x, float y) {
	this->x = x;
	this->y = y;
//	this->numVerts = numVerts;
//	this->numIndicies = numIndices;
//	this->vertices = new float[numVerts];
//	this->indices = new int[numIndices];
}

GameObject::~GameObject() {
//	delete[] vertices;
//	delete[] indices;
}

float GameObject::getX() {
	return x;
}
float GameObject::getY() {
	return y;
}
void GameObject::update(ShaderMan shader) {};