#include "callbacks.h"
#include "PaperGenerator.h"

namespace cb = callbacks;


PaperGenerator::PaperGenerator()
{
	m_clock = orxClock_CreateFromConfig( "PaperGeneratorClock" );
	orxClock_Register(
		m_clock, cb::clockUpdate<PaperGenerator>, this, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL
	);
	
	orxConfig_PushSection( "PaperGeneratorSettings" );
	m_maxStackSize = orxConfig_GetS32( "MaxStackSize" );
	m_scorePenalty = orxConfig_GetS32( "ScorePenalty" );
	m_paperStackYOffset = orxConfig_GetS32( "PaperStackYOffset" );
	orxConfig_PopSection();
}

void PaperGenerator::clockUpdate( const orxCLOCK_INFO* clockInfo )
{
	if( m_running )
	{
		spawnPaper();
	}
	
	//TODO: adjust the clock here based on elapsed time
	m_elapsed += clockInfo->fDT;
}

void PaperGenerator::start()
{
	m_running = true;
}

void PaperGenerator::reset()
{
	stop();
	m_elapsed = 0;
}

void PaperGenerator::stop()
{
	m_running = false;
}

int32_t PaperGenerator::stampPaper( STAMP stamp )
{
	if( m_currentPaper && m_running )
	{
		if( m_currentPaper->paperType() == stamp )
		{
			m_currentPaper->moveOutOfTable();
			if( !m_paperStack.empty() )
			{
				setCurrentPaper( m_paperStack.back() );
				m_paperStack.pop_back();
			}
			else
			{
				m_currentPaper = nullptr;
			}
			
			return 1;
		}
		else
		{
			return m_scorePenalty;
		}
	}
	
	return 0;
}

void PaperGenerator::spawnPaper()
{
	Paper::PAPER_TYPE type = static_cast<Paper::PAPER_TYPE>( ( rand() % 3 ) );
	auto temp = m_paperPool.construct( type );
	assert( temp );
	
	if( !m_currentPaper )
	{
		setCurrentPaper( temp );
	}
	else
	{
		addPaperToStack( temp );
	}
}

void PaperGenerator::addPaperToStack( Paper* paper )
{
// 	paper->dropToStack();
	orxVECTOR pos;
	orxConfig_PushSection( "PaperVars" );
	orxConfig_GetVector( "StackBaseOffset", &pos );
	orxConfig_PopSection();
	
	pos.fY -= m_paperStack.size() * m_paperStackYOffset;
	pos.fZ -= m_paperStack.size() * 0.001;
	
	paper->setPosition( pos );
	
	m_paperStack.emplace_back( paper );
	
	if( m_paperStack.size() >= m_maxStackSize )
	{
		stop();
		if( m_onGameOver )
		{
			m_onGameOver();
		}
	}
}

void PaperGenerator::setCurrentPaper( Paper* paper )
{
	m_currentPaper = paper;
	paper->moveToCenter();
}
