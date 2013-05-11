#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <orx.h>

namespace callbacks
{
	template<typename T>
	void orxFASTCALL clockUpdate( const orxCLOCK_INFO* clockInfo, void* context )
	{
		static_cast<T*>( context )->clockUpdate( clockInfo );
	}
}

#endif // CALLBACKS_H
