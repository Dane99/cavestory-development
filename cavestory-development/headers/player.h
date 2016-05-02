#pragma once
#include "animatedsprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite{
public:
	Player();
	Player(Graphics &graphics, float x, float y);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	/* void moveLeft
	 * Moves the player left by -dx
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx
	 */
	void moveRight();

	/* void stopMoving
	 * Stops moving the player and plays the idle animation
	 */
	void stopMoving();
private:
	float _dx, _dy;

	Direction _facing;
};