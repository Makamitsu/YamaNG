#pragma once

#include <GL/glew.h>

class Mesh;
class Model;
class VertexArray;
class Shader;
class IndexBuffer;


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:

public:
	void clear()const;
	void draw(const VertexArray& va, const IndexBuffer& ib, Shader& Shader) const;
	
	void draw(Mesh& mesh, Shader& Shader) const;
	void draw(Model& model, Shader& Shader) const;

};