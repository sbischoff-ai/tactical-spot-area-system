#ifndef MAP_H
#define MAP_H

#ifndef AREALIST_H
#include "AreaList.h"
#endif

class Session;

class Map
{
public:
	Map(Session* parent) : session(parent), spotList(), linkzoneList() {};
	~Map();

	AreaList getSpots();
	AreaList getLinkzones();

protected:
	AreaList spotList;
	AreaList linkzoneList;
	Session* session;
};

#endif //MAP_H
