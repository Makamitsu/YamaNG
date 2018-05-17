#pragma once

#include <vector>

#include "assimp\scene.h"
#include "VertexBufferLayout.h"

#define NB_BONES_PER_VERTEX 4

class Mesh;
class Bone;
class Material;
class Texture;
class VertexBufferLayout;

struct BoneWeight {
	unsigned int boneID[NB_BONES_PER_VERTEX];
	float weight[NB_BONES_PER_VERTEX];
};

class Model {

public:
	Model(std::string& path);
	Model(std::string& path, const VertexBufferLayout& dataLayout);
	~Model();

	std::vector<Mesh*> getMeshes() const { return m_Meshes; };

private:
	std::vector<Texture*> textures_loaded;
	std::vector<Mesh*> m_Meshes;
	std::vector<Material*> m_Materials;
	std::vector<Bone> m_bones;
	std::string m_Directory;

	VertexBufferLayout m_dataLayout;

	/* save the node 
	aiScene* m_scene;
	std::vector<aiNode*> ai_nodes;
	std::vector<aiNodeAnim*> ai_nodes_anim;
	void recursiveNodeProcess(aiNode* node);
	void AnimNodeProcess();
	void init(const char* filename);
	^ fill the vector ^ */


	void loadModel(std::string& path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* node, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	/*
	Bone* FindBone(std::string name);
	aiNode* FindAiNode(std::string name);
	aiNodeAnim* FindAiNodeAnim(std::string name);
	int FindBoneIDByName(std::string name);
	*/
};