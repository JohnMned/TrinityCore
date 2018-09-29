#include "ScriptMgr.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Player.h"

#define UPDATE_TIME_EVERY 60 // updates every 1 minute i recommend you this not less than 60 seconds
#define EQUIRED_ONLINE_TIME 7200 // in seconds '3600' = 1hour
#define REWARD_AMOUNT 1 // how much DP gives if player meets online time

// database config
#define DATABASE "fcms"
#define TABLE "account_data"

struct sPlayerExtention
{
    sPlayerExtention() : online_time(0) {}
	uint32 online_time;
};

typedef std::map<uint64, sPlayerExtention> PlayerExtention;

static PlayerExtention m_PlayerExtention;

class Online_Time_DP : public WorldScript
{
public:
    Online_Time_DP() : WorldScript("Online_Time_DP") { }

	static const uint32 m_SaveTimer = UPDATE_TIME_EVERY * IN_MILLISECONDS;

    uint32 m_Timer;

    void OnUpdate(uint32 diff)
    {
		m_Timer += diff;
        if (m_Timer > m_SaveTimer)
        {
            m_Timer = 0;
  
			SessionMap const& smap = sWorld->GetAllSessions();
			for (SessionMap::const_iterator iter = smap.begin(); iter != smap.end(); ++iter)
			{
				if (Player* player = iter->second->GetPlayer())
				{
					uint32 player_id = player->GetGUID();

					sPlayerExtention extention = m_PlayerExtention[player_id];

					m_PlayerExtention[player_id].online_time += UPDATE_TIME_EVERY;

					if(extention.online_time >= EQUIRED_ONLINE_TIME)
					{
						// first add DP then erase "reset" for that player
						LoginDatabase.PExecute("UPDATE `%s`.`%s` SET `DP`=`DP`+%u WHERE `id`='%u'", DATABASE, TABLE, REWARD_AMOUNT, player->GetSession()->GetAccountId());
						// now reset his online time
						m_PlayerExtention.erase(player_id);
						ChatHandler(player->GetSession()).PSendSysMessage("Congratulations you earned %u DP since you've been online for 2 hours.", REWARD_AMOUNT);
					}
				}
			}
		}
	}
};

class PlayerLogs : public PlayerScript
{
public:
    PlayerLogs() : PlayerScript("PlayerLogs"){}
 
    void OnLogout(Player* player)
    {
		 // reset online time
		m_PlayerExtention.erase(player->GetSession()->GetAccountId());
	}

};

void AddSC_Online_Time_DP()
{
    new Online_Time_DP();
	new PlayerLogs;
}