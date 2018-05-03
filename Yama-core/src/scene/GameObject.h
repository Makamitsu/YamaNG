#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Componant.h"

class Model;
class Transform;

class GameObject{

private:
public:
	std::unordered_map<std::string, Componant> componants;
	
	GameObject* parent;
	std::vector<GameObject*> childs;

	Model* model;
	Transform* transform;

	GameObject();
	~GameObject();
	
};