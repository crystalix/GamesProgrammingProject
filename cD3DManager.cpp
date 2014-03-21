/*
=================
cD3DManager.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the cD3DMANAGER class
=================
*/
#include "cD3DManager.h"

cD3DManager* cD3DManager::pInstance = NULL;

/*
=================
- Data constructor initializes the cD3DManager object 
- Is always called, thus ensures all cD3DManager objects are in a consistent state.
=================
*/
cD3DManager::cD3DManager()
{
}
/*
=================
- using the singleton design pattern (Meyers Singleton) as the design requires only one instance of this class.
=================
*/
cD3DManager* cD3DManager::getInstance()
{
	if(pInstance == NULL)
	{
		pInstance = new cD3DManager();
	}
	return cD3DManager::pInstance;
}

/*
=================
- Initialise cD3DManager and create Direct3D object.
=================
*/

bool cD3DManager::initD3DManager(HWND wndHandle)        // Initialise cD3DManager and create Direct3D object
{
	pD3D = NULL;
	pd3dDevice = NULL;

	// Create the DirectX object
	if( NULL == ( pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		return false;
	}

	// Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // D3DPRESENT_INTERVAL_ONE;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferWidth = 800;
	d3dpp.hDeviceWindow = wndHandle;

	// Create a default DirectX device
	if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL, // D3DDEVTYPE_REF
									wndHandle,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&pd3dDevice ) ) )
	{
		return false;
	}

	return true;
}
/*
=================
- shutdown the cD3DManager and release objects.
=================
*/

void cD3DManager::clean()						// shutdown the cD3DManager and release objects
{
	// Release the device and the Direct3D object
	if( pd3dDevice != NULL )
		pd3dDevice->Release( );

	if( pD3D != NULL )
		pD3D->Release( );

}
/*
=================
- begin the scene prior to rendering.
=================
*/

void cD3DManager::beginRender() 					// begin the scene prior to rendering
{
	// Clear the back buffer to a blue color
	pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0,0,255 ), 1.0f, 0 );
	pd3dDevice->BeginScene();

}
/*
=================
- end the scene after rendering.
=================
*/

void cD3DManager::endRender() 					// end the scene after rendering
{
	// finish the scene
	pd3dDevice->EndScene();
	// Present the back buffer contents to the display
	pd3dDevice->Present( NULL, NULL, NULL, NULL );
}
/*
=================
- create and load a surface with an image from file.
=================
*/

LPDIRECT3DSURFACE9 cD3DManager::getD3DSurfaceFromFile(LPCSTR theFilename) // create and load a surface with an image from file
{
	HRESULT hResult;
	LPDIRECT3DSURFACE9 surface;		// the Direct3D surface

	hResult = pd3dDevice->CreateOffscreenPlainSurface(800, // the width of the surface to create
										  600, // the height of the surface to create
										  D3DFMT_X8R8G8B8, // the surface format 
										  D3DPOOL_SYSTEMMEM, // the memory pool to use *IMPORTANT* when dealing with surfaces
										  &surface, // holds the resulting surface
										  NULL); // reserved; should be NULL
	// Check the return value to make sure that this function call was successful
	if (FAILED(hResult))
		return false;

	hResult = D3DXLoadSurfaceFromFile(surface,NULL,NULL,theFilename,NULL,
										D3DX_DEFAULT,0,NULL);
	if ( FAILED(hResult))
		return false;

	return surface;
}
/*
=================
- Returns the back buffer.
=================
*/

LPDIRECT3DSURFACE9 cD3DManager::getTheBackBuffer()  // get the back buffer
{
		LPDIRECT3DSURFACE9 backbuffer = NULL;	// This will hold the back buffer
		// Get the back buffer
		pd3dDevice->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer );
		return backbuffer;
}
/*
=================
- Release the backbuffer after use.
=================
*/
void cD3DManager::releaseTheBackbuffer(LPDIRECT3DSURFACE9 backbuffer)			// Release the backbuffer after use.
{
	if(backbuffer != NULL)
		backbuffer->Release();
}
/*
=================
- Returns the Direct3D device.
=================
*/

LPDIRECT3DDEVICE9 cD3DManager::getTheD3DDevice()    // get the Direct3D device
{
	return pd3dDevice;
}
/*
=================
- Call the updateSurface method to flip the buffers.
=================
*/
void cD3DManager::updateTheSurface(LPDIRECT3DSURFACE9 aSurface, LPDIRECT3DSURFACE9 theBackbuffer) 				// flip the buffers
{
	pd3dDevice->UpdateSurface(aSurface,NULL,theBackbuffer,NULL);
}
/*
=================
- Set the render state for the device 
=================
*/
void cD3DManager::SetDeviceRenderState(D3DRENDERSTATETYPE renderState, DWORD renderValue)  // Set the render state for the device
{
	cD3DManager::pd3dDevice->SetRenderState(renderState,renderValue);
}

/*
=================
- Destructor 
=================
*/
cD3DManager::~cD3DManager()
{
  if(pInstance != 0)delete pInstance;
}