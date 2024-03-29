#ifndef __WORLD_CHUNK__
#define __WORLD_CHUNK__
#include "Tile.h"
#include "ChunkType.h"
#include <SFML/Graphics.hpp>
#define CHUNK_SIZE 16


class WorldChunk{

public:

	WorldChunk(TYPE wall, int x, int y);
	WorldChunk(TYPE wall, int x, int y, sf::Color tileColor);
	~WorldChunk();
	void startDeallocationAnimation();
	void startDeallocationAnimation(sf::Vector2f startingPosition, float speed);
	void colorTiles(sf::Vector2f startingPosition, float speed,sf::Color color);
	void forceColorTiles(sf::Vector2f startingPosition, float speed,sf::Color color);
	
	bool isSafe();
	bool isNewLevel();
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow & window, sf::Shader* shader = NULL);
	int x;
	int y;
	Tile & getTile(int i, int j);
	bool isWall;
	TYPE getType;

private:
	TYPE myType;
	Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
	bool isBeingDestroyed = false;

};
#endif