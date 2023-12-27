.set LOCALID_ANABEL, 1

ElenaHall_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Elenahall_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Elenahall_OnWarp
	.byte 0

Elenahall_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Elenahall_EventScript_TurnPlayerNorth
	.2byte 0

Elenahall_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

Elenahall_OnFrame:
	map_script_2 VAR_TEMP_1, 0, Elenahall_EventScript_EnterHallOfFame
	.2byte 0

Elenahall_EventScript_EnterHallOfFame::
	lockall
	applymovement LOCALID_ANABEL, Elenahall_Movement_WalkIntoHallOfFame1
	applymovement OBJ_EVENT_ID_PLAYER, Elenahall_Movement_WalkIntoHallOfFame1
	waitmovement 0
	applymovement LOCALID_ANABEL, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Elenahall_Text_HereWeHonorLeagueChampions, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ANABEL, Elenahall_Movement_WalkIntoHallOfFame2
	applymovement OBJ_EVENT_ID_PLAYER, Elenahall_Movement_WalkIntoHallOfFame2
	waitmovement 0
	delay 20
	applymovement LOCALID_ANABEL, Common_Movement_WalkInPlaceFasterRight
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Elenahall_Text_LetsRecordYouAndYourPartnersNames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ANABEL, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD
	delay 40
	setvar VAR_TEMP_1, 1
	call EverGrandeCity_HallOfFame_EventScript_SetGameClearFlags
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Elenahall_EventScript_GameClearMale
	goto_if_eq VAR_RESULT, FEMALE, Elenahall_EventScript_GameClearFemale
	end

Elenahall_EventScript_GameClearMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

Elenahall_EventScript_GameClearFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

Elenahall_Movement_WalkIntoHallOfFame1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Elenahall_Movement_WalkIntoHallOfFame2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Elenahall_Text_HereWeHonorLeagueChampions:
	.string "ELENA: This room…\p"
	.string "This is where we keep records of\n"
	.string "POKéMON that prevailed through\l"
	.string "harsh battles.\p"
	.string "It is here that the LEAGUE CHAMPIONS\n"
	.string "are honored.$"

Elenahall_Text_LetsRecordYouAndYourPartnersNames:
	.string "ELENA: Come on, let's record your\n"
	.string "name as a TRAINER who triumphed over\l"
	.string "the POKéMON LEAGUE, though i dont think\l"
	.string "that you deserve it but its my job.$"
