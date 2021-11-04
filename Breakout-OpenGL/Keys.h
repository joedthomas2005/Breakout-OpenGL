#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
bool keys[6] = { false };

class Keys 
{
	public:
		Keys(GLFWwindow* window);
		enum KeyCode {
			RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3, SPACE = 4, ESCAPE = 5
		};
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		bool isKeyDown(KeyCode key);

		unsigned int gamePadPresent = 0;
		int gamePadAxisCount = 0;
		int gamePadButtonCount = 0;
		float leftJSlastValue = 0;
		void checkGamePadInput();
};

Keys::Keys(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
	
};



void Keys::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_RIGHT:
		keys[RIGHT] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[RIGHT];
		break;
	case GLFW_KEY_LEFT:
		keys[LEFT] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[LEFT];
		break;
	case GLFW_KEY_UP:
		keys[UP] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[UP];
		break;
	case GLFW_KEY_DOWN:
		keys[DOWN] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[DOWN];
		break;
	case GLFW_KEY_SPACE:
		keys[SPACE] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[SPACE];
		break;
	case GLFW_KEY_ESCAPE:
		keys[ESCAPE] = action == GLFW_PRESS ? true : action == GLFW_RELEASE ? false : keys[ESCAPE];
		break;
	};
};

void Keys::checkGamePadInput() {
	gamePadPresent = glfwJoystickPresent(GLFW_JOYSTICK_2);
	
	if (gamePadPresent) {
		////std::cout << "GAMEPAD CONNECTED NAME " << glfwGetJoystickName(GLFW_JOYSTICK_2) << std::endl;
		
		const float* axisValues = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &gamePadAxisCount);
		//std::cout << "LAST AXIS VALUE " << leftJSlastValue << " CURRENT AXIS VALUE " << axisValues[0] << std::endl;
		
		if (axisValues[0] > 0.2f && !(leftJSlastValue > 0.2f)) {
			//std::cout << "RIGHT PRESSED" << std::endl;
			keys[RIGHT] = true;
		}

		else if (leftJSlastValue > 0.2f && !(axisValues[0] > 0.2f)) {
			//std::cout << "RIGHT RELEASED" << std::endl;
			keys[RIGHT] = false; 
		}


		if (axisValues[0] < -0.2f && !(leftJSlastValue < -0.2f)) {
			//std::cout << "LEFT PRESSED" << std::endl;
			keys[LEFT] = true;
		}
		else if (leftJSlastValue < -0.2f && !(axisValues[0] < -0.2f)) {
			//std::cout << "LEFT RELEASED" << std::endl;
			keys[LEFT] = false;
		}

		leftJSlastValue = axisValues[0];
		const unsigned char* buttonValues = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &gamePadButtonCount);

		if (buttonValues[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS) {
			keys[SPACE] = true;
		}
		else if (buttonValues[GLFW_GAMEPAD_BUTTON_A] == GLFW_RELEASE) {
			keys[SPACE] = false;
		}
	}
}
bool Keys::isKeyDown(KeyCode key) {
	return keys[key];
};




