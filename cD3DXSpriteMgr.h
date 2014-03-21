/*
=================
cD3DXSpriteMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DXSpriteMgr class
=================
*/
#ifndef _CD3DXSPRITEMGR_H
#define _CD3DXSPRITEMGR_H
#include "GameConstants.h"

class cD3DXSpriteMgr
{
private:
	static cD3DXSpriteMgr* pInstance;
	LPD3DXSPRITE dxSpriteRenderer;    // D3DXSprite renderer object
	cD3DXSpriteMgr();					// constructor
public:
	// using the singleton design pattern (Meyers Singleton) as the design requires only one instance of this class
	static cD3DXSpriteMgr* getInstance();
	bool initD3DXSpriteMgr(LPDIRECT3DDEVICE9 pd3dDevice);       // Initialise cD3DManager and create Direct3D object
	void beginDraw();						// begin sprite drawing
	void drawSprite(LPDIRECT3DTEXTURE9 pTexture, CONST RECT * pSrcRect, CONST D3DXVECTOR3 * pCenter, CONST D3DXVECTOR3 * pPosition, D3DCOLOR Colour);
	void endDraw();							// end sprite drawing
	void setTheTransform(D3DXMATRIX theTransform);  // set the transform matrix to enable scale, rotate, translate
	void cleanUp();							// release the sprite renderer.
	~cD3DXSpriteMgr();

};
#endif