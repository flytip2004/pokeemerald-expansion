Meliodas_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Meliodas_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Meliodas_OnWarp
	map_script MAP_SCRIPT_ON_TRANSITION, Meliodas_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Meliodas_OnFrame
	.byte 0

Meliodas_OnTransition:
	setflag FLAG_MET_SCOTT_IN_EVERGRANDE
	setflag FLAG_HIDE_EVER_GRANDE_POKEMON_CENTER_1F_SCOTT
	end

Meliodas_OnLoad:
	call_if_set FLAG_DEFEATED_ELITE_4_MELIODAS, Meliodas_EventScript_ResetAdvanceToNextRoom
	call_if_eq VAR_ELITE_4_STATE, 1, Meliodas_EventScript_CloseDoor
	end

Meliodas_EventScript_ResetAdvanceToNextRoom::
	call PokemonLeague_EliteFour_EventScript_ResetAdvanceToNextRoom
	return

Meliodas_EventScript_CloseDoor::
	call PokemonLeague_EliteFour_EventScript_CloseDoor
	return

Meliodas_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Meliodas_EventScript_PlayerTurnNorth
	.2byte 0

Meliodas_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

Meliodas_OnFrame:
	map_script_2 VAR_ELITE_4_STATE, 0, Meliodas_EventScript_WalkInCloseDoor
	.2byte 0

Meliodas_EventScript_WalkInCloseDoor::
	lockall
	call PokemonLeague_EliteFour_EventScript_WalkInCloseDoor
	setvar VAR_ELITE_4_STATE, 1
	releaseall
	end

Meliodas_EventScript_Meliodas::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_ELITE_4_MELIODAS, Meliodas_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox Meliodas_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MELIODAS, Meliodas_Text_Defeat
	goto Meliodas_EventScript_Defeated
	end

Meliodas_EventScript_PostBattleSpeech::
	msgbox Meliodas_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Meliodas_EventScript_Defeated::
	setflag FLAG_DEFEATED_ELITE_4_MELIODAS 
	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
	msgbox Meliodas_Text_PostBattleSpeech, MSGBOX_DEFAULT
	release
	end

Meliodas_Text_IntroSpeech:
	.string "Welcome, challenger!\n"
	.string "I'm MELIODAS of the ELITE FOUR.\p"
	.string "I like that look you're giving me.\n"
	.string "I guess you'll give me a good match.\l"
	.string "That's good! Looking real good!\p"
	.string "All right! You and me, let's enjoy\n"
	.string "a battle that can only be staged\l"
	.string "here in the POKéMON LEAGUE!$"

Meliodas_Text_Defeat:
	.string "Well, how do you like that? I lost!\n"
	.string "Eh, it was fun, so it doesn't matter.$"

Meliodas_Text_PostBattleSpeech:
	.string "Well, listen to what this loser has\n"
	.string "to say.\p"
	.string "You've got what it takes to go far.\n"
	.string "Now, go on to the next room and enjoy\l"
	.string "your next battle!$"
