/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CSPRITE_H
#define _CSPRITE_H
#include "cD3DXTexture.h"

class cSprite
{
private:
	D3DXVECTOR3 spritePos;
	D3DXVECTOR2 spritePos2D;
	D3DXVECTOR2 spriteTranslation;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 spriteScaling;
	float spriteScalingRotation;
	float spriteRotation;
	D3DXMATRIX spriteTransformMatrix;
	cD3DXTexture* spriteTexture;
	RECT boundingRect;

public:
	cSprite();			// Default constructor
	cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	~cSprite();			// Destructor
	D3DXVECTOR3 getSpritePos();  // Return the sprites current position
	void setSpritePos(D3DXVECTOR3 sPosition); // set the position of the sprite
	D3DXVECTOR2 getSpritePos2D();  // Return the sprites current 2D position
	void setSpritePos2D(D3DXVECTOR3 sPosition); // set the 2D position of the sprite
	D3DXVECTOR2 getTranslation();		// Return the sprites translation
	void setTranslation (D3DXVECTOR2 Translation);		// set the translation for the sprite
	LPDIRECT3DTEXTURE9 getTexture();  // Return the sprites current image
	void setTexture(cD3DXTexture* aSpriteTexture);  // set the image of the sprite
	void setTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);  // set the image of the sprite
	void setSpriteCentre();      // set the centre of the sprite for rotation
	D3DXVECTOR2 getSpriteCentre();      // return the centre of the sprite for rotation
	void setSpriteScaling(float x, float y);      // set the scaling factor
	D3DXVECTOR2 getSpriteScaling();      // return the scaling factor
	void setSpriteScalingRotation(float angle);      // set the scaling factor rotation
	float getSpriteScalingRotation();      // return the scaling factor rotation
	void setSpriteRotation(float angle);      // set the rotation for the sprite
	float getSpriteRotation();      // return the rotation for the sprite
	void setSpriteTransformMatrix(D3DXMATRIX aMatrix, D3DXVECTOR2 aScalingCenter, float aScalingRotation, D3DXVECTOR2 aScaling, D3DXVECTOR2 aRotationCenter, float Rotation, D3DXVECTOR2 aTranslation);      // set the transformation matrix for the sprite
	D3DXMATRIX getSpriteTransformMatrix();      // return the transformation matrix for the sprite
	void update();							// update the position etc of the sprite
	void setBoundingRect(RECT* pRect);		// Determine the bounding rectangle for the sprite
	RECT getBoundingRect();		// Determine the bounding rectangle for the sprite
	bool collidedWith(RECT thisSprite, RECT otherSpritePos);	// Check for collisions
	int getSTWidth();						// Return width of texture;
	int getSTHeight();						// Return height of texture;
	bool insideRect(RECT thisSprite, POINT aPoint);						// Return true if a point is within the rectangle
};
#endif