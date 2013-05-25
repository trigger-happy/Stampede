/*
 * Manages the stamper arms
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

#ifndef STAMPERHANDS_H
#define STAMPERHANDS_H
#include <unordered_map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <orx.h>
#include "Paper.h"

class StamperHands : public boost::noncopyable
{
public:
	StamperHands();
	
	void show( bool s );
	
	void stamp( Paper::PAPER_TYPE type );
	
	orxOBJECT* activeStamp() const;
	orxOBJECT* idleStamp();
	
	// this is meant for the callback
	void stampingFinished();
	
	
private:
	std::unordered_map<std::string, orxOBJECT*>	m_stampHands;
	orxOBJECT*									m_activeStamp = nullptr;
};

typedef boost::shared_ptr<StamperHands> StamperHandsPtr;

#endif // STAMPERHANDS_H
