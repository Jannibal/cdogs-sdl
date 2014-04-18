/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.

    Copyright (c) 2013-2014, Cong Xu
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __CAMPAIGNS
#define __CAMPAIGNS

#include "c_array.h"
#include "character.h"
#include "mission.h"
#include "sys_config.h"

typedef struct
{
	char filename[CDOGS_FILENAME_MAX];
	char path[CDOGS_PATH_MAX];
	char info[80];
	bool isBuiltin;
	campaign_mode_e mode;
	int builtinIndex;
	int numMissions;
} campaign_entry_t;

typedef struct campaign_list
{
	char name[CDOGS_FILENAME_MAX];
	CArray subFolders;	// of campaign_list_t
	CArray list;		// of campaign_entry_t
} campaign_list_t;

typedef struct
{
	campaign_list_t campaignList;
	campaign_list_t dogfightList;
	campaign_entry_t quickPlayEntry;
} custom_campaigns_t;

typedef struct
{
	char *Title;
	char *Author;
	char *Description;
	CArray Missions;	// of Mission
	CharacterStore characters;
} CampaignSetting;

typedef struct
{
	CampaignSetting Setting;
	campaign_entry_t Entry;
	unsigned int seed;
	int MissionIndex;
	bool IsLoaded;
} CampaignOptions;
extern CampaignOptions gCampaign;

void CampaignInit(CampaignOptions *campaign);
void CampaignTerminate(CampaignOptions *campaign);
void CampaignSettingInit(CampaignSetting *setting);
void CampaignSettingTerminate(CampaignSetting *setting);

void LoadAllCampaigns(custom_campaigns_t *campaigns);
void UnloadAllCampaigns(custom_campaigns_t *campaigns);

bool CampaignEntryTryLoad(
	campaign_entry_t *entry, const char *path, campaign_mode_e mode);

Mission *CampaignGetCurrentMission(CampaignOptions *campaign);
void CampaignSeedRandom(CampaignOptions *campaign);

void CampaignAndMissionSetup(
	int buildTables, CampaignOptions *campaign, struct MissionOptions *mo);

#endif
