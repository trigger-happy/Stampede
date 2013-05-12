#include "callbacks.h"
#include "may_proto_orx.h"

static may_proto_orx* s_instance = nullptr;

namespace cb = callbacks;

#define ON_INPUT_DOWN(x) orxInput_HasNewStatus( x ) && orxInput_IsActive( x )

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
	if( ON_INPUT_DOWN( "BluePaper" ) )
	{
		m_generator->stampPaper( PaperGenerator::STAMP::BLUE );
	}
	else if( ON_INPUT_DOWN( "GreenPaper" ) )
	{
		m_generator->stampPaper( PaperGenerator::STAMP::GREEN );
	}
	else if( ON_INPUT_DOWN( "RedPaper" ) )
	{
		m_generator->stampPaper( PaperGenerator::STAMP::RED );
	}
	else if( ON_INPUT_DOWN( "JunkPaper" ) )
	{
		m_generator->stampPaper( PaperGenerator::STAMP::JUNK );
	}
	
	if( ON_INPUT_DOWN( "StartGame" ) )
	{
		m_generator->start();
	}
	else if( ON_INPUT_DOWN( "StopGame" ) )
	{
		m_generator->stop();
	}
	else if( ON_INPUT_DOWN( "ResetGame" ) )
	{
		m_generator->reset();
	}
}
