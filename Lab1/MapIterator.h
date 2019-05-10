#pragma once
#include "Map.h"

class Map;

class MapIterator 
{
	friend class Map;

private:

	
	MapIterator(const Map  &map);
	
	const Map &map;

	int currentIndex = 0;

public: 

	TElem getCurrent() const;

	bool valid() const;

	void next();

	void first();

};