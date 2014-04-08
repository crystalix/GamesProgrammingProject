/*
=================
main.cpp
Main entry point for my game
=================
*/

#include "GameConstants.h"
#include "GameResources.h"
#include "cD3DManager.h"
#include "cSprite.h"
#include "cXAudio.h"
#include "cD3DXFont.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include <d3d.h>
#include <d3d9.h>

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle
void DefaultPage(POINT _mouseXYpos);
void PageThree(POINT _mouseXYpos);
void PageFour(POINT _mouseXYpos);
void PageEight(POINT _mouseXYpos);
void PageNine(POINT _mouseXYpos);
void PageTwelve(POINT _mouseXYpos);
void PageThirteen(POINT _mouseXYpos);
// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();
	
D3DXVECTOR3 mousePos;
vector<LPCSTR> pages;
vector<LPCSTR> goodbutton;
vector<LPCSTR> badbutton;
cSprite* nextbutton = new cSprite();
cSprite* choiceButton = new cSprite();
cSprite* choiceButton2 = new cSprite();
cSprite* background = new cSprite();
cXAudio pageflip;
cXAudio backgroundSound;
cXAudio staticnoise;
bool endgame =false;
bool gameStarted = false;
int currentpage=0;
int button1=0;
int button2=1;
LPCSTR issane="sane";
int sanity=3;
bool choice;
bool madeChoice=false;

/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{
		case WM_LBUTTONDOWN:
			{
				POINT mouseXYpos;
				mouseXYpos.x=LOWORD(lParam);
				mouseXYpos.y=HIWORD(lParam); 
				mousePos=D3DXVECTOR3((float)mouseXYpos.x,(float)mouseXYpos.y,0.0f);
				
				switch(currentpage)
				{
					case 3 : PageThree(mouseXYpos);break;
					case 4 : PageFour(mouseXYpos);break;
					case 8: PageEight(mouseXYpos);break;
					case 9: PageNine(mouseXYpos);break;
					case 12:PageTwelve(mouseXYpos);break;
					case 13:PageThirteen(mouseXYpos);break;
					default: DefaultPage(mouseXYpos);break;
				}
				
				break;
			}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,"plant.ico"); // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "SpaceRockets"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"plant.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("SpaceRockets",			// the window class to use
							 "Space Rockets",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}



bool Start()
{
	issane="sane";
	backgroundSound.playSound(L"Sounds\\backgroundmusic.wav",true);
	pages.push_back("Images\\intropage.png");
	pages.push_back("Images\\startscreen.png");
	pages.push_back("Images\\page1.png");
	pages.push_back("Images\\page2.png");
	pages.push_back("Images\\path1.png");
	pages.push_back("Images\\path2.png");
	pages.push_back("Images\\page6.png");
	pages.push_back("Images\\page7.png");
	pages.push_back("Images\\page8.png");
	pages.push_back("Images\\path3.png");
	pages.push_back("Images\\path4.png");
	pages.push_back("Images\\page11.png");
	pages.push_back("Images\\page12.png");
	pages.push_back("Images\\path5.png");
	pages.push_back("Images\\path6.png");
	pages.push_back("Images\\endpage.png");
	goodbutton.push_back("Images\\rabbitbutton.png");
	goodbutton.push_back("Images\\goodbutton2.png");
	goodbutton.push_back("Images\\goodbutton3.png");
	badbutton.push_back("Images\\gohome.png");
	badbutton.push_back("Images\\badbutton2.png");
	badbutton.push_back("Images\\badbutton3.png");
	return true;
}
void Update()
{
	choiceButton->setTexture(d3dMgr->getTheD3DDevice(),goodbutton[0]);
	choiceButton2->setTexture(d3dMgr->getTheD3DDevice(),badbutton[0]);
	if(currentpage==3 || currentpage==8 || currentpage==12 && madeChoice==false)
	{
		choice=true;
	}
	else
	{
		choice=false;
	}

	nextbutton->update();
	choiceButton->update();
	choiceButton2->update();
	background->update();
	if(sanity>=2)
	{
		issane="sane";
	}
	else
	{
		issane="insane";
	}
}

void DefaultPage(POINT _mouseXYpos)
{
	madeChoice=false;
	if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
				{
					currentpage++;
					if(currentpage==3)
					{
						pageflip.playSound(L"Sounds\\static.wav",false);
					}
					else if(currentpage==6)
					{
						pageflip.playSound(L"Sounds\\whispers.wav",false);
					}
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					else
					{
						pageflip.playSound(L"Sounds\\pageflip.wav",false);
					}

					OutputDebugString(TEXT("Hit!\n"));
				}
}

void PageThree(POINT _mouseXYpos)
{
		if(choiceButton->insideRect(choiceButton->getBoundingRect(), _mouseXYpos))
				{

					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=4;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					button1=1;
					sanity++;
				}
		if(choiceButton2->insideRect(choiceButton2->getBoundingRect(), _mouseXYpos))
				{
					//go to page 5
					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=5;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					button1=1;
					sanity--;
				}
}
void PageFour(POINT _mouseXYpos)
{
	madeChoice=false;
		if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
				{
					currentpage=6;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					else
					{
						pageflip.playSound(L"Sounds\\pageflip.wav",false);
					}

					OutputDebugString(TEXT("Hit!\n"));
				}
}
void PageEight(POINT _mouseXYpos)
{
		if(choiceButton->insideRect(choiceButton->getBoundingRect(), _mouseXYpos))
				{

					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=9;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					sanity++;
				}
		if(choiceButton2->insideRect(choiceButton2->getBoundingRect(), _mouseXYpos))
				{
					//go to page 10
					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=10;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					sanity--;
				}
		button1=2;
}
void PageNine(POINT _mouseXYpos)
{
		if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
				{
					currentpage=11;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					else
					{
						pageflip.playSound(L"Sounds\\pageflip.wav",false);
					}

					OutputDebugString(TEXT("Hit!\n"));
				}
}
void PageTwelve(POINT _mouseXYpos)
{
		if(choiceButton->insideRect(choiceButton->getBoundingRect(), _mouseXYpos))
				{

					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=13;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					sanity++;
				}
		if(choiceButton2->insideRect(choiceButton2->getBoundingRect(), _mouseXYpos))
				{
					//go to page 10
					madeChoice=true;
					pageflip.playSound(L"Sounds\\pageflip.wav",false);
					currentpage=14;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					OutputDebugString(TEXT("Hit!\n"));
					sanity--;
				}
		button1=3;
		
}
void PageThirteen(POINT _mouseXYpos)
{
	madeChoice=false;
		if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
				{
					currentpage=15;
					if(currentpage >= pages.size())
					{
						currentpage = pages.size() - 1;
					}
					else
					{
						pageflip.playSound(L"Sounds\\pageflip.wav",false);
					}

					OutputDebugString(TEXT("Hit!\n"));
				}
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;
	if(!gameStarted)
	{
		gameStarted = Start();
	}
	

	LPDIRECT3DSURFACE9 aSurface;				// the Direct3D surface
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	// Initial starting position for Rocket
	D3DXVECTOR3 rocketPos = D3DXVECTOR3(600,550,0);
	D3DXVECTOR3 buttonpos1 = D3DXVECTOR3(600,400,0);
	D3DXVECTOR3 buttonpos2 = D3DXVECTOR3(600,550,0);
	D3DXVECTOR3 backgroundpos = D3DXVECTOR3(0,0,0);
	background->setTexture(d3dMgr->getTheD3DDevice(),(pages[currentpage]));
	background->setSpritePos(backgroundpos);
	nextbutton->setTexture(d3dMgr->getTheD3DDevice(),"Images\\nextbutton.png");
	nextbutton->setSpritePos(rocketPos);
	choiceButton->setSpritePos(buttonpos1);
	choiceButton2->setSpritePos(buttonpos2);

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\book.png");

	cD3DXFont* balloonFont = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "JI Balloon Caps");

	RECT textPos;
	//SetRect(&textPos, 50, 10, 550, 100);
	SetRect(&textPos,350,10,550,100);

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// Game code goes here
			Update();
			background->setTexture(d3dMgr->getTheD3DDevice(),(pages[currentpage]));
			d3dMgr->beginRender();
			theBackbuffer = d3dMgr->getTheBackBuffer();
			d3dMgr->updateTheSurface(aSurface, theBackbuffer);		
			d3dMgr->releaseTheBackbuffer(theBackbuffer);
			
			d3dxSRMgr->beginDraw();
			d3dxSRMgr->drawSprite(background->getTexture(),NULL,NULL,&(background->getSpritePos()),0xFFFFFFFF);
			
			if(choice==true)
			{
				choiceButton->setTexture(d3dMgr->getTheD3DDevice(),goodbutton[button1]);
				choiceButton2->setTexture(d3dMgr->getTheD3DDevice(),badbutton[button1]);
				d3dxSRMgr->drawSprite(choiceButton->getTexture(),NULL,NULL,&(choiceButton->getSpritePos()),0xFFFFFFFF);
				d3dxSRMgr->drawSprite(choiceButton2->getTexture(),NULL,NULL,&(choiceButton2->getSpritePos()),0xFFFFFFFF);
			}
			else if(choice==false)
			{
				d3dxSRMgr->drawSprite(nextbutton->getTexture(),NULL,NULL,&(nextbutton->getSpritePos()),0xFFFFFFFF);

			}
			background->setTexture(d3dMgr->getTheD3DDevice(),(pages[currentpage]));
			if(
			balloonFont->printText(issane,textPos);
			d3dxSRMgr->endDraw();
			d3dMgr->endRender();
		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}