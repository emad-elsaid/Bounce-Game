#include "Speed.h"
///////////////////////////////////////////////////
     Speed :: Speed ( int m )
   {
          max   = m ;
          value = 0 ;           
   }
   
///////////////////////////////////////////////////   
void Speed :: operator ++ ( )
   {
         value ++ ;
         
         if ( value >= max ) value = 0 ;
 
   }
 
///////////////////////////////////////////////////

void Speed :: operator -- ( )  
   {
         value -- ;
         
         if ( value < 0 )  value = max ;
     
   }
///////////////////////////////////////////////////

bool Speed :: ok( ) 
   {
    	return ( value == 0 );
   }
