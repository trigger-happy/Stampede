#include "callbacks.h"
#include "may_proto_orx.h"

static may_proto_orx* s_instance = nullptr;
namespace cb = callbacks;

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
	orxClock_Register( m_clock, cb::inputUpdate<may_proto_orx>, s_instance, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL );
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

void may_proto_orx::inputUpdate( const orxCLOCK_INFO* clockInfo )
{
	if( orxInput_HasNewStatus( "BluePaper" ) )
	{
		orxLOG( "Blue paper" );
		orxObject_CreateFromConfig( "BluePaper" );
	}
	else if( orxInput_HasNewStatus( "GreenPaper" ) )
	{
		orxLOG( "Green paper" );
		orxObject_CreateFromConfig( "GreenPaper" );
	}
	else if( orxInput_HasNewStatus( "RedPaper" ) )
	{
		orxLOG( "Red paper " );
		orxObject_CreateFromConfig( "RedPaper" );
	}
	else if( orxInput_HasNewStatus( "JunkPaper" ) )
	{
		orxLOG( "Junk paper " );
	}
}
