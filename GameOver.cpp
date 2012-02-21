#include "GameOver.h"

GameOver::GameOver(string fileName)
{
	mfileName = fileName;
	loadBmp();
}

int GameOver::loadBmp()
{
	bmp = load_bitmap(mfileName.c_str(), NULL);
	if(!bmp)
	{
		cout << "Error in File" << endl;
		destroy_bitmap(bmp);
		return -1;
	}
	else
		return 0;
}

void GameOver::render()
{
	 highcolor_fade_in( bmp, 9 );
	 rest(500);
	 clear_keybuf();
	 readkey();
	 higher_fade_out( 9 );
}

void GameOver::highcolor_fade_in(BITMAP * bmp_orig,int speed)
{
		 BITMAP* bmp_buff;
		  if((bmp_buff=create_bitmap(800,600)))
			{
				int a;
				if(speed<=0)speed=2;
				for(a=0;a<256;a+=speed)
				{
					clear(bmp_buff);
					set_trans_blender(0,0,0,a);
					draw_trans_sprite(bmp_buff,bmp_orig,0,0);
					vsync();
					blit(bmp_buff,screen,0,0,0,0,800,600);
				}
				destroy_bitmap(bmp_buff);
				
			}

	blit(bmp_orig,screen,0,0,0,0,800,600);

} //END OF FUNCTION.

void GameOver::higher_fade_out(int speed)
{
	BITMAP *bmp_orig,*bmp_buff;
	if((bmp_orig=create_bitmap(800,600)))
	{
		if((bmp_buff=create_bitmap(800,600)))
		{
		   int a;
		   blit(screen,bmp_orig,0,0,0,0,800,600);
			if(speed<=0)
				speed=2;
	
			for(int a=255-speed;a>0;a-=speed)
			{
				clear(bmp_buff);
				set_trans_blender(0,0,0,a);
				draw_trans_sprite(bmp_buff,bmp_orig,0,0);
				vsync();
				blit(bmp_buff,screen,0,0,0,0,800,600);

			 }
			destroy_bitmap(bmp_buff);
		}
    }
} 	
