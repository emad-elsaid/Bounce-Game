
#include <iostream>
#include "Ball.h"

Ball::Ball()
{
	// setting mass of the ball
	mass = 1;
	
	// speed defining
	speed.x = speed.y = 0;
	
	// position defining
	position.x = 50; position.y = 50;
	
	// define max speed;
	maxSpeed.x = 10;
	maxSpeed.y = 10;
	
	// define acceleration
	acceleration.x = 7;
	acceleration.y = 7;
	
	//loading the image
	ball = load_bitmap( "ballsprit.bmp", NULL );
	
	t = create_sub_bitmap( ball, ball->w/4, 0, ball->w/2, ball->h/4 );
	l = create_sub_bitmap( ball, 0, ball->h/4, ball->w/4, ball->h/2 );
	b = create_sub_bitmap( ball, ball->w/4, ball->h*3/4, ball->w/2, ball->h/4 );
	r = create_sub_bitmap( ball, ball->w*3/4, ball->h/4, ball->w/4, ball->h/2 );
	//define ball dimensions
	w = ball->w;
	h = ball->h;
	
}

Ball::~Ball()
{
	destroy_bitmap( t );
	destroy_bitmap( l );
	destroy_bitmap( b );
	destroy_bitmap( r );
	destroy_bitmap( ball );
}

void Ball::proc( bool top, bool left, bool bottom, bool right )
{
	//-----------------------------------
	// managing KEYS pressed
	//-----------------------------------
	if( key[KEY_RIGHT] && right && speed.x < maxSpeed.x )
		speed.x += acceleration.x;
		
	if( key[KEY_LEFT] && left && -speed.x < maxSpeed.x )
		speed.x -= acceleration.x;
	
	if( key[KEY_SPACE] && top && !bottom && speed.y < maxSpeed.y )
		speed.y = acceleration.y*7;// multiplication to give it a force

	//-----------------------------------
	// stop ball if not free
	//-----------------------------------
	if( !right && speed.x>0 ) speed.x = 0;
	if( !left && speed.x<0 ) speed.x = 0;
	if( !top && speed.y>0 ) speed.y = 0;
	
	if( !bottom && speed.y<0 && -speed.y/2>acceleration.y) speed.y = (int)( -speed.y/2); // to bounce
		
	//-----------------------------------
	// degrade ball acceleration of KEYS not pressed
	//-----------------------------------
	if( !key[KEY_RIGHT] && speed.x > 0 ) speed.x -= acceleration.x;
	if( !key[KEY_LEFT]   && speed.x < 0 ) speed.x += acceleration.x;
	if( !key[KEY_SPACE]   && speed.y > 0 ) speed.y -= acceleration.y;
	
	//-----------------------------------
	// Gravity acceleration
	//-----------------------------------
	if( bottom ) speed.y -= acceleration.y;
	
	//-----------------------------------
	// manage position of the ball
	//-----------------------------------
	position.x += speed.x;
	position.y -= speed.y;
	
	
}

BITMAP* Ball::render()
{
	return ball;
}
