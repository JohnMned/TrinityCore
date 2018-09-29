/*
<--------------------------------------------------------------------------->
 - Developer(s): Made by ?? Edited by - Ghostcrawler336
 - Complete: 100%
 - ScriptName: 'Duel Reset' 
 - Comment: Untested.
 - Updated - 8/7/2013 or 7/8/2013
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"

class Duel_Reset : public PlayerScript
{
	public:
		Duel_Reset() : PlayerScript("Duel_Reset"){}

		void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType /*type*/)
		{
			pWinner->RemoveAllSpellCooldown();
			pLoser->RemoveAllSpellCooldown();
			pWinner->SetHealth(pWinner->GetMaxHealth());
			if ( pWinner->getPowerType() == POWER_MANA )
				pWinner->SetPower(POWER_MANA, pWinner->GetMaxPower(POWER_MANA));
			pLoser->SetHealth(pLoser->GetMaxHealth());
			if ( pLoser->getPowerType() == POWER_MANA )
				pLoser->SetPower(POWER_MANA,  pLoser->GetMaxPower(POWER_MANA));
		}
};

void AddSC_Duel_Reset()
{
	new Duel_Reset();
}