#include "../Include/Quadtree.h"

void Quadtree::creatQuadtreeNodess(int numRows, int numColum, vector<cell*> m_nodoCells)
{
	m_newCells = m_nodoCells;
	m_root->creatQuadtreeNodes(numRows, numColum, m_newCells);

}