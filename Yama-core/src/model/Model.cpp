#include "Model.h"
#include "Texture.h"
#include "Mesh.h"
#include "Bone.h"

#include <iostream>
#include <vector>

#include "glm\glm.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>





Model::Model(std::string & path) {
	m_dataLayout = VertexBufferLayout();
	m_dataLayout[DataType::POSITION][DataType::NORMAL][DataType::TEX_COORD];
	loadModel(path);
}

Model::Model(std::string& path, const VertexBufferLayout& dataLayout):m_dataLayout(dataLayout){
	loadModel(path);
};


Model::~Model()
{
	for (Mesh* m : m_Meshes) {
		delete m;
	}
}

void Model::loadModel(std::string& path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs| aiProcess_GenSmoothNormals);

	for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
		m_Materials.push_back(&Material(*scene->mMaterials[i]));
	}

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
	unsigned int VBsize = mesh->mNumVertices * m_dataLayout.getStride();
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
	Mesh* lMesh = new Mesh( (void*)VBdata, VBsize, IBdata, IBsize, m_dataLayout);
	lMesh->setMaterial( mesh->mMaterialIndex<m_Materials.size() ? m_Materials.at(mesh->mMaterialIndex) : nullptr );
	return lMesh;
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


/***********************************************************************************************************/
/***********************************************************************************************************/
/***********************************************************************************************************/
/***********************************************************************************************************/
/*
void Model::recursiveNodeProcess(aiNode* node)
{
	ai_nodes.push_back(node);

	for (unsigned int i = 0; i < node->mNumChildren; i++)
		recursiveNodeProcess(node->mChildren[i]);
}
void Model::AnimNodeProcess()
{
	if (m_scene->mNumAnimations == 0)
		return;

	for (unsigned int i = 0; i < m_scene->mAnimations[0]->mNumChannels; i++)
		ai_nodes_anim.push_back(m_scene->mAnimations[0]->mChannels[i]);
	//We only get data from the first mAnimation because 
	//Assimp crushes all of the animation data into one
	//large sequence of data known as mAnimation.
	//Assimp does not support multiple mAnimations, surprisingly.
}


Bone* Model::FindBone(std::string name)
{
	for (unsigned int i = 0; i < m_bones.size(); i++)
	{
		if (m_bones.at(i).name == name)
			return &m_bones.at(i);
	}
	//This function simply scans our vector bones and checks if
	//any name matches the name we're looking for, if it doesn't
	//find any, we return nullptr.
	//Keep in mind, the bones vector is empty at the point of writing this,
	//but when this function is called it will already be filled up.
	return nullptr;
}

aiNode* Model::FindAiNode(std::string name)
{
	for (unsigned int i = 0; i < ai_nodes.size(); i++)
	{
		if (ai_nodes.at(i)->mName.data == name)
			return ai_nodes.at(i);
	}
	//This function's purpose is identical, except that instead of Bones,
	//it's looking for an aiNode* inside our ai_nodes vector.
	//This vector has already been filled by our recursiveNodeProcess() function.
	return nullptr;
}

aiNodeAnim* Model::FindAiNodeAnim(std::string name)
{
	for (unsigned int i = 0; i < ai_nodes_anim.size(); i++)
	{
		if (ai_nodes_anim.at(i)->mNodeName.data == name)
			return ai_nodes_anim.at(i);
	}
	//This function finds the animation with the name we pass in, we called it
	//right after calling our recursiveNodeProcess() function, but this function
	//will only really come into play during the next tutorial, where we cover
	//the actual animation portion of skeletal animation.
	return nullptr;
}

int Model::FindBoneIDByName(std::string name)
{
	for (unsigned int i = 0; i < m_bones.size(); i++)
	{
		if (m_bones.at(i).name == name)
			return i;
	}
	//This function finds the position of a certain bone within our bones vector.
	//This position is equal to the bone's ID, which is vital to determining the
	//rigging of our model within the vertex shader.
	return -1;    //In case we don't find a bone ID, we return -1.
				  //Just to avoid any confusion later on as to whether or not the
				  //ID was found. (It serves the same purpose as returning nullptr).
}

void Model::init(const char* filename)
{
	Assimp::Importer importer;

	importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_Triangulate |
		aiProcess_CalcTangentSpace | aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices);

	m_scene = importer.GetOrphanedScene();
	m_Meshes = new std::vector<Mesh*>();

	if (m_scene != NULL)
	{
		error = false;


		aiNode* rootNode = m_scene->mRootNode;
		recursiveNodeProcess(rootNode);
		AnimNodeProcess();
		globalInverseTransform = glm::inverse(AiToGLMMat4(rootNode->mTransformation));

		recursiveProcess(rootNode, m_scene, error);

		for (int i = 0; i < m_scene->mNumMeshes; i++)
		{
			for (int j = 0; j < m_scene->mMeshes[i]->mNumBones; j++)
			{
				//Here we're just storing the bone information that we loaded
				//with ASSIMP into the formats our Bone class will recognize.
				std::string b_name = m_scene->mMeshes[i]->mBones[j]->mName.data;
				glm::mat4 b_mat = glm::transpose(AiToGLMMat4(m_scene->mMeshes[i]->mBones[j]->mOffsetMatrix));

				//Just because I like debugging...
				std::cout << "Bone " << j << " " << b_name << std::endl;

				//Here we create a Bone Object with the information we've
				//gathered so far, but wait, there's more!
				Bone bone(&m_Meshes->at(i), i, b_name, b_mat);

				//These next parts are simple, we just fill up the bone's
				//remaining data using the functions we defined earlier.
				bone.node = FindAiNode(b_name);
				bone.animNode = FindAiNodeAnim(b_name);

				if (bone.animNode == nullptr)
					std::cout << "No Animations were found for " + b_name << std::endl;

				//Finally, we push the Bone into our vector. Yay.
				m_bones.push_back(bone);
			}
		}


		//Now we have to fill up the remaining ... remaining data within the
		//bone object, specifically: the pointers to the bone's parent bone.
		for (int i = 0; i < m_bones.size(); i++)
		{
			//Here we cycle through the existing bones and match them up with
			//their parents, the code here is pretty self explanatory.
			std::string b_name = m_bones.at(i).name;
			std::string parent_name = FindAiNode(b_name)->mParent->mName.data;

			Bone* p_bone = FindBone(parent_name);

			m_bones.at(i).parent_bone = p_bone;

			if (p_bone == nullptr)
				std::cout << "Parent Bone for " << b_name << " does not exist (is nullptr)" << std::endl;
		}
		//I tried combining the above loop with the one above, but this 
		//only resulted in crashes, and my Just-In-Time debugger isn't working,
		//so I'll just leave it as is.

		//Here we only need to give the first Mesh in meshes the skeleton data
		//because in order to initialize the GameObject that will encapsulate this
		//Mesh, we only need one skeleton. The GameObject will copy the skeleton
		//of the first Mesh in its meshes vector and use this as its own.
		//Did that not make sense?
		//Shit.
		//It will later on though, so don't worry.
		if (m_Meshes->size() > 0)
			m_Meshes->at(0).sceneLoaderSkeleton.Init(m_bones, globalInverseTransform);
	}
}*/
