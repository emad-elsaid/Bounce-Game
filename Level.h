#ifndef LEVEL_H
#define LEVEL_H

#include "Ball.h"
#include "Tile.h"
#include "Image.h"
#include "Life.h"
#include "Score.h"
#include "Coins.h"

#include <allegro.h>
class Level
{
	public:
		bool m_isFinished;
		bool m_isOver;
		int m_number;
		Level(int L);
		~Level();
		void proc();
		BITMAP *render();
		Score *m_score;
		Life *m_life;
	private:
		BITMAP *m_frame;
		Ball *m_ball;
		Tile *m_enemy;
		Tile *m_tile;
		Tile *m_door;
		Image *m_bg;
		Image *m_dash;
		Coins *m_coins;
		Coins *m_lives;
		Vector m_lastBall;
		bool collision(BITMAP* ,BITMAP*);
		Vector getNonTrans(BITMAP*);
};

#endif /* LEVEL_H */ 
