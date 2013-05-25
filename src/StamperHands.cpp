/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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

#include <iostream>
#include <array>
#include "StamperHands.h"

using namespace std;

// Totally bad idea but I'm out of time to find a better solution.
static StamperHands* s_instance = nullptr;

const static array<string, 4> s_objectNames = {
	"o_RightHandStampAll",
	"o_RightHandStampBlue",
	"o_RightHandStampRed",
	"o_RightHandStampGreen"
};

orxSTATUS orxFASTCALL stampFXEvent( const orxEVENT* event )
{
	orxFX_EVENT_PAYLOAD* payload = nullptr;
	payload = static_cast<orxFX_EVENT_PAYLOAD*>( event->pstPayload );
	if( event->eID == orxFX_EVENT_STOP )
	{
		if( strcmp( payload->zFXName, "fx_StampDown" ) == 0 )
		{
			if( s_instance->activeStamp() )
			{
				orxObject_AddFX( s_instance->activeStamp(), "fx_StampUp" );
			}
		}
		else if( strcmp( payload->zFXName, "fx_StampUp" ) == 0 )
		{
			s_instance->stampingFinished();
		}
	}
	
	return orxSTATUS_SUCCESS;
}

StamperHands::StamperHands()
{
	s_instance = this;
	
	for( auto n : s_objectNames )
	{
		auto stampHand = make_pair(	n, orxObject_CreateFromConfig( n.c_str() ) );
		orxObject_Enable( stampHand.second, false );
		m_stampHands.insert( stampHand );
	}
	
	orxEvent_AddHandler( orxEVENT_TYPE_FX, stampFXEvent );
}

void StamperHands::show( bool s )
{
	orxObject_Enable( m_stampHands["o_RightHandStampAll"], s );
}

void StamperHands::stamp( Paper::PAPER_TYPE type )
{
	for( auto i : m_stampHands )
	{
		orxObject_Enable( i.second, false );
	}
	
	switch( type )
	{
		case Paper::PAPER_TYPE::BLUE:
			m_activeStamp = m_stampHands["o_RightHandStampBlue"];
			break;
		case Paper::PAPER_TYPE::RED:
			m_activeStamp = m_stampHands["o_RightHandStampRed"];
			break;
		case Paper::PAPER_TYPE::GREEN:
			m_activeStamp = m_stampHands["o_RightHandStampGreen"];
			break;
		default:
			assert( false && "Invalid paper type" );
	}
	
	orxObject_Enable( m_activeStamp, true );
	orxObject_AddFX( m_activeStamp, "fx_StampDown" );
}

orxOBJECT* StamperHands::activeStamp() const
{
	return m_activeStamp;
}

orxOBJECT* StamperHands::idleStamp()
{
	return m_stampHands["o_RightHandStampAll"];
}

void StamperHands::stampingFinished()
{
	orxObject_Enable( idleStamp(), true );
	if( activeStamp() )
	{
		orxObject_Enable( activeStamp(), false );
	}
	m_activeStamp = nullptr;
}
