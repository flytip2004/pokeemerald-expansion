Ultra_Cave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra1_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra1_OnResume
	.byte 0

Ultra1_OnTransition:
	call_if_set FLAG_CAUGHT_POIPOLE , Ultra1_EventScript_HidePoipole
	call_if_unset FLAG_CAUGHT_POIPOLE , Ultra1_EventScript_TryShowPoipole
	end

Ultra1_EventScript_HidePoipole::
	setflag FLAG_HIDE_POIPOLE
	return

Ultra1_EventScript_TryShowPoipole::
	goto_if_set FLAG_DEFEATED_POIPOLE, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_POIPOLE
	return

Ultra1_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra1_EventScript_TryRemovePoipole
	end

Ultra1_EventScript_TryRemovePoipole::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra1_EventScript_Poipole::
	lockall
	playmoncry SPECIES_POIPOLE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_POIPOLE, 50
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra1_EventScript_DefeatedPoipole
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra1_EventScript_RanFromPoipole
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra1_EventScript_RanFromPoipole
	setflag FLAG_CAUGHT_POIPOLE
	release
	end
	
Ultra1_EventScript_DefeatedPoipole::
	setflag FLAG_DEFEATED_POIPOLE
	setvar VAR_0x8004, SPECIES_POIPOLE
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra1_EventScript_RanFromPoipole::
	setvar VAR_0x8004, SPECIES_POIPOLE
	goto Common_EventScript_LegendaryFlewAway
	end



