/*
=================
cD3DXSpriteMgr.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the cD3DXSpriteMgr class
=================
*/
#include "cD3DXSpriteMgr.h"

cD3DXSpriteMgr* cD3DXSpriteMgr::pInstance = NULL;

/*
=================
- Data constructor initializes the cD3DManager object 
- Is always called, thus ensures all cD3DManager objects are in a consistent state.
=================
*/
cD3DXSpriteMgr::cD3DXSpriteMgr()
{
}
/*
=================
- using the singleton design pattern (Meyers Singleton) as the design requires only one instance of this class.
=================
*/
cD3DXSpriteMgr* cD3DXSpriteMgr::getInstance()
{
	if(pInstance == NULL)
	{
		pInstance = new cD3DXSpriteMgr();
	}
	return cD3DXSpriteMgr::pInstance;
}

/*
=================
- Initialise cD3DXSpriteMgr and create LPD3DXSPRITE renderer object.
=================
*/
bool cD3DXSpriteMgr::initD3DXSpriteMgr(LPDIRECT3DDEVICE9 pd3dDevice)       // Initialise cD3DManager and create Direct3D object
{
	HRESULT hResult;

	// Create the Sprite    
	hResult = D3DXCreateSprite(pd3dDevice, &(cD3DXSpriteMgr::dxSpriteRenderer)); 

	// Check to make sure you have a valid Sprite
	if(FAILED(hResult))
	{
		return false;
	}
	return true;
}
/*
=================
- begin sprite drawing.
=================
*/
void cD3DXSpriteMgr::beginDraw() 						// begin sprite drawing
{
	cD3DXSpriteMgr::dxSpriteRenderer->Begin(D3DXSPRITE_ALPHABLEND);
}
/*
=================
- Draw sprite texture.
=================
*/
void cD3DXSpriteMgr::drawSprite(LPDIRECT3DTEXTURE9 pTexture, CONST RECT * pSrcRect, CONST D3DXVECTOR3 * pCenter, CONST D3DXVECTOR3 * pPosition, D3DCOLOR Colour)
{
	cD3DXSpriteMgr::dxSpriteRenderer->Draw(pTexture, pSrcRect, pCenter, pPosition, Colour);
}
/*
=================
- end sprite drawing.
=================
*/
void cD3DXSpriteMgr::endDraw() 							// end sprite drawing
{
	cD3DXSpriteMgr::dxSpriteRenderer->End();
}

/*
=================
- set the transform matrix to enable scale, rotate, translate.
=================
*/
void cD3DXSpriteMgr::setTheTransform(D3DXMATRIX theTransform)   // set the transform matrix to enable scale, rotate, translate
{
	if(S_OK == cD3DXSpriteMgr::dxSpriteRenderer->SetTransform(&theTransform))
		OutputDebugString("transform set!!!");
}

/*
=================
- shutdown the cD3DXSpriteMgr and release objects.
=================
*/

void cD3DXSpriteMgr::cleanUp()						// shutdown the cD3DXSpriteMgr and release objects
{
	if(dxSpriteRenderer != NULL)
		dxSpriteRenderer->Release();
}

/*
=================
- Destructor 
=================
*/
cD3DXSpriteMgr::~cD3DXSpriteMgr()
{
  if(pInstance != 0)delete pInstance;
}