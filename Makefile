GCC = g++
LIBS = `allegro-config --libs`
CFLAGS = -c

all: cleanout Tile.o  Life.o Score.o Coins.o Level.o GameOver.o  Image.o Ball.o   Game.o Menu.o Speed.o Bounce.out rune clean 

cleanout:
	rm Bounce.out -f
Bounce.out:
	$(GCC) -o Bounce.out Main.cpp  Tile.o Coins.o Image.o GameOver.o Life.o Score.o Level.o Ball.o Game.o Menu.o Speed.o $(LIBS)
rune:
	./Bounce.out
Life.o:
	$(GCC) $(CFLAGS) Life.cpp 
	
Image.o:
	$(GCC) $(CFLAGS) Image.cpp
Coins.o:
	$(GCC) $(CFLAGS) Coins.cpp 
	
GameOver.o:
	$(GCC) $(CFLAGS) GameOver.cpp

Score.o:
	$(GCC) $(CFLAGS) Score.cpp 

Level.o:
	$(GCC) $(CFLAGS) Level.cpp

Ball.o:
	$(GCC) $(CFLAGS) Ball.cpp 

Game.o:
	$(GCC) $(CFLAGS) Game.cpp 

Menu.o:
	$(GCC) $(CFLAGS) Menu.cpp 
	
Speed.o:
	$(GCC) $(CFLAGS) Speed.cpp 

Tile.o:
	$(GCC) $(CFLAGS) Tile.cpp 

run:
	./Bounce.out
	
clean:
	rm Life.o
	rm Score.o
	rm Level.o
	rm Ball.o 
	rm Game.o
	rm Menu.o
	rm Speed.o
	rm Tile.o
	rm GameOver.o  
	rm Image.o
	rm Coins.o
