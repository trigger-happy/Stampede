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

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <unordered_map>
#include <stack>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "Scene.h"

class SceneManager : public boost::noncopyable
{
public:
	SceneManager();
	
	void pushScene( const std::string& name );
	void popScene();
	Scene* getTopScene() const;
	
private:
	std::unordered_map<std::string, Scene>	m_scenes;
	std::stack<Scene*>						m_sceneStack;
};

typedef boost::shared_ptr<SceneManager> SceneManagerPtr;

#endif // SCENEMANAGER_H