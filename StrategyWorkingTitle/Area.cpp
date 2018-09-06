#include "Area.h"
#include "AreaList.h"
#include "Map.h"

// returns the map this area belongs to
Map* Area::getMap()
{
	return this->map;
}

// creates zone without spots
Zone::Zone(Map* parent): Area(parent), spotList() {}

// creates zone with Spots
// spots: AreaList of spots to init the zone with
// (doesn't assign spots if maps don't match)
Zone::Zone(Map* parent, AreaList spots) : Area(parent), spotList()
{
	AreaList* entry;
	for (entry = spots.getFirst(); !entry->isLast(); entry = entry->getNext()){
		Area* newSpot = entry->getThis();
		if (newSpot->isSpot() && newSpot->getMap() == this->map) {
			this->spotList.addArea(newSpot);
		}
	}
}

Zone::~Zone() {}

// returns true if this zone shares any spots with the given area
bool Zone::isOverlapping(Area* area)
{
	if (this->map != area->getMap()) return false;
	return this->spotList.contains(area);
}

bool Zone::isSpot()
{
	return false;
}

bool Zone::isZone()
{
	return true;
}

// return true if this zone contains the given spot
bool Zone::containsSpot(Spot* spot)
{
	return this->spotList.contains(spot);
}

// adds the given spot to this zone
void Zone::addSpot(Spot* spot)
{
	this->spotList.addArea(spot);
}

// returns number of spots in this zone
int Zone::getSpotCount()
{
	return this->spotList.getLength;
}

// returns a pointer to the first entry of this zones list of spots
AreaList Zone::getSpots()
{
	return this->spotList;
}

// creates spot without neighbours
Spot::Spot(Map* parent) : Area(parent), neighbourList() {}

// creates spot with neighbours
// neighbours: AreaList of spots
// (doesn't assign neighbours if maps don't match)
Spot::Spot(Map* parent, AreaList neighbours) : Area(parent), neighbourList()
{
	AreaList* entry;
	for (entry = neighbours.getFirst(); entry; entry = entry->getNext()){
		Area* newNeighbour = entry->getThis();
		if (newNeighbour->isSpot() && newNeighbour->getMap() == this->map) {
			this->addNeighbour((Spot*)newNeighbour);
		}
	}
}

Spot::~Spot()
{
}

bool Spot::isSpot()
{
	return true;
}

bool Spot::isZone()
{
	return false;
}

// returns true if this spot is neighbour to the given spot
bool Spot::isNeighbour(Spot* spot)
{
	return this->neighbourList.contains(spot);
}

// returns the number of neighbours this spot has
int Spot::getNeighbourCount()
{
	return this->neighbourList.getLength();
}

// returns a pointer to the first entry of this spots list of neighbours
AreaList Spot::getNeighbours()
{
	return this->neighbourList;
}

// determines this spot and the given spot as neighbours
void Spot::addNeighbour(Spot* spot)
{
	if (!spot->isNeighbour(this) && spot->getMap() == this->map){
		this->neighbourList.addArea(spot);
		spot->addNeighbour(this);
	}
}

// returns an AreaList of the Spots that resemble the shortest path to the given spot
// destination: Spot that the path leads to
AreaList Spot::getShortestPath(Spot* destination, AreaList exclusions = AreaList(), bool mapCheck = true){
	AreaList path;
	if (mapCheck) if(!this->map->getSpots().contains(destination)) return path;
	path.addArea(this);
	if (destination == this) return path;
	exclusions.addArea(this);
	AreaList* entry;
	AreaList restPath;
	int restPathLength = 0;
	for (entry = this->getNeighbours().getFirst(); !entry->isLast(); entry = entry->getNext()){
		Spot* neighbour = (Spot*)(entry->getThis());
		if (exclusions.contains(neighbour)) continue;
		AreaList restPath_temp = neighbour->getShortestPath(destination, exclusions, false);
		if (restPathLength > restPath_temp.getLength() || restPathLength == 0){
			restPath = restPath_temp;
			restPathLength = restPath.getLength();
		}
	}
	if (restPathLength > 1) path.appendAreaList(restPath);
	return path;
}