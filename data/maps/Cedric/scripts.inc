Cedric_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Cedric_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, Cedric_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Cedric_OnWarp
	.byte 0

@ Unused, Drake uses Sidneys identical OnWarp for some reason
Cedric_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Cedric_EventScript_PlayerTurnNorth
	.2byte 0

Cedric_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

Cedric_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 3, Cedric_EventScript_WalkInCloseDoor
	.2byte 0

Cedric_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 4
	releaseall
	end

Cedric_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_CEDRIC, Cedric_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 4, Cedric_EventScript_CloseDoor
	end

Cedric_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

Cedric_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

Cedric_EventScript_Cedric::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_CEDRIC, Cedric_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox Cedric_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_CEDRIC, Cedric_Text_Defeat
	goto Cedric_EventScript_Defeated
	end

Cedric_EventScript_PostBattleSpeech::
	msgbox Cedric_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Cedric_EventScript_Defeated::
	setvar VAR_0x8004, FANCOUNTER_DEFEATED_DRAKE
	special Script_TryGainNewFanFromCounter
	setflag FLAG_DEFEATED_ELITE_4_CEDRIC
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox Cedric_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Cedric_Text_IntroSpeech:
	.string "I am the last of the POKéMON LEAGUE\n"
	.string "ELITE FOUR, CEDRIC the real DRAGON master!\p"
	.string "In their natural state, POKéMON are\n"
	.string "wild living things. They are free.\p"
	.string "At times, they hinder us.\n"
	.string "At times, they help us.\p"
	.string "For us to battle with POKéMON as\n"
	.string "partners, do you know what it takes?\p"
	.string "Do you know what is needed?\p"
	.string "If you don't, then you will never\n"
	.string "prevail over me!$"

Cedric_Text_Defeat:
	.string "Superb, it should be said.$"

Cedric_Text_PostBattleSpeech:
	.string "You deserve every credit for coming\n"
	.string "this far as a TRAINER of POKéMON.\p"
	.string "You do seem to know what is needed.\p"
	.string "Yes, what a TRAINER needs is a\n"
	.string "virtuous heart.\p"
	.string "POKéMON touch the good hearts of\n"
	.string "TRAINERS and learn good from wrong.\p"
	.string "They touch the good hearts of\n"
	.string "TRAINERS and grow strong.\p"
	.string "Go! Go onwards!\n"
	.string "The CHAMPION is waiting!$"