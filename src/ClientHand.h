/*
 * Class to display the client hands
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

#ifndef CLIENTHAND_H
#define CLIENTHAND_H
#include <unordered_map>
#include <string>
#include <boost/noncopyable.hpp>
#include <memory>
#include <orx.h>

class ClientHand : public boost::noncopyable
{
public:
	ClientHand();

	void dropPaper();
	void setOffset( float offset );
	void reset();

	orxOBJECT* activeHand() const
	{
		return m_activeHand;
	}

	// meant for the callback, don't call this manually
	void droppingFinished();

private:
	std::unordered_map<std::string, orxOBJECT*>	m_hands;
	orxOBJECT*									m_activeHand = nullptr;
	float										m_offset = 0;
};

typedef std::shared_ptr<ClientHand> ClientHandPtr;

#endif // CLIENTHAND_H
