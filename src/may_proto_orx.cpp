#include <functional>
#include <boost/format.hpp>
#include "callbacks.h"
#include "may_proto_orx.h"

static may_proto_orx* s_instance = nullptr;

const static std::string s_stampSoundName = "s_Stamp";

namespace cb = callbacks;
using boost::format;

#define IS_INPUT_DOWN(x) orxInput_HasNewStatus( x ) && orxInput_IsActive( x )

orxSTATUS may_proto_orx::init()
{
	if( !s_instance )
	{
		s_instance = new may_proto_orx();
		orxViewport_CreateFromConfig( "Viewport" );
	}
	
	return orxSTATUS_SUCCESS;
}

orxSTATUS may_proto_orx::run()
{
	return s_instance->update();
}

void may_proto_orx::exit()
{
	delete s_instance;
}

may_proto_orx* may_proto_orx::instance()
{
	return s_instance;
}

may_proto_orx::may_proto_orx()
{
	m_clock = orxClock_FindFirst( orx2F( -1.0f ), orxCLOCK_TYPE_CORE );
	orxClock_Register( m_clock, cb::clockUpdate<may_proto_orx>, this, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL );
	
	m_generator = PaperGeneratorPtr( new PaperGenerator() );
	m_generator->atGameOver( std::bind( &may_proto_orx::onGameOver, this ) );
	
	m_sceneManager = SceneManagerPtr( new SceneManager() );
	setupScenes();
}

void may_proto_orx::setupScenes()
{
	auto titleScene = m_sceneManager->getScene( "TitleScene" );
	auto gameScene = m_sceneManager->getScene( "GameScene" );
	
	m_scoreDisplay = gameScene->objects.at( "ScoreDisplay" );
	
	// title scene input handling
	titleScene->frameUpdate = [this]( float dt )
	{
		if( IS_INPUT_DOWN( "GoToGameScene" ) )
		{
			m_sceneManager->pushScene( "GameScene" );
		}
	};
	
	// game scene input handling
	gameScene->frameUpdate = [this, gameScene]( float dt )
	{
		int32_t result = 0;
		if( IS_INPUT_DOWN( "BluePaper" ) )
		{
			result = m_generator->stampPaper( PaperGenerator::STAMP::BLUE );
			orxSound_Play( gameScene->sounds[s_stampSoundName] );
		}
		else if( IS_INPUT_DOWN( "GreenPaper" ) )
		{
			result = m_generator->stampPaper( PaperGenerator::STAMP::GREEN );
			orxSound_Play( gameScene->sounds[s_stampSoundName] );
		}
		else if( IS_INPUT_DOWN( "RedPaper" ) )
		{
			result = m_generator->stampPaper( PaperGenerator::STAMP::RED );
			orxSound_Play( gameScene->sounds[s_stampSoundName] );
		}
		else if( IS_INPUT_DOWN( "JunkPaper" ) )
		{
			result = m_generator->stampPaper( PaperGenerator::STAMP::JUNK );
			orxSound_Play( gameScene->sounds[s_stampSoundName] );
		}
		
		m_score += result;
		if( m_score < 0 )
		{
			m_score = 0;
		}
		if( m_generator->isRunning() && result )
		{
			updateScoreDisplay();
		}
		
		if( IS_INPUT_DOWN( "StartGame" ) )
		{
// 			m_generator->start();
// 			updateScoreDisplay();
		}
		else if( IS_INPUT_DOWN( "StopGame" ) )
		{
			m_generator->stop();
		}
		else if( IS_INPUT_DOWN( "ResetGame" ) )
		{
			m_generator->reset();
		}
	};
	
	gameScene->onPush = [this]()
	{
		m_generator->start();
		updateScoreDisplay();
	};
	
	m_sceneManager->pushScene( "TitleScene" );
}

orxSTATUS may_proto_orx::update()
{
	orxSTATUS result = orxSTATUS_SUCCESS;
	
	if( orxInput_IsActive( "Quit" ) )
	{
		result = orxSTATUS_FAILURE;
	}
	return result;
}

void may_proto_orx::clockUpdate( const orxCLOCK_INFO* clockInfo )
{
	m_sceneManager->frameUpdate( clockInfo->fDT );
}

void may_proto_orx::updateScoreDisplay()
{
	format msg = format( "Score: %1%" ) % m_score;
	orxObject_SetTextString( m_scoreDisplay, msg.str().c_str() );
}

void may_proto_orx::onGameOver()
{
	format msg = format( "Gameover, your score is: %1%" ) % m_score;
	orxObject_SetTextString( m_scoreDisplay, msg.str().c_str() );
}
