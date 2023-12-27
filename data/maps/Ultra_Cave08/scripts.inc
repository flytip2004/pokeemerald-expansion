Ultra_Cave08_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Ultra7_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Ultra7_OnResume
	.byte 0

Ultra7_OnTransition:
	call_if_set FLAG_CAUGHT_GUZZLORD , Ultra7_EventScript_HideGuzzlord
	call_if_unset FLAG_CAUGHT_GUZZLORD , Ultra7_EventScript_TryShowGuzzlord
	call_if_set FLAG_CAUGHT_STAKATAKA, Ultra7_EventScript_HideStakataka
	call_if_unset FLAG_CAUGHT_STAKATAKA , Ultra7_EventScript_TryShowStakataka
	end

Ultra7_EventScript_HideGuzzlord::
	setflag FLAG_HIDE_GUZZLORD
	return

Ultra7_EventScript_TryShowGuzzlord::
	goto_if_set FLAG_DEFEATED_GUZZLORD, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_GUZZLORD
	return

Ultra7_EventScript_HideStakataka::
	setflag FLAG_HIDE_STAKATAKA
	return

Ultra7_EventScript_TryShowStakataka::
	goto_if_set FLAG_DEFEATED_STAKATAKA, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_STAKATAKA
	return

Ultra7_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra7_EventScript_TryRemoveGuzzlord
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Ultra7_EventScript_TryRemoveStakataka
	end

Ultra7_EventScript_TryRemoveGuzzlord::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra7_EventScript_TryRemoveStakataka::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Ultra7_EventScript_Guzzlord::
	lockall
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_GUZZLORD, 80
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra7_EventScript_DefeatedGuzzlord
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra7_EventScript_RanFromGuzzlord
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra7_EventScript_RanFromGuzzlord
	setflag FLAG_CAUGHT_GUZZLORD
	release
	end

Ultra7_EventScript_Stakataka::
	lockall
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_STAKATAKA, 75
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Ultra7_EventScript_DefeatedStakataka
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Ultra7_EventScript_RanFromStakataka
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Ultra7_EventScript_RanFromStakataka
	setflag FLAG_CAUGHT_STAKATAKA
	release
	end
	
Ultra7_EventScript_DefeatedGuzzlord::
	setflag FLAG_DEFEATED_GUZZLORD
	setvar VAR_0x8004, SPECIES_GUZZLORD
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra7_EventScript_RanFromGuzzlord::
	setvar VAR_0x8004, SPECIES_GUZZLORD
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra7_EventScript_DefeatedStakataka::
	setflag FLAG_DEFEATED_STAKATAKA
	setvar VAR_0x8004, SPECIES_STAKATAKA
	goto Common_EventScript_LegendaryFlewAway
	end

Ultra7_EventScript_RanFromStakataka::
	setvar VAR_0x8004, SPECIES_STAKATAKA
	goto Common_EventScript_LegendaryFlewAway
	end





