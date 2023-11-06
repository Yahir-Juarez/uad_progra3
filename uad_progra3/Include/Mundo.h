#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "../Dependencies/JSON/nlohmann/json.hpp"
#include "../Include/CVector3.h"

using namespace std;
using json = nlohmann::json;

struct IDsRender
{
	unsigned int ShaderId;
	unsigned int GeometryId;
	int numFaces;
};

class Mundo
{
public:
	
};