#include <iostream>
#include <string>
#include <functional>
#include <orx.h>
#include "may_proto_orx.h"

using namespace std;

int main( int argc, char** argv )
{
	orx_Execute( 
		argc, argv,
		&may_proto_orx::init,
		&may_proto_orx::run,
		&may_proto_orx::exit
	);
	return EXIT_SUCCESS;
}

#ifdef __orxMSVC__

// Here's an example for a console-less program under windows with visual studio
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	orx_WinExecute( 
		&may_proto_orx::init,
		&may_proto_orx::run,
		&may_proto_orx::exit
	);
	return EXIT_SUCCESS;
}

#endif // __orxMSVC__
