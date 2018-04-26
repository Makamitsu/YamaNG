#pragma once

#include <string>
#include <assimp\material.h>
#include "glm\glm.hpp"

class Material {


public:
	std::string m_Name;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	glm::vec3 m_Ambient;
	glm::vec3 m_Emissive;
	glm::vec3 m_Transparente;
	int m_Wireframe;
	int m_Twosided;
	aiShadingMode m_ShadingModel;
	aiBlendMode m_BlendFunc;
	float m_Opacity;
	float m_Shininess;
	float m_Refreacti;
//	std::string m_Texture;
//	float m_TextureBlend;
//	aiTextureOp m_TextureOperator;
//	int m_UVMapping;
//	aiTextureMapMode m_UMappingMode;
//	aiTextureMapMode m_VMappingMode;
//	glm::vec3 m_TextureMapAxis;
//	aiTextureFlags m_TextureFlag;

	Material(const aiMaterial& mat);
private:



};