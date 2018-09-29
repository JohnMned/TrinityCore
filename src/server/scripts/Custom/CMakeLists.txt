# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# file(GLOB_RECURSE sources_Custom Custom/*.cpp Custom/*.h)

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
#  ${sources_Custom}
    Custom/Transmog/Transmogrification.h
    Custom/Transmog/Transmogrification.cpp
    Custom/Transmog/Transmogrifier.cpp
    Custom/Beatmaster.cpp
    Custom/Buff.cpp
    Custom/Duel_Reset.cpp
    Custom/factionracenpc.cpp
    Custom/Honorable.cpp
    Custom/Honorable1.cpp
    Custom/Honorable2.cpp
    Custom/Masterbuff.cpp
    Custom/MiniTeleporter.cpp
    Custom/Race.cpp
    Custom/Support.cpp
    Custom/VIP.cpp
    Custom/Profession.cpp
    Custom/Worldchat.cpp
    Custom/pvpmall.cpp
    Custom/pplayer.cpp
    Custom/viptoken.cpp
    Custom/killstreak.cpp
    Custom/visual.cpp
    Custom/Mini.cpp
    Custom/lvluptoken.cpp
    Custom/1v1.cpp
    Custom/AllSpells.cpp
    Custom/LearnTalents.cpp
    Custom/PVPAntiFarm.cpp
    Custom/announce_login.cpp
    Custom/chat_censor.cpp
    Custom/Add_TimerVP.cpp
    Custom/Add_TimerDP.cpp
)

message("  -> Prepared: Custom")
