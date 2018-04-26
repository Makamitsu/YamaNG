#pragma once

#include <vector>

#include "assimp\scene.h"

class Mesh;
class Material;
class Texture;

class Model {

public:
	Model(std::string& path);
	~Model();

	std::vector<Mesh*> getMeshes() const { return m_Meshes; };
private:
	std::vector<Texture*> textures_loaded;
	std::vector<Mesh*> m_Meshes;
	std::vector<Material*> m_Materials;
	std::string m_Directory;

	void loadModel(std::string& path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* node, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};