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

#include <orx.h>
#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager()
{
	orxConfig_PushSection( "SceneManager" );
	
	int32_t numScenes = orxConfig_GetListCounter( "Scenes" );
	
	for( int32_t i = 0; i < numScenes; ++i )
	{
		auto sceneName = orxConfig_GetListString( "Scenes", i );
		ScenePtr temp = ScenePtr( new Scene( sceneName ) );
		m_scenes[sceneName] = temp;
	}
	
	orxConfig_PopSection();
}

ScenePtr SceneManager::getTopScene() const
{
	return m_sceneStack.top();
}

void SceneManager::popScene()
{
	if( !m_sceneStack.empty() )
	{
		m_sceneStack.top()->scenePop();
		m_sceneStack.top()->onPop();
		m_sceneStack.pop();
		if( !m_sceneStack.empty() )
		{
			m_sceneStack.top()->scenePush();
			m_sceneStack.top()->onResume();
		}
	}
}

void SceneManager::pushScene( const string& name )
{
	if( !m_sceneStack.empty() )
	{
		m_sceneStack.top()->scenePop();
		m_sceneStack.top()->onSleep();
	}
	
	m_sceneStack.push( m_scenes.at( name ) );
	m_sceneStack.top()->scenePush();
	m_sceneStack.top()->onPush();
}

ScenePtr SceneManager::getScene( const string& name )
{
	return m_scenes.at( name );
}

void SceneManager::frameUpdate( float dt )
{
	m_sceneStack.top()->frameUpdate( dt );
}
