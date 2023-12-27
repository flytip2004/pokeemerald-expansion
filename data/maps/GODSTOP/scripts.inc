GODSTOP_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, God_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, God_OnResume
	.byte 0

God_OnTransition:
	call_if_set FLAG_CAUGHT_ARCEUS, God_EventScript_HideArceus
	call_if_unset FLAG_CAUGHT_ARCEUS, God_EventScript_TryShowArceus
	end

God_EventScript_HideArceus::
	setflag FLAG_HIDE_ARCEUS
	return

God_EventScript_TryShowArceus::
	goto_if_set FLAG_DEFEATED_ARCEUS, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_ARCEUS
	return

God_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, God_EventScript_TryRemoveArceus
	end

God_EventScript_TryRemoveArceus::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

God_EventScript_Arceus::
	lockall
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_ARCEUS, 80
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, God_EventScript_DefeatedArceus
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, God_EventScript_RanFromArceus
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, God_EventScript_RanFromArceus
	setflag FLAG_CAUGHT_ARCEUS
	release
	end
	
God_EventScript_DefeatedArceus::
	setflag FLAG_DEFEATED_ARCEUS
	setvar VAR_0x8004, SPECIES_ARCEUS
	goto Common_EventScript_LegendaryFlewAway
	end

God_EventScript_RanFromArceus::
	setvar VAR_0x8004, SPECIES_ARCEUS
	goto Common_EventScript_LegendaryFlewAway
	end
