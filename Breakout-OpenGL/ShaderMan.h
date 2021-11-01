#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<string>
#include<vector>

class ShaderMan {
public:
	unsigned int ID;

	ShaderMan(const char* vertShaderPath, const char* fragShaderPath);

	void use();

	void setVec3f(const std::string& name, float x, float y) const;

};

ShaderMan::ShaderMan(const char* vertShaderPath, const char* fragShaderPath) {
	//loading shader files
	std::ifstream fileStream;

	std::string vertShaderString;
	std::string fragShaderString;
	fileStream.open(vertShaderPath);
	vertShaderString = std::string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
	fileStream.close();
	fileStream.open(fragShaderPath);
	fragShaderString = std::string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
	fileStream.close();
	const char* vertShaderSource = vertShaderString.c_str();
	const char* fragShaderSource = fragShaderString.c_str();

	//generating and compiling shaders
	unsigned int vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vertShaderSource, NULL);
	glShaderSource(fShader, 1, &fragShaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "ERROR SHADER VERTEX COMPILATION FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 512, NULL, infoLog);
		std::cout << "ERROR SHADER FRAGMENT COMPILATION FAILED\n" << infoLog << std::endl;
	}
	//create program and attach program
	ID = glCreateProgram();
	glAttachShader(ID, vShader);
	glAttachShader(ID, fShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR SHADING LINKING FAILED\n" << infoLog << std::endl;
	}
	//delete shaders

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void ShaderMan::use() {
	glUseProgram(ID);
}

void ShaderMan::setVec3f(const std::string& name, float x, float y) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, 0.0);
}