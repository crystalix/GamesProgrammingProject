/*
=================
cD3DManager.h
- Header file for class definition - SPECIFICATION
- Header file for the cD3DMANAGER class
=================
*/
#ifndef _CD3DMANAGER_H
#define _CD3DMANAGER_H
#include "GameConstants.h"

class cD3DManager
{
private:
	static cD3DManager* pInstance;
	LPDIRECT3D9 pD3D;				// the Direct3D object
	LPDIRECT3DDEVICE9 pd3dDevice;	// the Direct3D device
	cD3DManager();					// constructor

public:
	// using the singleton design pattern (Meyers Singleton) as the design requires only one instance of this class
	static cD3DManager* getInstance();
	bool initD3DManager(HWND wndHandle);       // Initialise cD3DManager and create Direct3D object
	void clean();						// shutdown the cD3DManager and release objects
	void beginRender();					// begin the scene prior to rendering
	void endRender();					// end the scene after rendering
	LPDIRECT3DSURFACE9 getD3DSurfaceFromFile(LPCSTR theFilename); // create and load a surface with an image from file
	LPDIRECT3DSURFACE9 getTheBackBuffer(); // get the back buffer
	void releaseTheBackbuffer(LPDIRECT3DSURFACE9 backbuffer);			// Release the backbuffer after use.
	LPDIRECT3DDEVICE9 getTheD3DDevice();   // get // the Direct3D device
	void updateTheSurface(LPDIRECT3DSURFACE9 aSurface, LPDIRECT3DSURFACE9 theBackbuffer);				// flip the buffers
	void SetDeviceRenderState(D3DRENDERSTATETYPE renderState, DWORD renderValue);  // Set the render state for the device
	~cD3DManager();							// destructor
};
#endif


