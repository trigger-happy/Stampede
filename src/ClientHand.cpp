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

#include <iterator>
#include "ClientHand.h"

using namespace std;

// still a bad idea
static ClientHand* s_instance = nullptr;

orxSTATUS orxFASTCALL dropFXEvent( const orxEVENT* event )
{
	orxFX_EVENT_PAYLOAD* payload = nullptr;
	payload = static_cast<orxFX_EVENT_PAYLOAD*>( event->pstPayload );
	if( event->eID == orxFX_EVENT_STOP )
	{
		if( strcmp( payload->zFXName, "fx_MoveRight" ) )
		{
			if( s_instance->activeHand() )
			{
				orxObject_AddFX( s_instance->activeHand(), "fx_MoveLeft" );
			}
		}
		else if( strcmp( payload->zFXName, "fx_MoveLeft" ) )
		{
			s_instance->droppingFinished();
		}
	}

	return orxSTATUS_SUCCESS;
}

ClientHand::ClientHand()
{
	s_instance = this;

	orxConfig_PushSection( "ClientHands" );

	if( orxConfig_HasValue( "Hands" ) )
	{
		auto numHands = orxConfig_GetListCounter( "Hands" );
		for( int i = 0; i < numHands; ++i )
		{
			auto handName = orxConfig_GetListString( "Hands", i );
			auto hand = orxObject_CreateFromConfig( handName );
			m_hands.emplace( make_pair( handName, hand ) );

			orxObject_Enable( hand, false );
		}
	}

	orxConfig_PopSection();

	orxEvent_AddHandler( orxEVENT_TYPE_FX, dropFXEvent );
}

void ClientHand::dropPaper()
{
	auto index = rand() % m_hands.size();
	auto iter = m_hands.begin();
	advance( iter, index );

	m_activeHand = iter->second;
	orxObject_Enable( activeHand(), true );
	orxObject_AddFX( activeHand(), "fx_MoveRight" );
}

void ClientHand::droppingFinished()
{
	if( activeHand() )
	{
		orxObject_Enable( activeHand(), false );
	}
	m_activeHand = nullptr;
}

void ClientHand::setOffset( float offset )
{
	orxVECTOR position, inPosition;

	m_offset += offset;
	orxConfig_PushSection( "o_ClientHand" );

	orxConfig_GetVector( "Position", &position );
	orxConfig_GetVector( "InPosition", &inPosition );

	position.fY += offset;
	inPosition.fY += offset;

	orxConfig_SetVector( "Position", &position );
	orxConfig_SetVector( "InPosition", &inPosition );

	orxConfig_PopSection();
}

void ClientHand::reset()
{
	orxVECTOR position, inPosition;
	orxConfig_PushSection( "o_ClientHand" );

	orxConfig_GetVector( "Position", &position );
	orxConfig_GetVector( "InPosition", &inPosition );

	position.fY -= m_offset;
	inPosition.fY -= m_offset;

	orxConfig_SetVector( "Position", &position );
	orxConfig_SetVector( "InPosition", &inPosition );

	orxConfig_PopSection();

	m_offset = 0;
}
