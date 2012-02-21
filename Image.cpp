#include "Image.h"

Image::Image(std::string filename)
{
	 img=load_bitmap(filename.c_str() ,NULL);
}
Image::~Image()
{
	if( img )
		destroy_bitmap( img );
}
BITMAP* Image::render()
{
		
		return img;	
}
