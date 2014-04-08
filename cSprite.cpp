/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	cSprite::spritePos.x = 0.0f;
	cSprite::spritePos.y = 0.0f;
	cSprite::spritePos.z = 0.0f;
	cSprite::setTexture(new cD3DXTexture());
	cSprite::setSpriteScaling(1.0f, 1.0f);
	cSprite::setSpriteScalingRotation(0.0f);
	cSprite::setSpriteRotation(0.0f);
	//cSprite::update();
}
cSprite::cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename) // Constructor
{
	D3DXVECTOR2 translation = D3DXVECTOR2(0,0);
	cSprite::setSpritePos(sPosition);
	//cSprite::setSpritePos2D(sPosition);
	cSprite::setTexture(pd3dDevice, theFilename);
	cSprite::spriteTexture->setTextureInfo(theFilename);
	cSprite::setTranslation(translation);
	cSprite::setSpriteCentre();
	cSprite::setSpriteScaling(1.0f, 1.0f);
	cSprite::setSpriteScalingRotation(0.0f);
	cSprite::setSpriteRotation(0.0f);
	D3DXMatrixIdentity( &spriteTransformMatrix );
	cSprite::update();
}
/*
=================
- Destructor 
=================
*/
cSprite::~cSprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

D3DXVECTOR3 cSprite::getSpritePos()  // Return the sprites current position
{
	return cSprite::spritePos;
}
/*
=================
- set the position of the sprite.
=================
*/

void cSprite::setSpritePos(D3DXVECTOR3 sPosition)  // set the position of the sprite
{
	cSprite::spritePos = sPosition;
	cSprite::setSpritePos2D(sPosition);
}
/*
=================
- Return the sprites current 2D position.
=================
*/
D3DXVECTOR2 cSprite::getSpritePos2D()   // Return the sprites current 2D position
{
	return cSprite::spritePos2D;
}

/*
=================
- set the 2D position of the sprite.
=================
*/
void cSprite::setSpritePos2D(D3DXVECTOR3 sPosition)  // set the 2D position of the sprite
{
	cSprite::spritePos2D.x = sPosition.x;
	cSprite::spritePos2D.y = sPosition.y;
}

/*
=================
- Return the sprites translation.
=================
*/

D3DXVECTOR2 cSprite::getTranslation() 		// Return the sprites translation
{
	return cSprite::spriteTranslation;
}

/*
=================
- set the position of the sprite.
=================
*/
void cSprite::setTranslation (D3DXVECTOR2 Translation) 		// set the translation for the sprite
{
	cSprite::spriteTranslation = Translation;
}

/*
=================
- Return the sprites current image.
=================
*/

LPDIRECT3DTEXTURE9 cSprite::getTexture()  // Return the sprites current image
{
	return cSprite::spriteTexture->getTexture();
}
/*
=================
- set the image of the sprite.
=================
*/
void cSprite::setTexture(cD3DXTexture* aSpriteTexture)  // set the image of the sprite
{
	cSprite::spriteTexture = aSpriteTexture;
}

void cSprite::setTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename)  // set the image of the sprite
{
	cSprite::spriteTexture->createTexture(pd3dDevice, theFilename);
	cSprite::spriteTexture->setTextureInfo(theFilename);
}
/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setSpriteCentre()      // set the centre of the sprite for rotation
{
	D3DXIMAGE_INFO aTextureInfo;
	aTextureInfo = cSprite::spriteTexture->getTextureInfo();
	cSprite::spriteCentre.x = (float)aTextureInfo.Width/2;
	cSprite::spriteCentre.y = (float)aTextureInfo.Height/2;
}
/*
=================
- set the image of the sprite.
=================
*/
D3DXVECTOR2 cSprite::getSpriteCentre()      // return the centre of the sprite for rotation
{
	return cSprite::spriteCentre;
}

/*
=================
- set the scaling factor.
=================
*/

void cSprite::setSpriteScaling(float x, float y)      // set the scaling factor
{
	cSprite::spriteScaling.x = x;
	cSprite::spriteScaling.y = y;
}
/*
=================
- return the scaling factor.
=================
*/

D3DXVECTOR2 cSprite::getSpriteScaling()      // return the scaling factor
{
	return cSprite::spriteScaling;
}

/*
=================
- set the scaling factor rotation.
=================
*/

void cSprite::setSpriteScalingRotation(float angle)      // set the scaling factor rotation
{
	cSprite::spriteScalingRotation = D3DXToRadian(angle);
}
/*
=================
- return the scaling factor rotation.
=================
*/

float cSprite::getSpriteScalingRotation()      // return the scaling factor rotation
{
	return cSprite::spriteScalingRotation;
}

/*
=================
- set the rotation for the sprite.
=================
*/

void cSprite::setSpriteRotation(float angle)      // set the rotation for the sprite
{
	cSprite::spriteRotation = D3DXToRadian(angle);
}
/*
=================
- return the rotation for the sprite.
=================
*/

float cSprite::getSpriteRotation()      // return the rotation for the sprite
{
	return cSprite::spriteRotation;
}

/*
=================
- set the transformation matrix for the sprite.
=================
*/

void cSprite::setSpriteTransformMatrix(D3DXMATRIX aMatrix, D3DXVECTOR2 aScalingCenter, float aScalingRotation, D3DXVECTOR2 aScaling, D3DXVECTOR2 aRotationCenter, float Rotation, D3DXVECTOR2 aTranslation)      // set the transformation matrix for the sprite
{
	D3DXMatrixTransformation2D(&aMatrix, &aScalingCenter, aScalingRotation, &aScaling, &aRotationCenter, Rotation, &aTranslation);
}
/*
=================
- return the transformation matrix for the sprite.
=================
*/

D3DXMATRIX cSprite::getSpriteTransformMatrix()      // return the transformation matrix for the sprite
{
	return cSprite::spriteTransformMatrix;
}
/*
=================
- update the position etc of the sprite.
=================
*/

void cSprite::update() 							// update the position etc of the sprite
{
	D3DXMatrixTransformation2D(&spriteTransformMatrix,
		&cSprite::getSpriteCentre(),
		cSprite::getSpriteScalingRotation(),
		&cSprite::getSpriteScaling(),
		&cSprite::getSpriteCentre(),
		cSprite::getSpriteRotation(),
		&cSprite::getSpritePos2D());
	cSprite::setBoundingRect(&boundingRect);
}
/*
=================
- Determine the bounding rectangle for the sprite.
=================
*/

void cSprite::setBoundingRect(RECT* pRect)
{
	D3DXVECTOR3 sPos = getSpritePos();
	int sImageWidth = getSTWidth();
	int sImageHeight = getSTHeight();
	SetRect(pRect, (int)sPos.x, (int)sPos.y, (int)(sImageWidth+sPos.x), (int)(sImageHeight+sPos.y));
}
/*
=================
- Return the bounding rectangle for the sprite.
=================
*/
RECT cSprite::getBoundingRect()		// Return the bounding rectangle for the sprite
{
	return cSprite::boundingRect;
}
/*
=================
- Check for collisions.
=================
*/

bool cSprite::collidedWith(RECT thisSpriteRect, RECT otherSpriteRect)
{
	//if(!pAnotherSprite)
		//return 0;
	// declare rectangles for intersection test
	RECT tempRect;

	// determine the bounding rectangle for this Sprite and the other
	// getBoundingRect(&thisSpriteR);
	// anotherSpriteR
	// pAnotherSprite->getBoundingRect(&anotherSpriteR);

	// perform the intersection test
	if(IntersectRect(&tempRect,&thisSpriteRect, &otherSpriteRect))
		return true;
	else
		return false;
}
/*
=================
- Return the bounding rectangle for the sprite.
=================
*/
int cSprite::getSTWidth()						// Return width of texture;
{
	return cSprite::spriteTexture->getTWidth();
}
/*
=================
- Return the bounding rectangle for the sprite.
=================
*/
int cSprite::getSTHeight()						// Return height of texture;
{
	return cSprite::spriteTexture->getTHeight();
}
/*
=================
- Return the bounding rectangle for the sprite.
=================
*/
bool cSprite::insideRect(RECT thisSprite, POINT aPoint) 						// Return true if a point is within the rectangle
{
	if ((aPoint.x >= thisSprite.left-20) &&
		(aPoint.x <= thisSprite.right) &&
		(aPoint.y >= thisSprite.top-60 ) &&		//Fix for bounding box bug
		(aPoint.y <= thisSprite.bottom))
	{
		return true;
	}
	else
	{
		return false;
	}
}