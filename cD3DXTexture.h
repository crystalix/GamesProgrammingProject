/*
=================
cD3DXTexture.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DXTexture class
=================
*/
#ifndef _CD3DXTEXTURE_H
#define _CD3DXTEXTURE_H
#include "GameConstants.h"

class cD3DXTexture
{
private:
	LPDIRECT3DTEXTURE9 aTexture;
	D3DXIMAGE_INFO aTextureInfo;
public:
	cD3DXTexture();
	cD3DXTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);
	~cD3DXTexture();
	bool createTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);			// create the texture for use.
	LPDIRECT3DTEXTURE9 getTexture();       // return the texture.
	bool setTextureInfo(LPCVOID imgInMem);  // set the image info based on the filename supplied.
	bool setTextureInfo(LPCSTR theImageFilename); // set the image info based on the filename supplied.
	D3DXIMAGE_INFO getTextureInfo();		// return information about the image loaded.
	int getTWidth();						// Return width of texture;
	int getTHeight();						// Return height of texture;
};
#endif