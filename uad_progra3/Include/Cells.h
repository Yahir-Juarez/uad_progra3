#pragma once

#include <map>
#include "objDataParcal3.h"

class cell
{
public:
	int posCol;
	int posRow;
	vector<objData*> objetos;
	int carasTotal = 4;
};