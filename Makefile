SFMLLink=game
SFMLLib= -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
linux:
	g++ -O3  main.cpp Camera.cpp Player.cpp LinearBullet.cpp Tile.cpp WorldChunk.cpp World.cpp Particle.cpp StartPoint.cpp ArrowIndicator.cpp FlavorText.cpp -o $(SFMLLink) $(SFMLLib)
