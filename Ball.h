#ifndef BALL_H
#define BALL_H
#include <allegro.h>
struct Vector
{
	float x;
	float y;
};

class Ball
{
	public:
		BITMAP* ball;
		BITMAP* t;
		BITMAP* l;
		BITMAP* b;
		BITMAP* r;
		float mass;
		Vector speed;
		Vector maxSpeed;
		Vector acceleration;
		Vector position;
		int w;
		int h;
		
		Ball();
		~Ball();
		void proc( bool, bool, bool, bool );
		BITMAP* render();
};

#endif
