Ultra_Cave03_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra2_OnResume
	.byte 0

Ultra2_OnTransition:
	call_if_set FLAG_CAUGHT_NIHILEGO , Ultra2_EventScript_HideNihilego
	call_if_unset FLAG_CAUGHT_NIHILEGO , Ultra2_EventScript_TryShowNihilego
	end

Ultra2_EventScript_HideNihilego::
	setflag FLAG_HIDE_NIHILEGO
	return

Ultra2_EventScript_TryShowNihilego::
	goto_if_set FLAG_DEFEATED_NIHILEGO, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_NIHILEGO
	return

Ultra2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra2_EventScript_TryRemoveNihilego
	end

Ultra2_EventScript_TryRemoveNihilego::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra2_EventScript_Nihilego::
	lockall
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_NIHILEGO, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra2_EventScript_DefeatedNihilego
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra2_EventScript_RanFromNihilego
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra2_EventScript_RanFromNihilego
	setflag FLAG_CAUGHT_NIHILEGO
	release
	end
	
Ultra2_EventScript_DefeatedNihilego::
	setflag FLAG_DEFEATED_NIHILEGO
	setvar VAR_0x8004, SPECIES_NIHILEGO
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra2_EventScript_RanFromNihilego::
	setvar VAR_0x8004, SPECIES_NIHILEGO
	goto Common_EventScript_LegendaryFlewAway
	end

