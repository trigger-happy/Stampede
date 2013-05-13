#include <boost/format.hpp>
#include "callbacks.h"
#include "may_proto_orx.h"

static may_proto_orx* s_instance = nullptr;

namespace cb = callbacks;
using boost::format;

#define IS_INPUT_DOWN(x) orxInput_HasNewStatus( x ) && orxInput_IsActive( x )

orxSTATUS may_proto_orx::init()
{
	if( !s_instance )
	{
		s_instance = new may_proto_orx();
		orxViewport_CreateFromConfig( "Viewport" );
// 		orxObject_CreateFromConfig( "Object" );
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
	
	m_scoreDisplay = orxObject_CreateFromConfig( "ScoreDisplay" );
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
	int32_t result = 0;
	if( IS_INPUT_DOWN( "BluePaper" ) )
	{
		result = m_generator->stampPaper( PaperGenerator::STAMP::BLUE );
	}
	else if( IS_INPUT_DOWN( "GreenPaper" ) )
	{
		result = m_generator->stampPaper( PaperGenerator::STAMP::GREEN );
	}
	else if( IS_INPUT_DOWN( "RedPaper" ) )
	{
		result = m_generator->stampPaper( PaperGenerator::STAMP::RED );
	}
	else if( IS_INPUT_DOWN( "JunkPaper" ) )
	{
		result = m_generator->stampPaper( PaperGenerator::STAMP::JUNK );
	}

	m_score += result;
	if( m_score < 0 )
	{
		m_score = 0;
	}
	if( m_generator->isRunning() )
	{
		updateScoreDisplay();
	}
	
	if( IS_INPUT_DOWN( "StartGame" ) )
	{
		m_generator->start();
	}
	else if( IS_INPUT_DOWN( "StopGame" ) )
	{
		m_generator->stop();
	}
	else if( IS_INPUT_DOWN( "ResetGame" ) )
	{
		m_generator->reset();
	}
}

void may_proto_orx::updateScoreDisplay()
{
	format msg = format( "Score: %1%" ) % m_score;
	orxObject_SetTextString( m_scoreDisplay, msg.str().c_str() );
}
