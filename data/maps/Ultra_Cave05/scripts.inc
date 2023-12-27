Ultra_Cave05_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra4_OnResume
	.byte 0

Ultra4_OnTransition:
	call_if_set FLAG_CAUGHT_BUZZWOLE , Ultra4_EventScript_HideBuzzwole
	call_if_unset FLAG_CAUGHT_BUZZWOLE , Ultra4_EventScript_TryShowBuzzwole
	end

Ultra4_EventScript_HideBuzzwole::
	setflag FLAG_HIDE_BUZZWOLE
	return

Ultra4_EventScript_TryShowBuzzwole::
	goto_if_set FLAG_DEFEATED_BUZZWOLE, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_BUZZWOLE
	return

Ultra4_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra4_EventScript_TryRemoveBuzzwole
	end

Ultra4_EventScript_TryRemoveBuzzwole::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra4_EventScript_Buzzwole::
	lockall
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_BUZZWOLE, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra4_EventScript_DefeatedBuzzwole
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra4_EventScript_RanFromBuzzwole
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra4_EventScript_RanFromBuzzwole
	setflag FLAG_CAUGHT_BUZZWOLE
	release
	end
	
Ultra4_EventScript_DefeatedBuzzwole::
	setflag FLAG_DEFEATED_BUZZWOLE
	setvar VAR_0x8004, SPECIES_BUZZWOLE
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra4_EventScript_RanFromBuzzwole::
	setvar VAR_0x8004, SPECIES_BUZZWOLE
	goto Common_EventScript_LegendaryFlewAway
	end




