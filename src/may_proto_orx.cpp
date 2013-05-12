#include "callbacks.h"
#include "may_proto_orx.h"

static may_proto_orx* s_instance = nullptr;

namespace cb = callbacks;

#define ON_KEY_PRESS(X) static bool pressed = false; \
	pressed = !pressed; \
	if( pressed ) \
	{ \
		X; \
	}

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
	if( orxInput_HasNewStatus( "BluePaper" ) )
	{
		ON_KEY_PRESS( m_generator->stampPaper( PaperGenerator::STAMP::BLUE ) )
	}
	else if( orxInput_HasNewStatus( "GreenPaper" ) )
	{
		ON_KEY_PRESS( m_generator->stampPaper( PaperGenerator::STAMP::GREEN ) )
	}
	else if( orxInput_HasNewStatus( "RedPaper" ) )
	{
		ON_KEY_PRESS( m_generator->stampPaper( PaperGenerator::STAMP::RED ) )
	}
	else if( orxInput_HasNewStatus( "JunkPaper" ) )
	{
		ON_KEY_PRESS( m_generator->stampPaper( PaperGenerator::STAMP::JUNK ) )
	}
	
	if( orxInput_HasNewStatus( "StartGame" ) )
	{
		ON_KEY_PRESS( m_generator->start() )
	}
	else if( orxInput_HasNewStatus( "StopGame" ) )
	{
		ON_KEY_PRESS( m_generator->stop() )
	}
	else if( orxInput_HasNewStatus( "ResetGame" ) )
	{
		ON_KEY_PRESS( m_generator->reset() )
	}
}
