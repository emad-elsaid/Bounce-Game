#include "Life.h"

#include <iostream>
using namespace std;

Life::Life()
{
	m_numberOfLives = 0;
}

Life::Life( int NOL)
{
	if ( NOL > MAXNUMBEROFLIVES)
		m_numberOfLives = 1;
	else
		m_numberOfLives = NOL;
}

bool Life::isOver()
{
	if ( m_numberOfLives <= 1)
		return true;
	else
		return false;
}

void Life::operator++()
{
	m_numberOfLives++;
}

void Life::operator++(int x)
{
	m_numberOfLives++;
}

void Life::operator--()
{
	--m_numberOfLives;
	if( isOver() )
		m_numberOfLives = 1;
}
void Life::operator--(int x)
{
	m_numberOfLives--;
	if( isOver() )
		m_numberOfLives = 1;
}
BITMAP* Life::render( int Width, int Height)
{
	BITMAP* bmp;
	bmp = create_bitmap_ex( 32 ,Width ,Height); 
	clear_to_color( bmp, makecol(255,0,255) );// to make it transparent
	textprintf_centre_ex( bmp, font, Width / 2, Height / 2, makecol(0, 100, 243), -1   //Change Here if You want to change color but Leave the -1
	 , "%i",m_numberOfLives );
	return bmp;
}
