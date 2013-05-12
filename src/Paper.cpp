#include <cassert>
#include <string>
#include <array>
#include "Paper.h"

using namespace std;

const static array<string, 4> s_objectNames = {
	"RedPaper",
	"GreenPaper",
	"BluePaper",
	"JunkPaper"
};

Paper::Paper( Paper::PAPER_TYPE type )
	: m_type( type )
{
	int32_t index = static_cast<int32_t>( type );
	assert( index < 4 );
	
	m_object = orxObject_CreateFromConfig( s_objectNames[index].c_str() );
	
	orxConfig_PushSection( "PaperVars" );
	orxConfig_GetVector( "StartPos", &m_position );
	orxConfig_PopSection();
	
	orxObject_SetPosition( m_object, &m_position );
}

orxVECTOR Paper::position()
{
	orxObject_GetPosition( m_object, &m_position );
	return m_position;
}

void Paper::setPosition( const orxVECTOR& pos )
{
	orxObject_SetPosition( m_object, &pos );
}

void Paper::moveToCenter()
{
	auto status = orxObject_AddFX( m_object, "MoveToCenterFX" );
	assert( status == orxSTATUS_SUCCESS );
}

void Paper::moveOutOfTable()
{
	orxObject_AddFX( m_object, "MoveOutOfTableFX" );
}

void Paper::dropToStack( const orxVECTOR& pos )
{
	//TODO implement me
}
