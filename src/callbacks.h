#ifndef CALLBACKS_H
#define CALLBACKS_H
#include <orx.h>

namespace callbacks
{
	template<typename T>
	void orxFASTCALL inputUpdate( const orxCLOCK_INFO* clockInfo, void* context )
	{
		static_cast<T*>( context )->inputUpdate( clockInfo );
	}
}

#endif // CALLBACKS_H
