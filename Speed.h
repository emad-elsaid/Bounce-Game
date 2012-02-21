#ifndef SPEED_H
#define SPEED_H

class Speed
{
      private:
              int  value ;
              int  max ;

      public:
              Speed( int ) ;
              void operator ++ ( ) ;
              void operator -- ( ) ;
              bool ok( ) ;


};

#endif
