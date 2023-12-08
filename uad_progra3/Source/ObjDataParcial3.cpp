#include "../Include/objDataParcal3.h"

void objData::setPtrIDsData(map<string, IDsRender>& dataIDs)
{
	ptrIDsData = &dataIDs[nameObj];
}