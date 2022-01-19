// Copyright (c) 2022 Thomas Kaldahl 

#include "seegee.hpp"

namespace SeeGee {
	GLuint placeShader;
	GLuint colorShader;

	GLuint prog;

	GLFWwindow *window;

	mat4 mvp;
	GLuint mvpUni;

	vec3 color;

	const char *PLACE_SRC = R"(
		#version 330 core
		layout(location=0) in vec3 vertPos;
		uniform mat4 mvp;
		void main() {
			gl_Position = mvp * vec4(vertPos, 1.0f);
		}
	)";

	const char *COLOR_SRC = R"(
		#version 330 core
		uniform vec3 color;
		out vec3 colorOut;
		void main() {
			colorOut = color;
		}
	)";

	void checkShaderErr(GLuint shader) {
		int err;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &err);
		if(err) {
			int errLen;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errLen);

			std::vector<char> errMsg(errLen+1);
			glGetShaderInfoLog(shader, errLen, NULL, &errMsg[0]);
			fprintf(stderr, "%s\n", &errMsg[0]);
		}
	}
	
	// GENERAL METHODS
	void open(int width, int height, const char *title) {
		glewExperimental = true;
		if(!glfwInit()) {
			fprintf(stderr, "Failed to initialize GLFW\n");
			exit(-1);
		}
		glfwWindowHint(GLFW_SAMPLES, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		if(window == NULL) {
			fprintf(stderr, "Failed to open window\n");
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(window);

		if(glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			exit(-1);
		}
		
		prog = glCreateProgram();

		placeShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(placeShader, 1, &PLACE_SRC, NULL);
		glCompileShader(placeShader);
		checkShaderErr(placeShader);
		glAttachShader(prog, placeShader);

		colorShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(colorShader, 1, &COLOR_SRC, NULL);
		glCompileShader(colorShader);
		checkShaderErr(colorShader);
		glAttachShader(prog, colorShader);

		glLinkProgram(prog);

		glDetachShader(prog, placeShader);
		glDetachShader(prog, colorShader);

		mvp = mat4(
			2.0f / width, 0, 0, 0,
			0, -2.0f / height, 0, 0,
			0, 0, 1.0f, 0,
			-1.0f, 1.0f, 0, 1.0f
		);
		mvpUni = glGetUniformLocation(prog, "mvp");
	}

	void close() {
		glDisableVertexAttribArray(0);
		glfwDestroyWindow(window);
	}

	// GRAPHICS METHODS
	void clear(vec3 color) {
		glClearColor(color.x, color.y, color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void line(vec2 start, vec2 end, vec3 color) {
		// VERTICES
		const GLfloat verts[] = {
			start.x, start.y, 0.0f,
			end.x, end.y, 0.0f,
		};

		// VAO
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// VBO
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		// ATTRIBUTES
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// USE PROGRAM
		glUseProgram(prog);

		// PASS DATA
		GLuint colorUni = glGetUniformLocation(prog, "color");

		glUniformMatrix4fv(mvpUni, 1, GL_FALSE, &mvp[0][0]);
		glUniform3fv(colorUni, 1, &color[0]);

		// DRAW
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 2);

		// FREE
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	// INPUTS METHODS
	int shouldClose() { return glfwWindowShouldClose(window); }
	int getKey(int key) { return glfwGetKey(window, key); }
}
