#ifndef GAME_H
#define GAME_H

#include <string>
#include <allegro.h>
#include "Menu.h"
#include "Level.h"
#include "GameOver.h"

#define MODE_MENU 0
#define MODE_LEVEL 1
#define MODE_FINISH 2
#define MODE_OVER 3
#define MODE_CREDITS 4

class Game
{
	private:
		std::string title;
		unsigned int w;
		unsigned int h;
		unsigned int colors;
		unsigned int FPS;
		int m_mode;
		BITMAP *m_frame;
		bool end_game;
		Menu *m_menu;
		Level *m_level;
		GameOver *m_finished;
		GameOver *m_over;
		GameOver *m_credits;
		GameOver *m_startLogo;
	public:
		Game( std::string );
		bool start();
		void end();
		void input();
		void process();
		void output();
		void set_w( unsigned int );
		void set_h( unsigned int );
		bool fullscreen;
		unsigned int get_w();
		unsigned int get_h();
		virtual ~Game();
};

#endif
