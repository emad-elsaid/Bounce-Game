#include "Coins.h"



 Coins::Coins(std::string S) : Tile(S)
{
	
}

void Coins::transparent(int x,int y)
{
	if( _getpixel32(m_image,x ,y) != 16711935)
	{
		_putpixel32(m_image ,x ,y ,16711935);
		transparent(x-1,y-1);
		transparent(x-1,y);
		transparent(x-1,y+1);
		transparent(x,y-1);
		transparent(x,y+1);
		transparent(x+1,y-1);
		transparent(x+1,y);
		transparent(x+1,y+1);
		
	}
}
