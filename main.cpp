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
//references to the methods I'm using throughout the game to handle page changes
void DefaultPage(POINT _mouseXYpos);
void PageThree(POINT _mouseXYpos);
void PageFour(POINT _mouseXYpos);
void PageEight(POINT _mouseXYpos);
void PageNine(POINT _mouseXYpos);
void PageTwelve(POINT _mouseXYpos);
void PageThirteen(POINT _mouseXYpos);
void PageFifteen(POINT _mouseXYpos);
void PageSixteen(POINT _mouseXYpos);
// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

//position of mouse
D3DXVECTOR3 mousePos;
//array of strings that I'm using to change the page sprite filename
vector<LPCSTR> pages;
//array of strings that I'm using to change the decision buttons sprite filenames
vector<LPCSTR> goodbutton;
vector<LPCSTR> badbutton;
//string used for score text
LPCSTR issane="sane";
//initialising sprites
cSprite* nextbutton = new cSprite();
cSprite* backbutton = new cSprite();
cSprite* choiceButton = new cSprite();
cSprite* choiceButton2 = new cSprite();
cSprite* background = new cSprite();
cSprite* sanityText= new cSprite();
cSprite* openbook = new cSprite();
cSprite* table = new cSprite();
//sound effect audio
cXAudio pageflip;
//background audio
cXAudio backgroundSound;
//boolean used to initialise settings
bool gameStarted = false;
//bools that turns the option buttons on and off
bool choice;
bool madeChoice=false;
bool gameStart=false;
//boolean used to determine if on ending screen or not
bool gameEnd=false;
//tracks page of story
int currentpage=0;
//used to change choice button sprite
int button1=0;
//used to track game score
int sanity=3;


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
			//tracks mouse click position
			POINT mouseXYpos;
			mouseXYpos.x=LOWORD(lParam);
			mouseXYpos.y=HIWORD(lParam); 
			/*
			this switch statement is used to control the events of different pages
			this is needed to control what page to go to after a choice and the player's score change after a choice
			*/
			switch(currentpage)
			{
			case 2 : PageThree(mouseXYpos);break;
			case 3 : PageFour(mouseXYpos);break;
			case 7: PageEight(mouseXYpos);break;
			case 8: PageNine(mouseXYpos);break;
			case 11:PageTwelve(mouseXYpos);break;
			case 12:PageThirteen(mouseXYpos);break;
			case 14:PageFifteen(mouseXYpos);break;
			case 15:PageSixteen(mouseXYpos);break;
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
		"Storybook",			// the title bar text
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
	//return values back to their initial states for replays
	D3DXVECTOR3 openbookpos = D3DXVECTOR3(200,220,0);
	sanity=3;
	button1=0;
	gameStart=false;
	gameEnd=false;
	issane="sane";
	//start background music
	backgroundSound.playSound(L"Sounds\\backgroundmusic.wav",true);
	//add pages to the book
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
	pages.push_back("Images\\report.png");
	//add button images for the 'good' choices
	goodbutton.push_back("Images\\rabbitbutton.png");
	goodbutton.push_back("Images\\goodbutton2.png");
	goodbutton.push_back("Images\\goodbutton3.png");
	goodbutton.push_back("Images\\restartbutton.png");
	//add button images for the 'bad' choices
	badbutton.push_back("Images\\gohome.png");
	badbutton.push_back("Images\\badbutton2.png");
	badbutton.push_back("Images\\badbutton3.png");
	badbutton.push_back("Images\\quitbutton.png");
	return true;
}
void Update()
{
	//set choice to true when the page has a choice so the choice buttons will be used instead of next button
	if(currentpage==2 || currentpage==7 || currentpage==11 || currentpage==15 && madeChoice==false)
	{
		choice=true;
	}
	else
	{
		choice=false;
	}

	//update sprites
	nextbutton->update();
	backbutton->update();
	choiceButton->update();
	choiceButton2->update();
	background->update();
	openbook->update();
	table->update();
	//update score text
	if(sanity>=3)
	{
		issane="sane";
	}
	else
	{
		issane="insane";
	}
}
/*These are the methods that are being used in the switch statement.
They take in the mouse position on click, and if a button has been pressed, the code inside the if statement will happen.
the page is changed so the next chronological page will be shown,
the page flip sound effect will be played and sometimes another sound effect also.

*/
void DefaultPage(POINT _mouseXYpos)
{
	madeChoice=false;
	if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
	{
		currentpage++;
		if(currentpage==2)
		{
			pageflip.playSound(L"Sounds\\static.wav",false);
		}
		else if(currentpage==5)
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
	if(currentpage!=0)
	{
	if(backbutton->insideRect(backbutton->getBoundingRect(), _mouseXYpos))
	{
		pageflip.playSound(L"Sounds\\pageflip.wav",false);
		currentpage--;
		if(currentpage >= pages.size())
		{
			currentpage = pages.size() - 1;
		}
		OutputDebugString(TEXT("Hit!\n"));
		button1=1;
	}
	}
}


void PageThree(POINT _mouseXYpos)
{
	if(choiceButton->insideRect(choiceButton->getBoundingRect(), _mouseXYpos))
	{

		madeChoice=true;
		pageflip.playSound(L"Sounds\\pageflip.wav",false);
		currentpage=3;
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
		currentpage=4;
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
		currentpage=5;
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
		currentpage=8;
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
		currentpage=10;
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
		currentpage=12;
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
		currentpage=13;
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
		currentpage=14;
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
void PageFifteen(POINT _mouseXYpos)
{
	madeChoice=false;
	if(nextbutton->insideRect(nextbutton->getBoundingRect(), _mouseXYpos))
	{
		currentpage=15;
		gameEnd=true;
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
void PageSixteen(POINT _mouseXYpos)
{
	//restart the game
	if(choiceButton->insideRect(choiceButton->getBoundingRect(), _mouseXYpos))
	{
		madeChoice=true;
		pageflip.playSound(L"Sounds\\pageflip.wav",false);
		currentpage=0;
		if(currentpage >= pages.size())
		{
			currentpage = pages.size() - 1;
		}
		OutputDebugString(TEXT("Hit!\n"));
		button1=0;
		gameStarted = Start();
	}
	//exit the game
	if(choiceButton2->insideRect(choiceButton2->getBoundingRect(), _mouseXYpos))
	{
		WM_DESTROY;
		WM_CLOSE;
		exit(0);
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
	// Initial position vectors for sprites to be used in the game
	D3DXVECTOR3 rocketPos = D3DXVECTOR3(600,550,0);
	D3DXVECTOR3 backbuttonpos = D3DXVECTOR3(450,550,0);
	D3DXVECTOR3 buttonpos1 = D3DXVECTOR3(600,400,0);
	D3DXVECTOR3 buttonpos2 = D3DXVECTOR3(600,550,0);
	D3DXVECTOR3 restartbuttonPos =  D3DXVECTOR3(400,550,0);
	D3DXVECTOR3 quitbuttonPos =  D3DXVECTOR3(600,550,0);
	D3DXVECTOR3 backgroundpos = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3 sanitytextpos = D3DXVECTOR3(400,300,0);
	D3DXVECTOR3 openbookpos = D3DXVECTOR3(200,220,0);
	D3DXVECTOR3 tablepos = D3DXVECTOR3(200,450,0);

	//initial textures and positions of sprites
	background->setTexture(d3dMgr->getTheD3DDevice(),(pages[currentpage]));
	background->setSpritePos(backgroundpos);
	nextbutton->setSpritePos(rocketPos);
	backbutton->setTexture(d3dMgr->getTheD3DDevice(),"Images\\backbutton.png");
	backbutton->setSpritePos(backbuttonpos);
	choiceButton->setSpritePos(buttonpos1);
	choiceButton2->setSpritePos(buttonpos2);
	openbook->setTexture(d3dMgr->getTheD3DDevice(),"Images\\openbook.png");
	openbook->setSpritePos(openbookpos);
	table->setSpritePos(tablepos);
	table->setTexture(d3dMgr->getTheD3DDevice(),"Images\\table.png");


	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface

	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\room.png");

	//text 
	cD3DXFont* balloonFont = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "null");

	RECT textPos;
	//SetRect(&textPos, 50, 10, 550, 100);
	SetRect(&textPos,350,0,600,100);

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
			//change page texture
			background->setTexture(d3dMgr->getTheD3DDevice(),(pages[currentpage]));
			openbook->setSpritePos(openbookpos);
			if(openbook->collidedWith(openbook->getBoundingRect(),table->getBoundingRect()))
			{
				gameStart=true;
			}
			d3dMgr->beginRender();
			theBackbuffer = d3dMgr->getTheBackBuffer();
			d3dMgr->updateTheSurface(aSurface, theBackbuffer);		
			d3dMgr->releaseTheBackbuffer(theBackbuffer);

			d3dxSRMgr->beginDraw();
			//draw page
			if(gameStart==true)
			{
				d3dxSRMgr->drawSprite(background->getTexture(),NULL,NULL,&(background->getSpritePos()),0xFFFFFFFF);

				//if there is a choice button on the page, this code is carried out
				//the choice buttons' textured are set, and then they're drawn
				if(choice==true)
				{

					//if on the score page, the choice buttons' positions are changed
					//and the score sprite is displayed
					if(gameEnd==true)
					{
						choiceButton->setSpritePos(restartbuttonPos);
						choiceButton2->setSpritePos(quitbuttonPos);
						sanityText->setSpritePos(sanitytextpos);
						if(sanity>=3)
						{
							sanityText->setTexture(d3dMgr->getTheD3DDevice(),"Images\\sanetext.png");
						}
						else
						{
							sanityText->setTexture(d3dMgr->getTheD3DDevice(),"Images\\insanetext.png");
						}
						d3dxSRMgr->drawSprite(sanityText->getTexture(),NULL,NULL,&(sanityText->getSpritePos()),0xFFFFFFFF);
					}
					else
					{
						choiceButton->setSpritePos(buttonpos1);
						choiceButton2->setSpritePos(buttonpos2);
					}

					choiceButton->setTexture(d3dMgr->getTheD3DDevice(),goodbutton[button1]);
					choiceButton2->setTexture(d3dMgr->getTheD3DDevice(),badbutton[button1]);
					d3dxSRMgr->drawSprite(choiceButton->getTexture(),NULL,NULL,&(choiceButton->getSpritePos()),0xFFFFFFFF);
					d3dxSRMgr->drawSprite(choiceButton2->getTexture(),NULL,NULL,&(choiceButton2->getSpritePos()),0xFFFFFFFF);

				}
				//if there isn't a choice button on the page, this code is carried out
				// the next button is drawn
				else if(choice==false)
				{
					d3dxSRMgr->drawSprite(nextbutton->getTexture(),NULL,NULL,&(nextbutton->getSpritePos()),0xFFFFFFFF);
					//if not the first page or a page after a choice, the back button will be displayed
					if(currentpage!=0&&currentpage!=3 && currentpage!=4 && currentpage!=8 && currentpage!=9 && currentpage!=12 &&currentpage!=13 && currentpage!=16 && currentpage!=17)
					{
					d3dxSRMgr->drawSprite(backbutton->getTexture(),NULL,NULL,&(backbutton->getSpritePos()),0xFFFFFFFF);
					}
				}
			}
			else
			{	
				d3dxSRMgr->drawSprite(table->getTexture(),NULL,NULL,&(table->getSpritePos()),0xFFFFFFFF);
				d3dxSRMgr->drawSprite(openbook->getTexture(),NULL,NULL,&(openbook->getSpritePos()),0xFFFFFFFF);
				openbookpos.y++;
				
			}

				d3dxSRMgr->endDraw();
				//if its not the score screen, this code will show the score
				if(gameEnd==false&&gameStart==true)
				{
					balloonFont->printText(issane,textPos);
				}
			}
				d3dMgr->endRender();
		}
		d3dxSRMgr->cleanUp();
		d3dMgr->clean();
		return (int) msg.wParam;
	}