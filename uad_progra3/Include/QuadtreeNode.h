#pragma once
#include <map>

//#include "Globals.h"
//#include "CApp.h"
//#include "CVector3.h"
//#include "../Include/Parcial-1.h"
//#include "Mundo.h"
//#include "Frustum.h"
//#include "CCamera.h"
//#include "CAppParcial-3.h"
#include "AABB.h"
#include "Cells.h"

class QuadtreeNode
{
private:
	QuadtreeNode* m_topLeft;
	QuadtreeNode* m_topRight;
	QuadtreeNode* m_bottomLeft;
	QuadtreeNode* m_bottomRight;
	vector<cell*> m_nodoCells;
	AABB m_nodeLimits;

public:
	QuadtreeNode() {}
	~QuadtreeNode() {}
	void creatQuadtreeNodes(int numRows, int numColum, vector<cell*> m_nodoCells);
	void render(Camera* cam, vector<cell*> visibleCells){}
};