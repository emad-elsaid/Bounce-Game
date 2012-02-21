#ifndef MENU_H
#define MENU_H


 
class Menu
{	
	private:
	    int option;
        int level;
	public:
		int m_levels;
		bool startFlag;
		bool quitFlag;
		bool creditsFlag;
		BITMAP* bg;
		BITMAP* ball;
		int num_options;
		
	Menu();
	~Menu();
	void reset();
    void start();
    void quit();
	void credits();
    int  proc();
	int get_level();
    BITMAP* render();		
}; //END OF CLASS.

#endif
