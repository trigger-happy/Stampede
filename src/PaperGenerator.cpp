#include "callbacks.h"
#include "PaperGenerator.h"

namespace cb = callbacks;


const static int32_t c_maxStackSize = 20;


PaperGenerator::PaperGenerator()
{
	m_clock = orxClock_CreateFromConfig( "PaperGeneratorClock" );
	orxClock_Register(
		m_clock, cb::clockUpdate<PaperGenerator>, this, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL
	);
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
			//TODO store this in a config file
			return -1;
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
	m_paperStack.emplace_back( paper );
	
	if( m_paperStack.size() >= c_maxStackSize )
	{
		stop();
		m_onGameOver();
	}
}

void PaperGenerator::setCurrentPaper( Paper* paper )
{
	m_currentPaper = paper;
}
