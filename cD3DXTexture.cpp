/*
=================
cD3DXTexture.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the cD3DXTextureMgr class
=================
*/
#include "cD3DXTexture.h"

/*
=================
- Data constructor initializes the cD3DXTextureMgr object 
- Is always called, thus ensures all cD3DXTextureMgr objects are in a consistent state.
=================
*/
cD3DXTexture::cD3DXTexture()
{
	cD3DXTexture::aTexture = NULL;
}

cD3DXTexture::cD3DXTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename)
{
	cD3DXTexture::createTexture(pd3dDevice, theFilename);
	cD3DXTexture::setTextureInfo(theFilename);
}
/*
=================
- Destructor.
=================
*/
cD3DXTexture::~cD3DXTexture()
{
	if(aTexture != NULL)
		aTexture ->Release();
}

/*
=================
- create the texture for use.
=================
*/
bool cD3DXTexture::createTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename) 	// create the texture for use.
{
	HRESULT hResult;
	// Create the texture associated with this sprite    
	// hResult = D3DXCreateTextureFromFile(pd3dDevice, theTexture, &aTexture); //*IMPORTANT* stretch images to power-of-2 dimensions
	hResult = D3DXCreateTextureFromFileEx(pd3dDevice,				// the device to be associated with the texture
											theFilename,			// Pointer to a string that specifies the filename
											D3DX_DEFAULT_NONPOW2,	// Width in pixels
											D3DX_DEFAULT_NONPOW2,	// Height, in pixels.
											0,						// Number of mip levels requested.
											0,						// Usage
											D3DFMT_A8R8G8B8,		// Describing the requested pixel format for the texture.
											D3DPOOL_DEFAULT,		// Describing the memory class into which the texture should be placed.
											D3DX_DEFAULT,			// Controlling how the image is filtered.
											D3DX_DEFAULT,			// Mipfilter controlling how the image is filtered.
											D3DCOLOR_XRGB(255, 0, 255),	// Colour key
											NULL,					// structure to be filled in with a description of the data in the source image file,
											NULL,					// structure representing a 256-color palette to fill
											&aTexture);				// Address of a pointer to an IDirect3DTexture9 interface, representing the created texture object.
											//*IMPORTANT* doesn't stretch images to power-of-2 dimensions
	// Check to make sure you have a valid texture
	if(FAILED(hResult))
	{
		return false;
	}
	return true;
}
/*
=================
- return the texture.
=================
*/
LPDIRECT3DTEXTURE9 cD3DXTexture::getTexture()        // return the texture.
{
	return cD3DXTexture::aTexture;
}
/*
=================
- set the image info based on the image in memory.
=================
*/
bool cD3DXTexture::setTextureInfo(LPCVOID imgInMem)  // set the image info based on the filename supplied.
{
	HRESULT hResult;
	// Get texture info  
	UINT imgSize = sizeof(imgInMem);
	hResult = D3DXGetImageInfoFromFileInMemory(imgInMem,imgSize,&aTextureInfo);

	if(FAILED(hResult))
	{
		return false;
	}
	return true;
}/*
=================
- set the image info based on the filename supplied.
=================
*/
bool cD3DXTexture::setTextureInfo(LPCSTR theImageFilename)  // set the image info based on the filename supplied.
{
	HRESULT hResult;
	// Get texture info   
	hResult = D3DXGetImageInfoFromFile(theImageFilename,&aTextureInfo);

	if(FAILED(hResult))
	{
		return false;
	}
	return true;
}
/*
=================
- return information about the image loaded.
=================
*/
D3DXIMAGE_INFO cD3DXTexture::getTextureInfo() 		// return information about the image loaded.
{
	return cD3DXTexture::aTextureInfo;
}
/*
=================
- Return width of texture.
=================
*/
int cD3DXTexture::getTWidth() 						// Return width of texture;
{
	return aTextureInfo.Width;
}
/*
=================
- Return height of texture.
=================
*/
int cD3DXTexture::getTHeight() 						// Return height of texture;
{
	return aTextureInfo.Height;
}