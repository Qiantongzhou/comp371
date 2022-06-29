#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

unsigned int VBO = 0;
unsigned int shaderProgram = 0;
void rend() {

}
void initMode() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//GPU 内存
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//内存起始位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void intShader(const char* _vertexPath,const char* _fragPath) {
	string _VertexCode("");
	string _fragCode("");
	ifstream _vFile;
	ifstream _fFile;
	try {
		_vFile.open(_vertexPath);
		_fFile.open(_fragPath);

		stringstream _vstream, _fstream;
		_vstream << _vFile.rdbuf();
		_fstream << _fFile.rdbuf();
		_VertexCode = _vstream.str();
		_fragCode = _fstream.str();

	}
	catch(ifstream::failure e) {
		string err = "read shader fail";
		cout << err << endl;

	}
	const char* _vstr = _VertexCode.c_str();
	const char* _fstr = _fragCode.c_str();

	unsigned int _vertexID = 0, _fragID = 0;
	char _infoLog[512];
	int _successFlag = 0;
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexID, 1, &_vstr, NULL);
	glCompileShader(_vertexID);
	glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag) {
		glGetShaderInfoLog(_vertexID,512,NULL,_infoLog);
		string err(_infoLog);
		cout << err << endl;

	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "comp371-tuxing", NULL, NULL);
	if (window == NULL) {
		cout << "FAIL" << endl;
		glfwTerminate();
		return -1;

	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "fail" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initMode();
	intShader("vertexShader.glsl", "fragmentShader.glsl");



	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate;
	return 0;
}