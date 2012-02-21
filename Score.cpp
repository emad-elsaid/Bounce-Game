#include "Score.h"
#include <iostream>
using namespace std;

Score::Score()
{
	m_value = 0 ;
}

bool Score::isLess()
{
	if(m_value < 0)
		return true;
	else
		return false;
}
double Score::getValue()
{
	return m_value + VALUEMULTIPLIER;
}

Score Score::operator += (int x)
{
	m_value += x;
}

void Score::operator -= (int x)
{
	m_value -= x;
	if( isLess() )
		m_value = 0;
	
}

BITMAP* Score::render(int Width, int Height)
{
	BITMAP* bmp;
	bmp = create_bitmap( Width ,Height);
	clear_to_color( bmp, makecol(255,0,255) );// to make it transparent
	textprintf_centre_ex( bmp, font, Width / 2, Height / 2, makecol(0, 100, 243), -1   //Change Here if You want to change color but Leave the -1
	 , "%i",m_value );
	return bmp;
}
