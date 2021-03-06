#pragma once

#include <string>
#include <unordered_map>

#include "glm\glm.hpp"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {

private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void setUniformMat4f(const std::string& name, const glm::mat4& mat);
	void setUniform1i(const std::string& name, int val);

private:

	ShaderProgramSource parseShader(std::string filePath);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& source);

	int getUniformLocation(const std::string& name);


};