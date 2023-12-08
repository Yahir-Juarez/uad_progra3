#include "../Include/QuadtreeNode.h"

void QuadtreeNode::creatQuadtreeNodes(int numRows, int numColum, vector<cell*> m_newCells)
{
	int EstandarFaces = 40;
	int caras_totales = 0;
	for (int i = 0; i < m_newCells.size(); i++)
	{
		cout << "Caras -> " << m_newCells[i]->carasTotal << " Columna -> " << m_newCells[i]->posCol << " Fila -> " << m_newCells[i]->posRow << endl;
		cout << "Objetos dentro de la celda" << endl;
		for (int j = 0; j < m_newCells[i]->objetos.size(); j++)
		{
			cout << "Nombre -> " << m_newCells[i]->objetos[j]->nameObj << " Columna -> " << m_newCells[i]->objetos[j]->posCol << " Fila -> " << m_newCells[i]->objetos[j]->posRow << endl;
		}
	}
	for (int i = 0; i < m_newCells.size(); i++)
	{
		caras_totales += m_newCells[i]->carasTotal;
	}
	if (caras_totales < EstandarFaces && numRows > 1 && numColum > 1)
	{
		for (int i = 0; i < m_newCells.size(); i++)
		{
			m_nodoCells = m_newCells;
		}
		return;
	}
	int indexCol = numColum / 2;
	int indexRow = numRows / 2;


	vector<cell*> cellTopLeft;
	vector<cell*> cellTopRight;
	vector<cell*> cellBottomLeft;
	vector<cell*> cellBottomRight;

	for (int i = 0; i < m_newCells.size(); i++)
	{
		if (m_newCells[i]->posCol <= indexCol)
		{
			if (m_newCells[i]->posCol <= indexRow)
			{
				cellTopLeft.push_back(m_newCells[i]);
			}
			else
			{
				cellTopRight.push_back(m_newCells[i]);
			}
		}
		else
		{
			if (m_newCells[i]->posCol <= indexRow)
			{
				cellBottomLeft.push_back(m_newCells[i]);
			}
			else
			{
				cellBottomRight.push_back(m_newCells[i]);
			}
		}
	}
	m_topLeft->creatQuadtreeNodes(indexRow, indexCol, cellTopLeft);
	m_topRight->creatQuadtreeNodes(numRows - indexRow, indexCol, cellTopLeft);
	m_topLeft->creatQuadtreeNodes(indexRow, numColum - indexCol, cellTopLeft);
	m_topLeft->creatQuadtreeNodes(numRows - indexRow, numColum - indexCol, cellTopLeft);



	//for (int i = 0; i < actualSector->objectsRender.size(); i++)
	//{
	//	if (actualSector->objectsRender[i].posCol <= indexCol)
	//	{
	//		if (actualSector->objectsRender[i].posRow <= indexRow)
	//		{
	//			sectorA.objectsRender.push_back(actualSector->objectsRender[i]);
	//		}
	//		else
	//		{
	//			sectorB.objectsRender.push_back(actualSector->objectsRender[i]);
	//		}
	//	}
	//	else
	//	{
	//		if (actualSector->objectsRender[i].posRow <= indexRow)
	//		{
	//			sectorC.objectsRender.push_back(actualSector->objectsRender[i]);
	//		}
	//		else
	//		{
	//			sectorD.objectsRender.push_back(actualSector->objectsRender[i]);
	//		}
	//	}
	//}
	//sectorA.SectorPoint = actualSector->SectorPoint;
	//sectorB.SectorPoint = actualSector->SectorPoint;
	//sectorB.SectorPoint.Z += (cellSize * 2) * (indexRow + 1);
	//sectorC.SectorPoint = actualSector->SectorPoint;
	//sectorC.SectorPoint.X += (sqrt(3) * cellSize) * (indexCol + 1);
	//sectorD.SectorPoint = actualSector->SectorPoint;
	//sectorD.SectorPoint.X += (sqrt(3) * cellSize) * (indexCol + 1);
	//sectorD.SectorPoint.Z += (cellSize * 2) * (indexRow + 1);

	//sectorA.totalFaces = getTotalNumFaces(sectorA);
	//sectorB.totalFaces = getTotalNumFaces(sectorB);
	//sectorC.totalFaces = getTotalNumFaces(sectorC);
	//sectorD.totalFaces = getTotalNumFaces(sectorD);

	//sectorA.numColumns = indexCol;
	//sectorA.numRows = indexRow;
	//sectorB.numColumns = indexCol;
	//sectorB.numRows = actualSector->numRows - indexRow;
	//sectorC.numColumns = actualSector->numColumns - indexCol;
	//sectorC.numRows = indexRow;
	//sectorD.numColumns = actualSector->numColumns - indexCol;
	//sectorD.numRows = actualSector->numRows - indexRow;

	//sectors.push_back(sectorA);
	//sectors.push_back(sectorB);
	//sectors.push_back(sectorC);
	//sectors.push_back(sectorD);

	//int sizePreFor = sectors.size() - 4;

	//for (int i = sectors.size() - 1; i > sizePreFor; i--)
	//{
	//	if (sectors[i].totalFaces < EstandarFaces)
	//	{
	//		createFrustum(&sectors[i]);
	//		sectors.erase(sectors.begin() + i);
	//	}
	//}
}