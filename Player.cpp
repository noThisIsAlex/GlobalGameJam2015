#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(){

	//if (!texture.loadFromFile("player.png")) {
	if (!texture.loadFromFile("player.png")) {
		// error!
		std::cout << "unable to load player sprite" << std::endl;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sf::Vector2u textureSize = texture.getSize();
	sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);

	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::A, TurnCounter));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::W, Forward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::D, TurnClockwise));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::S, Backward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::Left, TurnCounter));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::Up, Forward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::Right, TurnClockwise));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::S, Backward));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::Space, SuperBoost));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::I, SuperBoost));
	/*
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::J, StrafeLeft));
	map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::L, StrafeRight));
	*/
	

	// Keys to swap
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::A, Flamethrower));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::S, Lazer));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::L, Shield));
	//map.insert(std::pair<sf::Keyboard::Key, Action>(sf::Keyboard::SemiColon, LimitBreak));

	keyToSwapIn = sf::Keyboard::Unknown;
	sfxBuffer.loadFromFile("falco041.wav");
	sfx.setBuffer(sfxBuffer);
	sfx.setVolume(40);
	mute = false;
}
Player::~Player(){

}

void Player::move(const sf::Vector2<float>& dir){
	pos += dir;
	sprite.setPosition(pos.x, pos.y);
}

void Player::draw(sf::RenderWindow & window, sf::Shader* shader){
	window.draw(sprite,shader);
}
void Player::turn(float deg){
	angle += deg;
	sprite.setRotation(angle+90);
}

const sf::Vector2<float> & Player::getCenter(){
	return pos;
}

sf::Vector2f Player::forward(){
	//moving = false;	
	//dashing = false;
	sprite.setRotation(angle+90);
	return sf::Vector2f
		((float)cos(angle*1.0/RAD2DEGf) * RAD2DEGf,(float)sin(angle*1.0/RAD2DEGf) * RAD2DEGf);
}
void Player::toggleSound()
{
	mute = !mute;
}
void Player::setSpeedMultiplier(float multiplier){
	this->speedMult = multiplier;
}
void Player::doAction(sf::Keyboard::Key keyStroke) {
	switch(map[keyStroke]) {
		
		case TurnCounter:
			// turn counter-clockwise
            turn(-7);
			break;
		case Forward:
			// move forward
            move(forward() * speedMult);
            moving = true;
			break;
		case Backward:
			// move backwards
            move(forward() * -0.05f);
			break;
		case TurnClockwise:
			// turn clockwise
            turn(7);
			break;
		case Flamethrower:
			// TODO flamethrower
			break;
		case Lazer:
			// TODO lazer
			break;
		case Shield:
			// TODO shield
			break;
		case LimitBreak:
			// TODO LIMIT BREAK
			break;
		case SuperBoost:
			dashing=true;
			move(forward() * 1.0f);
			if(!mute)
				sfx.play();
			//flipEffect();
			break;
		case StrafeLeft:
			//move(left() * 0.3f);
			dashing = true;
			turn(-12);
			break;
		case StrafeRight:
			//move(left() * -0.3f);
			dashing = true;
			turn(12);
			break;
		default:
			break;
	}
}

void Player::swapKey(sf::Keyboard::Key keyToSwapOut) {
	Action actionToSwapOut = map[keyToSwapOut];

	map[keyToSwapOut] = map[keyToSwapIn];
	map[keyToSwapIn] = actionToSwapOut;

	keyToSwapIn = sf::Keyboard::Unknown;
}

void Player::swapOrDoAction(sf::Keyboard::Key keyStroke) {
	doAction(keyStroke);
    /*
    if (keyToSwapIn == sf::Keyboard::Unknown) {
        doAction(keyStroke);
    } else {
        swapKey(keyStroke);
    }
    */
}
sf::Vector2f Player::left(){
	sf::Vector2f fwd = forward();
	sf::Vector2f left = sf::Vector2f(
		(cos(M_PI/2)*fwd.x + sin(M_PI/2)*fwd.y),
		(-sin(M_PI/2)*fwd.x + cos(M_PI/2)*fwd.y));
	return left;
}

float Player::getAngle() {
	return angle;
}

bool Player::isMoving(){
	return moving;
}
bool Player::isDashing(){
	return dashing;
}

void Player::resetMoveState(){
	moving = false;
	dashing = false;
}
void Player::setColor(sf::Color c){
	sprite.setColor(c);
}

void Player::flipEffect() {
	while(sprite.getScale().x > MIN_SCALE)
		sprite.scale(0.8,1.0);

}

sf::Sprite& Player::getSprite()
{
	return sprite;
}
