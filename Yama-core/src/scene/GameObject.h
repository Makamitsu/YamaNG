#pragma once

#include "Componant.h"

#include <unordered_map>
#include <string>
#include "Model.h"

class GameObject {

private:
	std::unordered_map<std::string, Componant> componants;
	
	Model model;

public:

};