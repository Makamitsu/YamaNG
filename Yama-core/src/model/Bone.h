#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>

#include <assimp/scene.h>

class Mesh;
class Skeleton;

static aiMatrix4x4 GLMMat4ToAi(glm::mat4 mat)
{
	return aiMatrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}

static glm::mat4 AiToGLMMat4(aiMatrix4x4& in_mat)
{
	glm::mat4 tmp;
	tmp[0][0] = in_mat.a1;
	tmp[1][0] = in_mat.b1;
	tmp[2][0] = in_mat.c1;
	tmp[3][0] = in_mat.d1;

	tmp[0][1] = in_mat.a2;
	tmp[1][1] = in_mat.b2;
	tmp[2][1] = in_mat.c2;
	tmp[3][1] = in_mat.d2;

	tmp[0][2] = in_mat.a3;
	tmp[1][2] = in_mat.b3;
	tmp[2][2] = in_mat.c3;
	tmp[3][2] = in_mat.d3;

	tmp[0][3] = in_mat.a4;
	tmp[1][3] = in_mat.b4;
	tmp[2][3] = in_mat.c4;
	tmp[3][3] = in_mat.d4;
	return tmp;
}

class Bone
{
public:
	unsigned int id;
	std::string name;    //The bone's name as loaded by ASSIMP.

	Mesh* mesh;    //The mesh this bone is going to affect.
				   //Only one skeleton per mesh one mesh per skeleton is currently supported.

	aiNode* node;   //This bone's corresponding aiNode 
					//(this is where we'll get its transformation matrix,
					//as well as its parent and children nodes.

	aiNodeAnim* animNode;    //This is the bone's corresponding aiNodeAnim,
							 //where we'll get info for this bone's current
							 //animation. Remember that this node contains
							 //the keyframes for every animation this bone has,
							 //when we eventually start switching animations,
							 //we won't be changing which aiNodeAnim this
							 //variable points to, but rather at which point in 
							 //this massive array of keyframes we wish to start.


	Bone* parent_bone;    //A pointer to this bone's parent bone.
	glm::mat4 parent_transforms;    //This is a concatenation of all transforms
									//before this bone, from this bone's parent,
									//all the way to the skeleton's root node.
									//This is used when calculating the current
									//keyframe's transformation.

	glm::mat4 offset_matrix;    //The offset matrix, and correct me if I'm wrong
								//about this, is the matrix that transforms from
								//the bone's local space to its world space.
								//Think of it as being like a model matrix, 
								//transforming vertices from their default
								//positions relative to the mesh, into their new
								//positions in world space.

	Skeleton* parent_skeleton;  //The parent skeleton of this bone.
								//Note that the skeleton class does not exist
								//YET. We will write it as soon as we are done
								//with the bone class (Tutorial #3)

	Bone() { name = ""; id = -2; }

	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, aiMatrix4x4 in_o_mat);
	Bone(Mesh* in_mesh, unsigned int in_id, std::string in_name, glm::mat4 in_o_mat);

	glm::mat4 GetParentTransforms();
};