#ifndef SCORE_H
#define SCORE_H
#include <allegro.h>
#define VALUEMULTIPLIER 100

class Score
{
	unsigned int m_value;
	bool isLess();
	public:
		Score();
		double getValue();
		Score operator += ( int );
		void operator -= ( int );
		BITMAP* render( int , int);
};


#endif
