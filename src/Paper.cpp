#include <cassert>
#include "Paper.h"


Paper::Paper( Paper::PAPER_TYPE type )
{
	assert( static_cast<int32_t>( type ) < 4 );
	
	// load up the paper here
}

orxVECTOR Paper::position() const
{
	//TODO changeme
	orxVECTOR pos;
	memset( &pos, 0, sizeof( pos ) );
	return orxVECTOR();
}

void Paper::setPosition( const orxVECTOR& pos )
{
	//TODO implement me
}
