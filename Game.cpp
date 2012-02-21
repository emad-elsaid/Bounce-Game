#include "Game.h"

Game::Game( std::string Gtitle = "Allegro game" )
{
	title = Gtitle;
	fullscreen = false;
	w = 800;
	h = 600;
	colors = 32;
	FPS = 30;
	end_game = false;
	m_mode = MODE_MENU;
}
/* _____________________________________________________
 * start function starts the game with the specification required
 * _____________________________________________________
 * */
bool Game::start()
{
	allegro_init();
	install_keyboard();
	install_timer();
	install_mouse();
	set_color_depth( colors );
	
	if ( fullscreen )
	{
		if ( set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0 ) < 0 ) return false;
	}
	else
	{
		if ( set_gfx_mode( GFX_AUTODETECT_WINDOWED, w, h, 0, 0 ) < 0 ) return false;
	}
	
	set_window_title( title.c_str() );
	clear( screen );
	
	m_menu = new Menu();
	m_over = new GameOver("gameover.bmp");
	m_finished = new GameOver("finished.bmp");
	m_credits = new GameOver("credits.bmp");
	m_startLogo = new GameOver("startlogo.bmp");
	m_frame = create_bitmap( 800, 600);
	m_level = NULL;
	
	m_startLogo->render();
	do {			/* loop */
		input();		/* get input */
		process();	/* process it */
		rest(1000/FPS);
		output();		/* give output */
    } while ( ! end_game );	/* until the flag is set */
	
	return 0;
}

/* _____________________________________________________
 * ends the game by setting the flag to true
 * _____________________________________________________
 * */
void Game::end()
{
	end_game = true;
}

void Game::input()
{
	
}

void Game::process()
{
	
	switch ( m_mode )
	{
		// On menu running actions ============
		case MODE_MENU:     
			m_menu->proc();
			
			if( m_menu->startFlag )
			{
				m_mode = MODE_LEVEL;
				m_level = new Level( m_menu->get_level() );
				m_menu->reset();
			}
			else if( m_menu->quitFlag )
			{
				end();
			}
			else if( m_menu->creditsFlag )
			{
				m_mode = MODE_CREDITS;
				m_menu->reset();
			}
			
			if( key[KEY_ESC] ) end();
			
			break;
		
		// On Level running actions ============
		case MODE_LEVEL:
		    m_level->proc();
			
			if(m_level->m_isFinished)
			{
				if(m_level->m_number < m_menu->m_levels)
				{
					int lastLevel = m_level->m_number;
					Life L = *(m_level->m_life);
					Score S = *(m_level->m_score);
					S += 150;
					delete m_level;
					m_level = new Level(lastLevel+1);
					*(m_level->m_life) = L;
					*(m_level->m_score) = S;
				}
				else
				{
					clear_keybuf();
					m_mode = MODE_FINISH;
				}
			}
			if(m_level->m_isOver)
			{
				clear_keybuf();
				m_mode = MODE_OVER;
			}
			if( key[KEY_ESC] )
			{
				
				m_mode = MODE_MENU;
				rest( 1000 );
			}
			break;
		
		// On finished scene running actions ============
		case MODE_FINISH:
			m_finished->render(); 
			m_mode = MODE_MENU;
			break;
			
		// On gameover scene running actions ============
		case MODE_OVER :    
			m_over->render();
			m_mode = MODE_MENU;
			break;
			
		case MODE_CREDITS :
			m_credits->render();
			m_mode = MODE_MENU;
			break;
	}
}

void Game::output()
{
	switch ( m_mode )
	{
		
		case MODE_MENU:     
			m_frame = m_menu->render();
			vsync(); 
			blit( m_frame, screen,0,0,0,0 ,m_frame->w ,m_frame->h); 
			break;
			
		case MODE_LEVEL:    
			m_frame = m_level->render();
			vsync(); 
			blit( m_frame, screen,0,0,0,0 ,m_frame->w ,m_frame->h);
			break;
	}

}

void Game::set_w( unsigned int width )
{
	w = width;
}

void Game::set_h( unsigned int height )
{
	h = height;
}

unsigned int Game::get_w()
{
	return w;
}

unsigned int Game::get_h()
{
	return h;
}

Game::~Game()
{
	delete m_menu;
	if( m_level != NULL )
		delete m_level;
	delete m_over;
	delete m_finished;
}
