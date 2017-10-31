#include <stdio.h>
#include <assert.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "KinematicUnit.h"
#include "PlayerMoveToMessage.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;

Game::Game()
	:mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mShouldExit(false)
	,mpFont(NULL)
	,mpSample(NULL)
	,mBackgroundBufferID(INVALID_ID)
	//,mSmurfBufferID(INVALID_ID)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;
	_devMode = false;
	CohesionWeight = AlignmentWeight = SeparateWeight = 1;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//startup allegro
	if(!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return false;
	}

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpSpriteManager = new SpriteManager();

	//startup a lot of allegro stuff

	//load image loader addon
	if( !al_init_image_addon() )
	{
		fprintf(stderr, "image addon failed to load!\n");
		return false;
	}

	//install audio stuff
	if( !al_install_audio() )
	{
		fprintf(stderr, "failed to initialize sound!\n");
		return false;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return false;
	}
 
	if (!al_reserve_samples(1))
	{
		fprintf(stderr, "failed to reserve samples!\n");
		return false;
	}

	//should probably be done in the InputSystem!
	if( !al_install_keyboard() )
	{
		printf( "Keyboard not installed!\n" ); 
		return false;
	}

	//should probably be done in the InputSystem!
	if( !al_install_mouse() )
	{
		printf( "Mouse not installed!\n" ); 
		return false;
	}

	//should be somewhere else!
	al_init_font_addon();
	if( !al_init_ttf_addon() )
	{
		printf( "ttf font addon not initted properly!\n" ); 
		return false;
	}

	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 20, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		return false;
	}

	//show the mouse
	if( !al_hide_mouse_cursor( mpGraphicsSystem->getDisplay() ) )
	{
		printf( "Mouse cursor not able to be hidden!\n" ); 
		return false;
	}

	if( !al_init_primitives_addon() )
	{
		printf( "Primitives addon not added!\n" ); 
		return false;
	}

	//load the sample
	mpSample = al_load_sample( "clapping.wav" );
	if (!mpSample)
	{
		printf( "Audio clip sample not loaded!\n" ); 
		return false;
	}

	mpMessageManager = new GameMessageManager();

	//load buffers
	mBackgroundBufferID = mpGraphicsBufferManager -> loadBuffer("wallpaper.bmp");
	bottomWallBufferID = mpGraphicsBufferManager -> loadBuffer ("wallHor.bmp");
	topWallBufferID = mpGraphicsBufferManager -> loadBuffer ("wallHor.bmp");
	rightWallBufferID = mpGraphicsBufferManager-> loadBuffer ("wallVert.bmp");
	leftWallBufferID = mpGraphicsBufferManager -> loadBuffer ("wallVert.bmp");
	mPlayerIconBufferID = mpGraphicsBufferManager -> loadBuffer("arrow.bmp");
	mEnemyIconBufferID = mpGraphicsBufferManager -> loadBuffer("enemy-arrow.bmp");
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer( mEnemyIconBufferID );
	Sprite* pEnemyArrow = NULL;
	if( pAIBuffer != NULL )
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite( AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, pAIBuffer->getWidth(), pAIBuffer->getHeight() );
	}
	
	// MIDDLETON CODE		////////////////////////////////////////////////////////
	GraphicsBuffer* leftWallBuffer = mpGraphicsBufferManager -> getBuffer (leftWallBufferID);
	if (leftWallBuffer != NULL)
		mpSpriteManager -> createAndManageSprite (WALL_SPRITE_ID, leftWallBuffer, 0, 0, leftWallBuffer -> getWidth (), leftWallBuffer -> getHeight ());
	
	GraphicsBuffer* rightWallBuffer = mpGraphicsBufferManager -> getBuffer (rightWallBufferID);
	if (rightWallBuffer != NULL)
		mpSpriteManager -> createAndManageSprite (WALL_SPRITE_ID, rightWallBuffer, 1014, 0, rightWallBuffer -> getWidth (), rightWallBuffer -> getHeight ());

	GraphicsBuffer* topWallBuffer = mpGraphicsBufferManager -> getBuffer (topWallBufferID);
	if (topWallBuffer != NULL)
		mpSpriteManager -> createAndManageSprite (WALL_SPRITE_ID, topWallBuffer, 0, 0, topWallBuffer -> getWidth (), topWallBuffer -> getHeight ());
	
	GraphicsBuffer* bottomWallBuffer = mpGraphicsBufferManager -> getBuffer (bottomWallBufferID);
	if (bottomWallBuffer != NULL)
		mpSpriteManager -> createAndManageSprite (WALL_SPRITE_ID, bottomWallBuffer, 0, 758, bottomWallBuffer -> getWidth (), bottomWallBuffer -> getHeight ());


	_um = new UnitManager ();
	_um -> LoadSprites (pArrowSprite, pEnemyArrow);
	_um -> Init ();
	
	_im = new InputManager ();
	_im -> LoadAssets (MESSAGE_MANAGER, GRAPHICS_SYSTEM, mpFont, _um);
	////////////////////////////////////////////////////////////////////////////////

	return true;
}

void Game::cleanup()
{
	_um -> Clean ();

	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;


	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;

	al_destroy_sample(mpSample);
	mpSample = NULL;
	al_destroy_font(mpFont);
	mpFont = NULL;

	//shutdown components
	al_uninstall_audio();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_shutdown_ttf_addon();
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();

	delete _um;
	_um = NULL;
	delete _im;
	_im = NULL;

}

void Game::beginLoop()
{
	mpLoopTimer->start();
}
	
bool Game::processLoop()
{
	bool ESC_Called, isEmpty;

	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager -> getSprite (BACKGROUND_SPRITE_ID );
	pBackgroundSprite -> draw (*(mpGraphicsSystem -> getBackBuffer ()), 0, 0 );

	// Update units & player
	_um -> Update (LOOP_TARGET_TIME/1000.0f, GRAPHICS_SYSTEM -> getBackBuffer ());
	
	// Display Dev Mode interface if ON.
	if (_devMode)
		_DevModeOutput ();
	

	// Process messages:
	mpMessageManager->processMessagesForThisframe ();

	// Returns true if ESC was typed. Else returns false.
	return _im -> ProcessInput ();
}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

void Game::ToggleDevMode () {
	std::cout << "DEV MODE TOGGLED! (" << _devMode << " -> " << !_devMode << ")" << std::endl;
	_devMode = !_devMode;
}

void Game::_DevModeOutput () {
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 1, ALLEGRO_ALIGN_LEFT, "              Key Mappings:");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 2, ALLEGRO_ALIGN_LEFT, "-------------------------------------------");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 3, ALLEGRO_ALIGN_LEFT, "[TAB] Toggle Dev Tools");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 4, ALLEGRO_ALIGN_LEFT, "[I]   Insert FIVE units in a flock");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 5, ALLEGRO_ALIGN_LEFT, "[D]   Remove a boid");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 6, ALLEGRO_ALIGN_LEFT, "[+]   Increment the value of a selected weight");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 7, ALLEGRO_ALIGN_LEFT, "[-]   Decrement the value of a selected weight");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 8, ALLEGRO_ALIGN_LEFT, "[ESC] Escape the program");

	std::string cohesionText = "[C]  Cohesion       " + std::to_string (CohesionWeight);
	std::string separationText = "[S]  Separation     " + std::to_string (SeparateWeight);
	std::string alignmentText = "[A]  Alignment      " + std::to_string (AlignmentWeight);

	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 10, ALLEGRO_ALIGN_LEFT, "      Settings that you can alter:");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 11, ALLEGRO_ALIGN_LEFT, "-------------------------------------------");
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 12, ALLEGRO_ALIGN_LEFT, cohesionText.c_str ());
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 13, ALLEGRO_ALIGN_LEFT, separationText.c_str ());
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 14, ALLEGRO_ALIGN_LEFT, alignmentText.c_str ());
	al_draw_text (mpFont, al_map_rgb (255, 255, 255), 10.0f, DEV_OUTPUT_OFFSET * 16, ALLEGRO_ALIGN_LEFT, "Possible Values: 0 - 10");

}