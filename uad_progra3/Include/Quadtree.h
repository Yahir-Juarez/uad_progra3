#pragma once
#include <map>

//#include "Globals.h"
//#include "CApp.h"
//#include "CVector3.h"
#include "../Include/Parcial-1.h"
//#include "Mundo.h"
//#include "Frustum.h"
//#include "CCamera.h"
//#include "objDataParcal3.h"
#include "QuadtreeNode.h"
#include "Cells.h"

class Quadtree
{
private:
	vector<cell*> m_newCells;
	QuadtreeNode* m_root;
public:
	void creatQuadtreeNodess(int numRows, int numColum, vector<cell*> m_nodoCells);
	void render(Camera* cam, vector<cell*> visibleCells){}
};