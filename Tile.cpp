#include "Tile.h"

#include <iostream>

using namespace std;

Tile::Tile(std::string imageName)
{
	m_image = load_bmp( imageName.c_str() ,NULL );
	m_box = m_frame = NULL;
	w = m_image->w;
	h = m_image->h;
	
}

BITMAP* Tile::getFrame(int x,int y,int w,int h)
{
	if( m_frame != NULL ) destroy_bitmap( m_frame );
	m_frame = create_bitmap(800,600);
	
	if(!m_frame)
	{
		cout << "Error in Loading BitMap in file Tile.cpp" << endl;
		exit(1);
	}
	
	int ximage = x - (800 - m_image->w) / 2; 
	int yimage = y - (600 - m_image->h) / 2; 
	
	blit(m_image ,m_frame ,0 , 0, 0, 0, m_frame->w ,m_frame->h);

	return m_frame;
	 
}


BITMAP* Tile::getBox(int x,int y,int w,int h)
{
	if( x<0 || y<0 ) return NULL;
	m_box = create_sub_bitmap( m_image, x, y, w, h);
	if(!m_box)
	{
		cout << "Error in Loading BitMap in file Tile.cpp" << endl;
		return NULL;
	}
	return m_box;
}

Tile::~Tile()
{
	destroy_bitmap(m_image);
	if( m_frame != NULL )
		destroy_bitmap(m_frame);
	if( m_box != NULL )
    	destroy_bitmap(m_box);
}
