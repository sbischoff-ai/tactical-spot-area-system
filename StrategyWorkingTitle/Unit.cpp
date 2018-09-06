#include "Unit.h"
#include "Area.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

bool Unit::isInArea(Area* area)
{
	if (area->isSpot())
		return area == this->location;
	int i;
	if (area->isZone()) 
	{
		Zone* zone = dynamic_cast<Zone*>(area);
		for (i = 0; i < zone->getSpotCount(); i++) if (zone->getSpot(i) == this->location) return true;
	}
	return false;
}