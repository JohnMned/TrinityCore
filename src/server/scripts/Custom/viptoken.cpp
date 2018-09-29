#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Common.h"
#include "Language.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
 
class vip_token_item : public ItemScript
{
public: vip_token_item() : ItemScript("vip_token_item") { }
       
bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/)
{
if (player->GetSession()->GetSecurity() == SEC_MODERATOR)
{
player->GetSession()->SendNotification("You already have VIP access."); /* if player already have VIP access he will get a refund */
player->DestroyItemCount(item->GetEntry(), 1, true, false);
player->AddItem(59999, 10);
player->GetSession()->SendNotification("Your tokens had been refunded.");
return false;
}
else
{
   QueryResult insertvip = LoginDatabase.PQuery("REPLACE INTO `account_access` VALUES(%u, 1, 1)", player->GetSession()->GetAccountId()); /*/will run the sql and give player V,I,P rank wich in my server is SEC_VIP=4 */
player->GetSession()->SetSecurity(SEC_MODERATOR); /*will set security of that account to 4 so player don't have to logout to get vip privilege */
player->GetSession()->SendNotification("Your account level is now VIP enjoy");
player->GiveLevel(85);
player->DestroyItemCount(item->GetEntry(), 1, true, false);
return true;
  }
       }
};
 
void AddSC_vip_token_item()
{
new vip_token_item();
}