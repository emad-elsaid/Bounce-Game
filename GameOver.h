#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <string>
#include <iostream>
#include <allegro.h>
using namespace std;

class GameOver
{
	private:
		BITMAP *bmp;
		string mfileName;
		int loadBmp();
	public:
		GameOver(string fileName);
		void render();
		void highcolor_fade_in(BITMAP *, int);
		void higher_fade_out(int);
};

#endif
