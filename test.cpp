#include "seegee.hpp"
using namespace SeeGee;

int main() {
	vec3 black = vec3(0);
	vec3 white = vec3(1);

	open(600, 600, "SeeGee Test");

	while(!getKey(KEY_ESCAPE) && !getKey(KEY_Q) && !shouldClose()) {
		clear(black);
		line(vec2(0, 0), vec2(0, 600), white);
		line(vec2(0, 600), vec2(600, 600), white);
		line(vec2(600, 600), vec2(600, 0), white);
		line(vec2(600, 0), vec2(0, 0), white);

		draw();
		pollEvents();
	}
}
