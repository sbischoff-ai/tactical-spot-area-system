#ifndef UNIT_H
#define UNIT_H

class Spot;
class Area;

class Unit
{
public:
	Unit();
	~Unit();

	bool isInArea(Area*);

protected:
	Spot* location;
};

#endif // UNIT_H