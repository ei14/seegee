#include "seegee.hpp"
using namespace SeeGee;

int main() {
	vec3 black = vec3(0);
	vec3 white = vec3(1);

	open(500, 500, "SeeGee Test");

	while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS
		&& glfwWindowShouldClose(window) == 0
	) {
		clear(black);
		line(vec2(0, 0), vec2(0, 500), white);
		line(vec2(0, 500), vec2(500, 500), white);
		line(vec2(500, 500), vec2(500, 0), white);
		line(vec2(500, 0), vec2(0, 0), white);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
