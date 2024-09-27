Tau_Outside_Kyurem_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Tau4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Tau4_OnResume
	.byte 0

Tau4_OnTransition:
	call_if_set FLAG_CAUGHT_KYUREM , Tau4_EventScript_HideKyurem
	call_if_unset FLAG_CAUGHT_KYUREM , Tau4_EventScript_TryShowKyurem
	end

Tau4_EventScript_HideKyurem::
	setflag FLAG_HIDE_KYUREM
	return

Tau4_EventScript_TryShowKyurem::
	goto_if_set FLAG_DEFEATED_KYUREM, Common_EventScript_NopReturn
	clearflag FLAG_HIDE_KYUREM
	return

Tau4_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Tau4_EventScript_TryRemoveKyurem
	end

Tau4_EventScript_TryRemoveKyurem::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject 1
	return

Tau4_EventScript_Kyurem::
	lockall
	playmoncry SPECIES_KYUREM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    setwildbattle SPECIES_KYUREM, 75, ITEM_DNA_SPLICERS
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Tau4_EventScript_DefeatedKyurem
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Tau4_EventScript_RanFromKyurem
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Tau4_EventScript_RanFromKyurem
	setflag FLAG_CAUGHT_KYUREM
	release
	end
	
Tau4_EventScript_DefeatedKyurem::
	setflag FLAG_DEFEATED_KYUREM
	setvar VAR_0x8004, SPECIES_KYUREM
	goto Common_EventScript_LegendaryFlewAway
	end

Tau4_EventScript_RanFromKyurem::
	setvar VAR_0x8004, SPECIES_KYUREM
	goto Common_EventScript_LegendaryFlewAway
	end

