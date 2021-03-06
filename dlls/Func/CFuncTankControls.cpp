#include "Base/ExtDLL.h"
#include "Util.h"
#include "Base/CBase.h"

#include "Weapons/Weapons.h"


#include "player.h"
#include "CFuncTank.h"
#include "CFuncTankControls.h"

LINK_ENTITY_TO_CLASS( func_tankcontrols, CFuncTankControls );

TYPEDESCRIPTION	CFuncTankControls::m_SaveData[] =
{
	DEFINE_FIELD( CFuncTankControls, m_pTank, FIELD_CLASSPTR ),
};

IMPLEMENT_SAVERESTORE( CFuncTankControls, CBaseEntity );

int	CFuncTankControls::ObjectCaps( void )
{
	return (CBaseEntity::ObjectCaps() & ~FCAP_ACROSS_TRANSITION) | FCAP_IMPULSE_USE | FCAP_INDIRECT_USE;
}

void CFuncTankControls::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{ // pass the Use command onto the controls
	if ( m_pTank )
		m_pTank->Use( pActivator, pCaller, useType, value );

	ASSERT( m_pTank != NULL );	// if this fails,  most likely means save/restore hasn't worked properly
}

void CFuncTankControls::Think( void )
{
	edict_t *pTarget = NULL;

	do
	{
		pTarget = FIND_ENTITY_BY_TARGETNAME( pTarget, STRING( pev->target ) );
	} while ( !FNullEnt( pTarget ) && strncmp( STRING( pTarget->v.classname ), "func_tank", 9 ) );

	if ( FNullEnt( pTarget ) )
	{
		ALERT( at_console, "No tank %s\n", STRING( pev->target ) );
		return;
	}

	m_pTank = (CFuncTank*)Instance( pTarget );
}

void CFuncTankControls::Spawn( void )
{
	pev->solid = SOLID_TRIGGER;
	pev->movetype = MOVETYPE_NONE;
	pev->effects |= EF_NODRAW;
	SET_MODEL( ENT( pev ), STRING( pev->model ) );

	UTIL_SetSize( pev, pev->mins, pev->maxs );
	UTIL_SetOrigin( pev, pev->origin );

	pev->nextthink = gpGlobals->time + 0.3;	// After all the func_tank's have spawned

	CBaseEntity::Spawn();
}
