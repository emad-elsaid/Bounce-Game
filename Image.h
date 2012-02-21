#ifndef IMAGE_H
#define IMAGE_H
#include <allegro.h>
#include <string>

class Image
{
	private:
		BITMAP* img;
	public:
		Image(std::string);
		~Image();
		BITMAP* render();

		
}; //End Of Class.

#endif
