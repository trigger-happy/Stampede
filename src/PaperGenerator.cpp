#include "callbacks.h"
#include "PaperGenerator.h"

namespace cb = callbacks;

PaperGenerator::PaperGenerator()
{
	m_clock = orxClock_CreateFromConfig( "PaperGeneratorClock" );
	orxClock_Register(
		m_clock, cb::clockUpdate<PaperGenerator>, this, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL
	);
}

void PaperGenerator::clockUpdate( const orxCLOCK_INFO* clockInfo )
{
	orxLOG( "Paper generator clock" );
}
