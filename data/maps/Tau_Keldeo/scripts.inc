Tau_Keldeo_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau6_OnResume
	.byte 0

Tau6_OnTransition:
	call_if_set FLAG_CAUGHT_KELDEO, Tau6_EventScript_HideKeldeo
	call_if_unset FLAG_CAUGHT_KELDEO, Tau6_EventScript_TryShowKeldeo
	end

Tau6_EventScript_HideKeldeo::
	setflag FLAG_HIDE_KELDEO
	return

Tau6_EventScript_TryShowKeldeo::
	goto_if_set FLAG_DEFEATED_KELDEO, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_KELDEO
	return

Tau6_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau6_EventScript_TryRemoveKeldeo
	end

Tau6_EventScript_TryRemoveKeldeo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau6_EventScript_Keldeo::
	lockall
	playmoncry SPECIES_KELDEO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_KELDEO, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau6_EventScript_DefeatedKeldeo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau6_EventScript_RanFromKeldeo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau6_EventScript_RanFromKeldeo
	setflag FLAG_CAUGHT_KELDEO
	release
	end
	
Tau6_EventScript_DefeatedKeldeo::
	setflag FLAG_DEFEATED_KELDEO
	setvar VAR_0x8004, SPECIES_KELDEO
	goto Common_EventScript_LegendaryFlewAway
	end

Tau6_EventScript_RanFromKeldeo::
	setvar VAR_0x8004, SPECIES_KELDEO
	goto Common_EventScript_LegendaryFlewAway
	end
