// Copyright (c) 2022 Thomas Kaldahl 

#ifndef SEEGEE_HPP
#define SEEGEE_HPP

#include <vector>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace SeeGee {
	using glm::mat4;
	using glm::vec2;
	using glm::vec3;

	extern GLuint placeShader;
	extern const char *PLACE_SRC;
	extern GLuint colorShader;
	extern const char *COLOR_SRC;

	extern GLuint prog;

	extern GLFWwindow *window;

	extern mat4 mvp;
	extern GLuint mvpUni;

	extern vec3 color;

	extern void open(int width, int height, const char *title);
	extern void close();

	extern void clear(vec3 color);

	extern void line(vec2 start, vec2 end);
	extern void line(vec2 start, vec2 end, vec3 color);
}

#endif
