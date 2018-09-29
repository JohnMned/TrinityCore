/*
Made by: SymboliXDEV
Edited by: Rochet2
Work %: UnMiniTeleportered
Compile: Success
*/
 
#include "ScriptPCH.h"
 
static const uint32 buffIdstools[] = { 20217 };
 
class npc_MiniTeleporter : public CreatureScript
{
public:
    npc_MiniTeleporter() : CreatureScript("npc_MiniTeleporter") { }
 
    bool OnGossipHello(Player * player, Creature * creature)
    {
        if (player->IsInCombat())
        {
            player->GetSession()->SendNotification("You are in Combat");
            return true;
        }
 
        // Placeholders for teleports
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Spell_Arcane_TeleportTheramore:20|tMall", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\ACHIEVEMENT_ARENA_2V2_1:20|tGurubashi Arena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
 
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Ability_Mount_Charger:20|tBuff me", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Ability_Mage_ArcaneBarrage:20|tReset my Talents", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Spell_Shadow_DeathScream:20|tRemove my Sickness", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Spell_Shadow_DemonForm:20|tHeal me / Reset my CDs", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Hammer_04:20|tRepair Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Ability_Stealth:20|tClear Combat", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Ability_Creature_Cursed_04:20|tReset Instances", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }
 
    bool OnGossipSelect(Player* player, Creature * creature, uint32 sender, uint32 actions)
    {
        player->PlayerTalkClass->ClearMenus();
 
        if (sender != GOSSIP_SENDER_MAIN || actions <= GOSSIP_ACTION_INFO_DEF)
        {
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
 
        switch (actions)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->TeleportTo(530, 281.041748f, 5999.461426f, 144.730270f, 1.598671f);
            player->CLOSE_GOSSIP_MENU();
            return true;
 
        case GOSSIP_ACTION_INFO_DEF+2:
            player->TeleportTo(0, -13203.307617f, 278.522278f, 43.672985f, 4.276077f);
            player->CLOSE_GOSSIP_MENU();
            return true;
 
        case GOSSIP_ACTION_INFO_DEF+3:
            for (int i = 0; i < sizeof(buffIdstools) / sizeof(*buffIdstools); ++i)
                player->CastSpell(player, buffIdstools[i]);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+4: // Reset Talents
            player->ResetTalents(true);
            player->SendTalentsInfoData(false);
            player->GetSession()->SendAreaTriggerMessage("Your talents has been reset.", player->GetGUID(), true);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+5: // Remove my siccness
            if (player->HasAura(15007))
                player->RemoveAura(15007);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+6: // reset my CD'S
            player->SetFullHealth();
            player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
            player->RemoveAllSpellCooldown();
            break;
 
        case GOSSIP_ACTION_INFO_DEF+7: // repair my items
            player->DurabilityRepairAll(false, 0.0f, false);
            break;
 
        case GOSSIP_ACTION_INFO_DEF+8: // Clear Combat
            player->CombatStop();
            break;
 
        case GOSSIP_ACTION_INFO_DEF+9: // Reset all Instances For PvE 
            for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
            {
                Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
                {
                    player->UnbindInstance(itr, Difficulty(i));
                }
            }
            break;
 
        default: // Close
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
 
        OnGossipHello(player, creature);
        return true;
    }
};
 
void AddSC_npc_MiniTeleporter()
{
    new npc_MiniTeleporter;
}