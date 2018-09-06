#ifndef AREALIST_H
#define AREALIST_H

class Area;

class AreaList
{
public:
	AreaList() : thisArea(0), next(0), prior(0) {};
	~AreaList();

	bool isFirst();
	bool isLast();
	bool contains(Area*);
	Area* getThis();
	AreaList* getPrior();
	AreaList* getNext();
	AreaList* getFirst();
	AreaList* getLast();
	int getLength();
	void addArea(Area*);
	void RemoveThis();
	void appendAreaList(AreaList);

private:
	Area* thisArea;
	AreaList* next;
	AreaList* prior;
};

#endif // AREALIST_H