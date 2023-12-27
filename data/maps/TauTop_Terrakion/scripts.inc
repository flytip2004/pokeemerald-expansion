TauTop_Terrakion_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau2_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau2_OnResume
	.byte 0

Tau2_OnTransition:
	call_if_set FLAG_CAUGHT_TERRAKION, Tau2_EventScript_HideTerrakion
	call_if_unset FLAG_CAUGHT_TERRAKION, Tau2_EventScript_TryShowTerrakion
	end

Tau2_EventScript_HideTerrakion::
	setflag FLAG_HIDE_TERRAKION
	return

Tau2_EventScript_TryShowTerrakion::
	goto_if_set FLAG_DEFEATED_TERRAKION, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_TERRAKION
	return

Tau2_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau2_EventScript_TryRemoveTerrakion
	end

Tau2_EventScript_TryRemoveTerrakion::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau2_EventScript_Terrakion::
	lockall
	playmoncry SPECIES_TERRAKION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_TERRAKION, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau2_EventScript_DefeatedTerrakion
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau2_EventScript_RanFromTerrakion
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau2_EventScript_RanFromTerrakion
	setflag FLAG_CAUGHT_TERRAKION
	release
	end
	
Tau2_EventScript_DefeatedTerrakion::
	setflag FLAG_DEFEATED_TERRAKION
	setvar VAR_0x8004, SPECIES_TERRAKION
	goto Common_EventScript_LegendaryFlewAway
	end

Tau2_EventScript_RanFromTerrakion::
	setvar VAR_0x8004, SPECIES_TERRAKION
	goto Common_EventScript_LegendaryFlewAway
	end
