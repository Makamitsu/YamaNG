#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string & filepath):m_FilePath(filepath)
{
	ShaderProgramSource source = parseShader(filepath);
	m_RendererID = createShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	bind();
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string & name, int val)
{
	bind();
	GLCall(glUniform1i(getUniformLocation(name), val));
}

int Shader::getUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << " doesn't exist!\n";
	}
	else {
		m_UniformLocationCache[name] = location;

	}
	return location;
}

ShaderProgramSource Shader::parseShader(std::string filePath) {
	std::ifstream stream(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GLCall(unsigned int program = glCreateProgram());

	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int vf = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, vf));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(vf));

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* log = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, log));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << ":\n";
		std::cout << log << "\n";
		GLCall(glDeleteShader(id));
		return 0;
	}
	return id;
}


