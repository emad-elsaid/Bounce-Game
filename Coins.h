#ifndef COINS_H
#define COINS_H
#include <string>

#include "Tile.h"

class Coins : public Tile
{
	private:
		
	public:
		Coins(std::string);
		void transparent(int ,int);
		
};

#endif
