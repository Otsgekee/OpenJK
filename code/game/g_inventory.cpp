/*
This file is part of Jedi Academy.

    Jedi Academy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Jedi Academy is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Jedi Academy.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright 2001-2013 Raven Software

//g_inventory.cpp
#include "g_local.h"

/*
================
Goodie Keys
================
*/
qboolean INV_GoodieKeyGive( gentity_t *target )
{
	if ( !target || !target->client )
	{
		return (qfalse);
	}

	target->client->ps.inventory[INV_GOODIE_KEY]++;
	return (qtrue);

}

qboolean INV_GoodieKeyTake( gentity_t *target )
{
	if ( !target || !target->client )
	{
		return (qfalse);
	}

	if (target->client->ps.inventory[INV_GOODIE_KEY])
	{
		target->client->ps.inventory[INV_GOODIE_KEY]--;
		return (qtrue);
	}

	//had no keys
	return (qfalse);
}

int INV_GoodieKeyCheck( gentity_t *target )
{
	if ( !target || !target->client )
	{
		return (qfalse);
	}

	if ( target->client->ps.inventory[INV_GOODIE_KEY] )
	{//found a key
		return (INV_GOODIE_KEY);
	}

	//no keys
	return (qfalse);
}

/*
================
Security Keys
================
*/
qboolean INV_SecurityKeyGive( gentity_t *target, const char *keyname )
{
	if ( target == NULL || keyname == NULL || target->client == NULL )
	{
		return qfalse;
	}

	for ( int i = 0; i <= 4; i++ )
	{
		if ( target->client->ps.security_key_message[i][0] == '\0' )
		{//fill in the first empty slot we find with this key
			target->client->ps.inventory[INV_SECURITY_KEY]++;	// He got the key
			Q_strncpyzChecked( target->client->ps.security_key_message[ i ], keyname, MAX_SECURITY_KEY_MESSSAGE );
			return qtrue;
		}
	}
	//couldn't find an empty slot
	return qfalse;
}

void INV_SecurityKeyTake( gentity_t *target, char *keyname )
{
	if ( !target || !keyname || !target->client )
	{
		return;
	}

	for ( int i = 0; i <= 4; i++ )
	{
		if ( target->client->ps.security_key_message[i] )
		{
			if ( !Q_stricmp( keyname, target->client->ps.security_key_message[i] ) )
			{
				target->client->ps.inventory[INV_SECURITY_KEY]--;	// Take the key
				target->client->ps.security_key_message[i][0] = '\0';
				return;
			}
		}
		/*
		//don't do this because we could have removed one that's between 2 valid ones
		else
		{
			break;
		}
		*/
	}
}

qboolean INV_SecurityKeyCheck( gentity_t *target, char *keyname )
{
	if ( !target || !keyname || !target->client )
	{
		return (qfalse);
	}

	for ( int i = 0; i <= 4; i++ )
	{
		if ( target->client->ps.inventory[INV_SECURITY_KEY] && target->client->ps.security_key_message[i] )
		{
			if ( !Q_stricmp( keyname, target->client->ps.security_key_message[i] ) )
			{
				return (qtrue);
			}
		}
		/*
		//don't do this because we could have removed one that's between 2 valid ones
		else
		{
			break;
		}
		*/
	}

	return (qfalse);
}
