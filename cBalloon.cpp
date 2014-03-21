/*
=================
cBalloon.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBalloon.h"
/*
=================
- Data constructor initializes the cBalloon to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cBalloon::cBalloon(): cSprite() 			// Default constructor
{
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
cBalloon::cBalloon(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)  // Constructor
{
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
/*
=================
- update the position etc of the sprite.
=================
*/
void cBalloon::update(float deltaTime) 					// update the balloons position based on the translation
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cBalloon::getSpritePos2D() + (cBalloon::getTranslation())*deltaTime;
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cBalloon::setSpritePos(tempV3);
	cSprite::update();
}
/*
=================
- Returns the current direction of the sprite.
=================
*/
eDirection cBalloon::getDirection()       // Rturns the current direction of the sprite
{
	return cBalloon::mDirection;
}
/*
=================
- Sets the current direction for the sprite.
=================
*/
void cBalloon::setDirection(eDirection theDirection)  // Sets the current direction for the sprite.
{
	cBalloon::mDirection = theDirection;
}
