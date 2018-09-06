#ifndef AREA_H
#define AREA_H

#ifndef AREALIST_H
#include "AreaList.h"
#endif

class Map;

// abstract base class of spots and zones
class Area
{
public:
	Area(Map* parent) : map(parent) {};
	virtual ~Area() {};

	virtual bool isSpot() = 0;
	virtual bool isZone() = 0;
	Map* getMap();

protected:
	Map* map;
};

// class that combines groups of spots
class Zone :
	public Area
{
public:
	Zone(Map*);
	Zone(Map*, AreaList);
	~Zone();

	bool isOverlapping(Area*);
	bool isSpot();
	bool isZone();
	bool containsSpot(Spot*);
	int getSpotCount();
	AreaList getSpots();
	void addSpot(Spot*);

private:
	AreaList spotList;
};

// spots resemble actual places on a map, where units can stand on and move between
class Spot :
	public Area
{
public:
	Spot(Map*);
	Spot(Map*, AreaList);
	~Spot();

	bool isSpot();
	bool isZone();
	bool isNeighbour(Spot*);
	bool isLinked(Spot*); // noch zu implementieren. Linklisten beim Nachbarn hinzufügen aktualisieren muss noch implementiert werden
	int getNeighbourCount();
	AreaList getNeighbours();
	void addNeighbour(Spot*);
	AreaList getShortestPath(Spot*, AreaList, bool); // isLinked Abfrage muss noch eingefügt werden

private:
	AreaList neighbourList;
};

#endif // AREA_H
