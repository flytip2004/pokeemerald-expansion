Ultra_Cave07_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra6_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra6_OnResume
	.byte 0

Ultra6_OnTransition:
	call_if_set FLAG_CAUGHT_CELESTEELA , Ultra6_EventScript_HideCelesteela
	call_if_unset FLAG_CAUGHT_CELESTEELA , Ultra6_EventScript_TryShowCelesteela
	call_if_set FLAG_CAUGHT_KARTANA , Ultra6_EventScript_HideKartana
	call_if_unset FLAG_CAUGHT_KARTANA , Ultra6_EventScript_TryShowKartana
	end

Ultra6_EventScript_HideCelesteela::
	setflag FLAG_HIDE_CELESTEELA
	return

Ultra6_EventScript_TryShowCelesteela::
	goto_if_set FLAG_DEFEATED_CELESTEELA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_CELESTEELA
	return

Ultra6_EventScript_HideKartana::
	setflag FLAG_HIDE_KARTANA
	return

Ultra6_EventScript_TryShowKartana::
	goto_if_set FLAG_DEFEATED_KARTANA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_KARTANA
	return

Ultra6_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra6_EventScript_TryRemoveCelesteela
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra6_EventScript_TryRemoveKartana
	end

Ultra6_EventScript_TryRemoveCelesteela::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra6_EventScript_TryRemoveKartana::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra6_EventScript_Celesteela::
	lockall
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_CELESTEELA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra6_EventScript_DefeatedCelesteela
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra6_EventScript_RanFromCelesteela
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra6_EventScript_RanFromCelesteela
	setflag FLAG_CAUGHT_CELESTEELA
	release
	end

Ultra6_EventScript_Kartana::
	lockall
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_KARTANA, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra6_EventScript_DefeatedKartana
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra6_EventScript_RanFromKartana
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra6_EventScript_RanFromKartana
	setflag FLAG_CAUGHT_KARTANA
	release
	end
	
Ultra6_EventScript_DefeatedCelesteela::
	setflag FLAG_DEFEATED_CELESTEELA
	setvar VAR_0x8004, SPECIES_CELESTEELA
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra6_EventScript_RanFromCelesteela::
	setvar VAR_0x8004, SPECIES_CELESTEELA
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra6_EventScript_DefeatedKartana::
	setflag FLAG_DEFEATED_KARTANA
	setvar VAR_0x8004, SPECIES_KARTANA
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra6_EventScript_RanFromKartana::
	setvar VAR_0x8004, SPECIES_KARTANA
	goto Common_EventScript_LegendaryFlewAway
	end



