Enrico_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Enrico_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, Enrico_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Enrico_OnWarp
	.byte 0

Enrico_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Enrico_EventScript_PlayerTurnNorth
	.2byte 0

Enrico_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

Enrico_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 2, Enrico_EventScript_WalkInCloseDoor
	.2byte 0

Enrico_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 3
	releaseall
	end

Enrico_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_ENRICO, Enrico_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 3, Enrico_EventScript_CloseDoor
	end

Enrico_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

Enrico_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

Enrico_EventScript_Enrico::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_ENRICO, Enrico_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox Enrico_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ENRICO, Enrico_Text_Defeat
	goto Enrico_EventScript_Defeated
	end

Enrico_EventScript_PostBattleSpeech::
	msgbox Enrico_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Enrico_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_ENRICO
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox Enrico_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Enrico_Text_IntroSpeech:
	.string "Welcome, my name is ENRICO\n"
	.string "of the ELITE FOUR.\p"
	.string "I am the master of the ICE TYPE\n"
	.string "you may know me under\p"
	.string "the name of ZOCKGEFROREN.\p"
	.string "Do you really think you have what it\n"
	.string "takes to end my cold reign?\p"
	.string "How brave of you well then\n"
	.string "show me what you got!$"

Enrico_Text_Defeat:
	.string "You and your POKéMON…\n"
	.string "Melted me away!\p"
	.string "This is really quite amusing.\p"
	.string "I am surprise that my fighting skills\n"
	.string "failed to harm you and your\p"
	.string "POKEMON. Well Congratulations.$"

Enrico_Text_PostBattleSpeech:
	.string "Advance to the next room.\p"
	.string "And there, confirm the truly fearsome\n"
	.string "side of the POKéMON LEAGUE.$"
