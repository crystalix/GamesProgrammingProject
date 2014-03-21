/*
=================
cExplosion.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CEXPLOSION_H
#define _CEXPLOSION_H
#include "cSprite.h"

class cExplosion : public cSprite
{
private:
	bool mActive;
	int mNoFrames;
	int mCurrentFrame;
	RECT mSourceRect;
	float mRate;

public:
	cExplosion(D3DXVECTOR3 sPosition, cD3DXTexture* aTexture); 	// Default constructor
	cExplosion();
	cExplosion(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	void update(float dt);					// update the balloons position based on the translation
	RECT getSourceRect();					// Return the current segment of the sprite sheet to draw.
	int getCurrentFrame();					// Return the current frame.
	void setActive(bool sActive);			// Set the sprite to active.
	bool isActive();						// Determine if the sprite is active.
};
#endif