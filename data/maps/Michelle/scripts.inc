Michelle_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FinalLeageu_MichelleRoom_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FinalLeageu_MichelleRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FinalLeageu_MichelleRoom_OnFrame
	.byte 0

FinalLeageu_MichelleRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, FinalLeageu_MichelleRoom_EventScript_PlayerTurnNorth
	.2byte 0

FinalLeageu_MichelleRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

FinalLeageu_MichelleRoom_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 1, FinalLeageu_MichelleRoom_EventScript_WalkInCloseDoor
	.2byte 0

FinalLeageu_MichelleRoom_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 2
	releaseall
	end

FinalLeageu_MichelleRoom_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_LARA, FinalLeageu_MichelleRoom_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 2, FinalLeageu_MichelleRoom_EventScript_CloseDoor
	end

FinalLeageu_MichelleRoom_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

FinalLeageu_MichelleRoom_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

FinalLeageu_MichelleRoom_EventScript_Michelle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_LARA, FinalLeageu_MichelleRoom_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox FinalLeageu_MichelleRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LARA, FinalLeageu_MichelleRoom_Text_Defeat
	goto FinalLeageu_MichelleRoom_EventScript_Defeated
	end

FinalLeageu_MichelleRoom_EventScript_PostBattleSpeech::
	msgbox FinalLeageu_MichelleRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

FinalLeageu_MichelleRoom_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_LARA
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox EverGrandeCity_PhoebesRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

FinalLeageu_MichelleRoom_Text_IntroSpeech:
	.string "Ahahaha!\p"
	.string "I'm LARA of the ELITE FOUR.\n"
	.string "I did my training on a secret flower field.\p"
	.string "While I trained, I gained the ability\n"
	.string "to commune with FAIRY-type POKéMON.\p"
	.string "Yes, the bond I developed with POKéMON\n"
	.string "is extremely tight.\p"
	.string "So, come on, just try and see if you can\n"
	.string "even inflict damage on my POKéMON!$"

FinalLeageu_MichelleRoom_Text_Defeat:
	.string "Oh, darn.\n"
	.string "I've gone and lost.$"

FinalLeageu_MichelleRoom_Text_PostBattleSpeech:
	.string "There's a definite bond between you\n"
	.string "and your POKéMON, too.\p"
	.string "I didn't recognize it, so it's only\n"
	.string "natural that I lost.\p"
	.string "Yup, I'd like to see how far your bond\n"
	.string "will carry you.\p"
	.string "Go ahead, move on to the next room.$"
