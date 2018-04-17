#include <GLFW\glfw3.h>


#include <iostream>


#include "src\graphics\window.h"

int main() {

	using namespace yama::graphics;

	Window window("YamaEngine", 800, 600);

	glClearColor(0.2f,0.2f,1.0f,1.0f);



	while (!window.closed() ) {

		window.clear();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();


		window.update();
	}

}