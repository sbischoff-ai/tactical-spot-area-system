#include "AreaList.h"

AreaList::~AreaList()
{
	if (this->next) delete this->next;
}

bool AreaList::isFirst()
{
	if (this->prior) return false;
	return true;
}

bool AreaList::isLast()
{
	if (this->next) return false;
	return true;
}

bool AreaList::contains(Area* area)
{
	AreaList* entry;
	for (entry = this->getFirst(); entry; entry = entry->getNext()) if (entry->getThis() == area) return true;
	return false;
}

Area* AreaList::getThis()
{
	return this->thisArea;
}

AreaList* AreaList::getPrior()
{
	return this->prior;
}

AreaList* AreaList::getNext()
{
	return this->next;
}

AreaList* AreaList::getFirst()
{
	if (this->isFirst()) return this;
	AreaList* entry = this;
	while (!entry->isFirst()) entry = entry->getPrior();
	return entry;
}

AreaList* AreaList::getLast()
{
	if (this->isLast()) return this;
	AreaList* entry = this;
	while (!entry->isLast) entry = entry->getNext();
	return entry;
}

int AreaList::getLength()
{
	int l = 0;
	AreaList* entry;
	for (entry = this->getFirst(); entry; entry = entry->getNext()) l++;
	return l;
}

void AreaList::addArea(Area* area)
{
	AreaList* entry = this->getLast(); 
	if (!entry->thisArea) entry->thisArea = area;
	else {
		entry->next = new AreaList();
		entry->next->thisArea = area;
		entry->next->prior = entry;
	}
}

void AreaList::RemoveThis()
{
	AreaList* entry;
	for (entry = this; !entry->isLast(); entry = entry->getNext()) entry->thisArea = entry->getNext()->thisArea;
	entry->getPrior()->next = 0;
	delete entry;
}

void AreaList::appendAreaList(AreaList newList){
	AreaList* entry;
	for (entry = newList.getFirst(); entry; entry = entry->getNext()) this->addArea(entry->getThis);
}