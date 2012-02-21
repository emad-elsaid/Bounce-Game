#include "Level.h"
#include <sstream>
#include <iostream>
using namespace std;
Level::Level(int L)
{
	// loading main level tiles
	stringstream s;
	s << "level" << L << ".bmp" ;
	m_tile = new Tile( s.str() );
	
	stringstream door;
	door << "door" << L << ".bmp" ;
	m_door = new Tile( door.str() );
	
	stringstream enemy;
	enemy << "enemy" << L <<".bmp";
	m_enemy = new Tile( enemy.str() );
	
	stringstream coins;
	coins << "coins" << L <<".bmp";
	m_coins = new Coins( coins.str() );
	
	stringstream lives;
	lives << "life"<< L << ".bmp";
	m_lives = new Coins( lives.str() );
	
	// loading images and creating objects
	m_bg = new Image("bg1.bmp");
	m_dash = new Image("dashboard.bmp");
	m_life = new Life(3);
	m_score = new Score();
	
	// creating Ball object
	m_ball = new Ball();
	m_ball->position.x = 50;
	m_ball->position.y = 20;
	
	m_lastBall = m_ball->position;
	
	m_frame = create_bitmap(800,600);
	m_isOver = false;
	m_isFinished = false;
	m_number = L ;
	
	
}


void Level::proc()
{
	BITMAP *enemyBox = m_enemy->getBox(m_ball->position.x,m_ball->position.y,m_ball->w,m_ball->h);
	if(collision(m_ball->ball,enemyBox))
	{
		rest( 1000 );
		if(m_life->isOver())
		{
			m_isOver = true;
		}
		else
		{
			(*m_life)--;
			delete m_ball;
			m_ball = new Ball();
			m_lastBall = m_ball->position;
		}
	}
	
	// get the surroundings collision to detect the free sides
	BITMAP* t = m_tile->getBox( m_ball->position.x+m_ball->ball->w/4, m_ball->position.y, m_ball->ball->w/2, m_ball->ball->h/4 );
	bool top = collision( t, m_ball->t );
	
	BITMAP* l = m_tile->getBox( m_ball->position.x, m_ball->position.y+m_ball->ball->h/4, m_ball->ball->w/4, m_ball->ball->h/2 );
	bool left = collision( l, m_ball->l );
	
	BITMAP* b = m_tile->getBox( m_ball->position.x+m_ball->ball->w/4, m_ball->position.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	bool bottom = collision( b, m_ball->b );
	
	BITMAP* r = m_tile->getBox( m_ball->position.x+m_ball->ball->w*3/4, m_ball->position.y+m_ball->ball->h/4, m_ball->ball->w/4, m_ball->ball->h/2 );
	bool right = collision( r, m_ball->r );
	
	// process the ball
	m_ball->proc( !top, !left, !bottom, !right );
	
	// if it passed the wall then bring it back on it ( Bottom && Top )
		int step = ( m_ball->position.y > m_lastBall.y )? 1 : -1;
		BITMAP* slice;
		while( m_ball->position.y != m_lastBall.y )
		{
			
			if( step == 1 )
			{
				b = m_tile->getBox( m_lastBall.x+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
				slice = m_ball->b;
			}
			else
			{
				b = m_tile->getBox( m_lastBall.x+m_ball->ball->w/4, m_lastBall.y, m_ball->ball->w/2, m_ball->ball->h/4 );
				slice = m_ball->t;
			}
			
			if( collision( b, slice )== true )
				break;
				
			m_lastBall.y += step;	
		}
	// if it passed the wall then bring it back on it ( Right && Left )
		step = ( m_ball->position.x > m_lastBall.x )? 1 : -1;
		while( m_ball->position.x != m_lastBall.x )
		{
			
			if( step == 1 )
			{
				l = m_tile->getBox( m_lastBall.x+m_ball->ball->w*3/4, m_lastBall.y+m_ball->ball->h/4, m_ball->ball->w/4, m_ball->ball->h/2 );
				slice = m_ball->r;
			}
			else
			{
				l = m_tile->getBox( m_lastBall.x, m_lastBall.y+m_ball->ball->h/4, m_ball->ball->w/4, m_ball->ball->h/2 );
				slice = m_ball->l;
			}
			
			if( collision( l, slice )== true )
				break;
				
			m_lastBall.x += step;	
		}

	b = m_tile->getBox( m_lastBall.x+2+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	l = m_tile->getBox( m_lastBall.x+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	slice = m_ball->b;
	
	// slop handleing
	b = m_tile->getBox( m_lastBall.x+2+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	l = m_tile->getBox( m_lastBall.x+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	slice = m_ball->b;
	if( collision( l, slice ) && !collision( b, slice ) )
	{
		m_lastBall.x += 2;
		if( m_ball->speed.y < 0 ) m_ball->speed.y = 0;
		// thats a fake jumb ( work around ) for slops
		if( key[KEY_SPACE] ) m_ball->speed.y = m_ball->acceleration.y*7;
	}
	b = m_tile->getBox( m_lastBall.x-2+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	l = m_tile->getBox( m_lastBall.x+m_ball->ball->w/4, m_lastBall.y+m_ball->ball->h*3/4, m_ball->ball->w/2, m_ball->ball->h/4 );
	slice = m_ball->b;
	if( collision( l, slice ) && !collision( b, slice ) )
	{
		m_lastBall.x -= 2;
		if( m_ball->speed.y < 0 ) m_ball->speed.y = 0;
		// thats a fake jumb ( work around ) for slops
		if( key[KEY_SPACE] ) m_ball->speed.y = m_ball->acceleration.y*7;
	}
	
	
	m_ball->position = m_lastBall;
	BITMAP *doorBox = m_door->getBox(m_ball->position.x,m_ball->position.y,m_ball->w,m_ball->h);
	if(collision(m_ball->ball,doorBox))
	{
		m_isFinished = true;
	}
	

	BITMAP *coinsBox = m_coins->getBox(m_ball->position.x,m_ball->position.y,m_ball->w,m_ball->h);
	if(collision(m_ball->ball,coinsBox))
	{
		Vector V = getNonTrans(coinsBox);
		m_coins->transparent(V.x + m_ball->position.x,V.y + m_ball->position.y);
		*(m_score) += 100;
		if((int)m_score->getValue()%1000==0 && m_score->getValue()!=0)
		{
			*(m_score)+=100;
			(*(m_life))++;
		}
		
	}
	
	BITMAP *livesBox = m_lives->getBox(m_ball->position.x,m_ball->position.y,m_ball->w,m_ball->h);
	if(collision(m_ball->ball,livesBox))
	{
		Vector V = getNonTrans(livesBox);
		m_lives->transparent(V.x + m_ball->position.x,V.y + m_ball->position.y);
		(*(m_life))++;
		
	}
	//to change the ball image
	enemyBox = m_enemy->getBox(m_ball->position.x,m_ball->position.y,m_ball->w,m_ball->h);
	if(collision(m_ball->ball,enemyBox))
	{
		destroy_bitmap( m_ball->ball );
		destroy_bitmap( m_ball->t );
		destroy_bitmap( m_ball->l );
		destroy_bitmap( m_ball->b );
		destroy_bitmap( m_ball->r );
		m_ball->t = m_ball->l = m_ball->r = m_ball->b = NULL;
		m_ball->ball = load_bitmap( "ball_destroyed.bmp" , NULL );
	}
}

BITMAP *Level::render()
{
	clear(m_frame);
	int x;
	if ( m_ball->position.x < 800/2)
		x = 0;
	else if(m_ball->position.x > m_tile->w - 800/2)
	{
		x = m_tile->w - 800;
	} 
	else
		x = m_ball->position.x - 800/2;
	
		
	int y ;
	if ( m_ball->position.y < 600/2)
		y = 0;
	else if(m_ball->position.y > m_tile->h - 600/2)
	{
		y = m_tile->h - 600;
	} 
	else
		y = m_ball->position.y - 600/2;
		
	draw_sprite( m_frame, m_bg->render(), 0, 0);
	draw_sprite(m_frame , m_door->getBox(x,y,800,600), 0, 0);
	draw_sprite( m_frame, m_tile->getBox(x,y,800,600), 0, 0);
	draw_sprite(m_frame,m_enemy->getBox(x,y,800,600), 0, 0);
	draw_sprite(m_frame, m_ball->render(), m_ball->position.x-x , m_ball->position.y-y );
	draw_sprite(m_frame,m_coins->getBox(x,y,800,600),0,0); 
	draw_sprite(m_frame,m_lives->getBox(x,y,800,600),0,0); 
	draw_sprite(m_frame, m_dash->render(), 0, 0 );
	
	BITMAP *scoreFrame = m_score->render( 100, 30);
	draw_sprite( m_frame, scoreFrame, 90, 10);
	destroy_bitmap(scoreFrame);
	
	BITMAP *lifeFrame = m_life->render(100, 30);
	draw_sprite( m_frame, lifeFrame, 280, 10);
	destroy_bitmap(lifeFrame);
	
	textprintf_centre_ex( m_frame, font, 560, 25, makecol(0, 100, 243), -1, "%i", m_number );
	return m_frame;
	
}	
	
bool Level::collision(BITMAP* img1,BITMAP* img2)
{
	// if faild to pass images tell there is no collision
	if( img1==NULL || img2==NULL ) return false;
		
	for( int y=0; y < img1->h; y++ )
	{
		for(  int x=0; x < img1->w; x++ )
		{
			if( _getpixel32( img1, x, y )!=16711935 && _getpixel32( img2, x, y )!=16711935 )
				return true;
		}
	}

	return false;
}

Vector Level::getNonTrans(BITMAP* B)
{
	Vector V ;
	if( B == NULL )return V;
	
	for( int y=0; y < B->h; y++ )
	{
		for(  int x=0; x < B->w; x++ )
		{
			 _getpixel32( B, x, y );
			
			if( _getpixel32( B, x, y ) != 16711935  )
			{
				Vector V ;
				V.x = x;
				V.y = y;
				return V;
			}
		}
	}

	return V;
}
Level::~Level()
{
	//if( m_bg )
		delete m_bg;
	//if( m_ball ) 
		delete m_ball;
	//if( m_tile ) 
		delete m_tile;
	//if( m_score ) 
		delete m_score;
	//if( m_life ) 
		delete m_life;
		
		delete m_coins;
	if( m_frame != NULL )
		destroy_bitmap(m_frame);
}
