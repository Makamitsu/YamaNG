#include "Model.h"
#include "Texture.h"
#include "Mesh.h"
#include "VertexBufferLayout.h"

#include <iostream>

#include "glm\glm.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Model::Model(std::string & path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::loadModel(std::string& path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	VertexBufferLayout* layout = new VertexBufferLayout();
	layout->push<GL_FLOAT, 4>(3, VertexBufferElementType::POSITION);
	layout->push<GL_FLOAT, 4>(3, VertexBufferElementType::NORMAL);
	layout->push<GL_FLOAT, 4>(2, VertexBufferElementType::TEX_COORD);
	unsigned int VBsize = mesh->mNumVertices * layout->getStride();
	float* VBdata = new float[VBsize];

	unsigned int IBsize = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			++IBsize;
	}
	unsigned int* IBdata = new unsigned int[IBsize];

	std::vector<Texture> textures;

	int crs = 0;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		//positions
		VBdata[crs++] = mesh->mVertices[i].x;
		VBdata[crs++] = mesh->mVertices[i].z;
		VBdata[crs++] = mesh->mVertices[i].y;
		//normals
		VBdata[crs++] = mesh->mNormals[i].x;
		VBdata[crs++] = mesh->mNormals[i].y;
		VBdata[crs++] = mesh->mNormals[i].z;
		//texCoord
		if (mesh->mTextureCoords[0]) {
			VBdata[crs++] = mesh->mTextureCoords[0][i].x;
			VBdata[crs++] = mesh->mTextureCoords[0][i].y;
		}
		else {
			VBdata[crs++] = 0.0f;
			VBdata[crs++] = 0.0f;
		}
	}

	crs = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace& face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			IBdata[crs++] = face.mIndices[j];
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return new Mesh( (void*)VBdata, VBsize, IBdata, IBsize, *layout);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture(str.C_Str());
		textures.push_back(texture);
	}
	return textures;
}
