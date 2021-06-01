#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass,
		"Blueprint'/Game/_MyWorld/Actors/Player/BP_CPlayer.BP_CPlayer_C'");
}


