#include<allegro.h>
#include "Menu.h"

Menu::Menu()
	{
		reset();
		bg = load_bitmap("ball.bmp",NULL);          //Background Image.
	    ball = load_bitmap("ballsprit.bmp",NULL);	//Ball Image.
		m_levels = 6;	
		num_options = 4;
	}

void Menu::reset()
{
	    option			= 1;
        level				= 1;
		startFlag 		= false;
		quitFlag 		= false;
		creditsFlag 	= false;

}
Menu::~Menu()
{
		destroy_bitmap( bg );
		destroy_bitmap( ball );

}
void Menu::start()
	{
		startFlag = true;
	}
void Menu::quit()
	{
		quitFlag = true;
		
	}
	int Menu::get_level()
	{
		
		return  level;
		
	}
void Menu::credits()
{
	creditsFlag = true;
}
	/*==================== PROCESS =======================*/ 
int Menu::proc()
	{
		if(key[KEY_ENTER] && option==1 )
			start();
			
		if(key[KEY_RIGHT] && option==2 )
		{
		    ++level;
			rest(200);
		}	
		if(key[KEY_LEFT] && option==2 )
		{
		 	--level;
			rest(200);
		}
		
		if(level<1)
			level = m_levels;
			
		if(level>m_levels)
			level = 1;	
		
		if(key[KEY_ENTER] && (option==3) )
			credits();
			
		if(key[KEY_ENTER] && (option==4) )
		   quit();
		   
		if(key[KEY_DOWN])
		{
			++option;
			rest(90);
		}
		
		if(key[KEY_UP])
		{
			--option;
			rest(90);
		}
		
		if(option>num_options)
			option=1;
		
		if(option<=0)
			option=num_options;

		
		 return option;
	}
//=============================================
// Render Function to blit Background Image.     
// Draw The Ball In The New Position.            
//=============================================
BITMAP* Menu::render()
	{
		BITMAP* buffer=create_bitmap(bg->w,bg->h);
		blit(bg, buffer, 0, 0, 0, 0, bg->w, bg->h);		
		draw_sprite( buffer, ball, 75, 225+option*70);
		textprintf_ex(buffer, font, 265, 385, makecol(0, 0, 0),
              -1, "<- %d ->",level );

		return buffer;
		
		
	}
