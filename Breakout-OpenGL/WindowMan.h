#pragma once
class Window
{
	private:
		GLFWwindow* window;
		int * pWidth;
		int * pHeight;
		static void callbackError(int error, const char* description) {
			std::cerr << "Error: " << description;
		}
		static void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
			glViewport(0, 0, width, height);
		}

	public:
		Window(int width, int height, const char* title, GLFWkeyfun key_callback, int swap_interval) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwSetErrorCallback(callbackError);
			this->window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (this->window == NULL) {
				exit(-1);
			}
			glfwSetKeyCallback(window, key_callback);
			glfwMakeContextCurrent(window);
			glfwSwapInterval(swap_interval);
			pWidth = new int;
			pHeight = new int;
			glfwGetFramebufferSize(window, pWidth, pHeight);
			glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
		}
		void initViewport() {
			glViewport(0, 0, *pWidth, *pHeight);
		}
		void setSwapInterval(int interval) {
			glfwSwapInterval(interval);
		}
		bool shouldClose() {
			return glfwWindowShouldClose(window);
		}
		GLFWwindow* getWindow() {
			return window;
		}
		void update() {
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		void destroy() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		
};
