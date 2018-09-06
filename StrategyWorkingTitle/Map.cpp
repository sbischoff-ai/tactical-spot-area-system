#include "Map.h"

Map::~Map()
{
}

AreaList Map::getSpots(){
	return this->spotList;
}

AreaList Map::getLinkzones(){
	return this->linkzoneList;
}