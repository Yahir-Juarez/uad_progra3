#pragma once
#pragma once

#include <map>

#include "Globals.h"
#include "CApp.h"
#include "CVector3.h"
#include "../Include/Parcial-1.h"
#include "Mundo.h"
#include "Frustum.h"
#include "CCamera.h"
class objData
{
public:
	void setPtrIDsData(map<string, IDsRender>& dataIDs);
	string nameObj;
	int posRow;
	int posCol;
	MathHelper::Matrix4 posicionMatriz;
	int numFaces;
	IDsRender* ptrIDsData;
};