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

#ifndef SCENE_H
#define SCENE_H
#include <functional>
#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <orx.h>

class Scene
{
public:
	typedef std::function<void ()> stackEvent;
	typedef std::function<void (float)> frameEvent;
	
	Scene( const std::string& n );
	
	stackEvent onPush;		//!< called when the scene gets pushed to the stack
	stackEvent onPop;		//!< called when the scene is removed from the stack
	stackEvent onSleep;		//!< called when the scene is no longer on top of the stack
	stackEvent onResume;	//!< called when the scene is now on top of the stack
	
	// to be called by scene manager only
	stackEvent scenePush;
	stackEvent scenePop;
	
	frameEvent frameUpdate;
	
	std::unordered_map<std::string, orxOBJECT*>	objects;
	orxSOUND*									music = nullptr;
	std::string									inputSet;
	std::string									name;
};

typedef boost::shared_ptr<Scene> ScenePtr;

#endif // SCENE_H
