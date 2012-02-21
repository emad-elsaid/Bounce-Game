#ifndef TILE_H
#define TILE_H

#include <allegro.h>
#include <string>


class Tile
{
	protected:
		BITMAP *m_image;
		BITMAP *m_frame;
		BITMAP *m_box;

public:
	int w;
	int h;
	Tile(std::string);
	BITMAP *getFrame( int ,int ,int ,int);
	BITMAP *getBox( int,int ,int ,int);
	~Tile();
};


#endif
