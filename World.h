#ifndef __WORLD_H__
#define __WORLD_H__
#include "Player.h"
#include "WorldChunk.h"
#include "Tile.h"
class World{
public:
	World(int seed);
	~World();
	void draw(sf::RenderWindow & window);
	void update(sf::Time elapsed);
	Player & getPlayer();
private:
	int seed;
	Player player;
	std::map<std::pair<int,int>, WorldChunk *> chunks;
	std::vector<WorldChunk *> loadedChunks;
	std::pair<int,int> getPlayerChunk();
	std::pair<int,int> lastPlayerChunk;
	void generateChunk(std::pair<int,int> key); //Generate tiles around when the player moves to a new chunk.
	void generateChunk(std::pair<int,int> root, int offsetx, int offsetY);
	WorldChunk *  getChunkWithOffset(int offsetX, int offsetY);
	bool isPlayerNearTop();
	bool isPlayerNearBottom();
	bool isPlayerNearLeft();
	bool isPlayerNearRight();
	void unloadChunks(std::pair<int,int> newPos);
	void freeChunk(std::pair<int,int> key);

};
#endif