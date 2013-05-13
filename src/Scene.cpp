/*
 * Copyright (C) 2013  James Choa triggerhappyelite@gmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <algorithm>
#include "Scene.h"

using namespace std;

Scene::Scene( const string& n )
	: name( n )
{
	// set some default handlers
	onPop = [this](){
		auto iter = objects.begin();
		while( iter != objects.end() )
		{
			orxObject_Enable( iter->second, false );
			++iter;
		}
	};
	
	onSleep = onPop;
	
	onPush = [this](){
		auto iter = objects.begin();
		while( iter != objects.end() )
		{
			orxObject_Enable( iter->second, true );
			++iter;
		}
		orxInput_SelectSet( inputSet.c_str() );
	};
	onResume = onPush;
	
	// load up the objects and disable them
	orxConfig_PushSection( n.c_str() );
	if( orxConfig_HasValue( "Objects" ) )
	{
		auto numObjects = orxConfig_GetListCounter( "Objects" );
		for( int i = 0; i < numObjects; ++i )
		{
			auto objectName = orxConfig_GetListString( "Objects", i );
			auto object = orxObject_CreateFromConfig( objectName );
			objects.emplace( make_pair( objectName, object ) );
			
			// disable the object for now
			orxObject_Enable( object, false );
		}
	}
	
	inputSet = orxConfig_GetString( "InputSet" );
	orxConfig_PopSection();
}
