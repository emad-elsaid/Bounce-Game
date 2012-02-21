#ifndef LIFE_H
#define LIFE_H

#include <allegro.h>

#define MAXNUMBEROFLIVES 10

class Life
{
	private:
		 int m_numberOfLives;
			
	public:
			Life();
			Life( int );
			bool isOver();
			void operator++();
			void operator++(int x); 
			void operator--();
			void operator--(int x);
			BITMAP *render( int , int);
};
#endif
