.set LOCALID_ANABEL, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

Elena_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Elena_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Elena_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Elena_OnFrame
	.byte 0

Elena_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

Elena_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Elena_EventScript_PlayerTurnNorth
	.2byte 0

Elena_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

Elena_OnFrame:
	map_script_2 VAR_TEMP_1, 0, Elena_EventScript_EnterRoom
	.2byte 0

Elena_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, Elena_Movement_PlayerApproachElena
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto Elena_EventScript_Elena
	releaseall
	end

Elena_Movement_PlayerApproachElena:
	walk_up
	walk_up
	step_end

Elena_EventScript_Elena::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox Elena_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ELENA, Elena_Text_Defeat
	goto Elena_EventScript_Defeated
	end

Elena_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox Elena_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Elena_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, Elena_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call Elena_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Elena_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, Elena_EventScript_BrendanAdvice
	end

Elena_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

Elena_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

Elena_EventScript_MayAdvice::
	msgbox Elena_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call Elena_EventScript_RivalLookBackAndForth
	msgbox Elena_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto Elena_EventScript_BirchArrivesExitForHoF
	end

Elena_EventScript_BrendanAdvice::
	msgbox Elena_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call Elena_EventScript_RivalLookBackAndForth
	msgbox Elena_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto Elena_EventScript_BirchArrivesExitForHoF
	end

Elena_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, Elena_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Elena_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox Elena_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_ANABEL, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_ANABEL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Elena_Text_ElenaComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_ANABEL, Elena_Movement_ElenaExitStart
	applymovement OBJ_EVENT_ID_PLAYER, Elena_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, Elena_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Elena_Text_ElenaWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Elena_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, Elena_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_ANABEL, Elena_Movement_ElenaExit
	applymovement OBJ_EVENT_ID_PLAYER, Elena_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_ELENA_HALL, 7, 16
	waitstate
	releaseall
	end

Elena_EventScript_MayCongratulations::
	msgbox Elena_Text_MayCongratulations, MSGBOX_DEFAULT
	return

Elena_EventScript_BrendanCongratulations::
	msgbox Elena_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

Elena_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, Elena_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Elena_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, Elena_Movement_RivalLookBackAndForth
	waitmovement 0
	return

Elena_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

Elena_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

Elena_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

Elena_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

Elena_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

Elena_Movement_ElenaExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

Elena_Movement_ElenaExit:
	walk_up
	delay_8
	set_invisible
	step_end

Elena_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

Elena_Text_IntroSpeech:
	.string "ELENA: Welcome, {PLAYER}{KUN}.\p"
	.string "Do you really think you can…\n"
	.string "beat me?\l"
	.string "I am ELENA the last champion.\p"
	.string "I hope you are prepared for\p"
	.string "pain and suffering$"

Elena_Text_Defeat:
	.string "I, the CHAMPION, fall in defeat…\p"
	.string "HOW IS THAT EVEN POSSIBLE.\n"
	.string "I AM THE GOD OF THIS WORLD.\l"
	.string "YOU HEAR ME!!!!!!!$"

Elena_Text_PostBattleSpeech:
	.string "ELENA: FUCK YOU AND PLEASE\n"
	.string "JUMP OF A FUCKING BRIDGE YOU\p"
	.string "PIECE OF ...\n"
	.string "WHY YOU STILL HERE?\p"
	.string "OH RIGHT, its kinda my job to\n"
	.string "crown you the next CHAMPION.\p"
	.string "I now proclaim you to be the new\n"
	.string "HOENN region and that what lays beyond…$"

Elena_Text_MayAdvice:
	.string "MAY: {PLAYER}{KUN}!\p"
	.string "Here's some advice before you challenge\n"
	.string "the CHAMPION…$"

Elena_Text_MayItsAlreadyOver:
	.string "MAY: Huh?\n"
	.string "What, what, what?\p"
	.string "{PLAYER}{KUN}…\n"
	.string "Could it be that…\l"
	.string "It's already over?$"

Elena_Text_BrendanAdvice:
	.string "BRENDAN: {PLAYER}!\p"
	.string "How would you like some advice before\n"
	.string "you challenge the CHAMPION?…$"

Elena_Text_BrendanYouveWon:
	.string "BRENDAN: {PLAYER}…\p"
	.string "Are you trying to tell me…\n"
	.string "You've beaten the CHAMPION?$"

Elena_Text_BirchArriveRatePokedex:
	.string "PROF. BIRCH: See?\n"
	.string "What did I tell you, {RIVAL}?\p"
	.string "Didn't I tell you that you don't need\n"
	.string "to worry about {PLAYER}{KUN}?\p"
	.string "… … … … … … … …\n"
	.string "{PLAYER}{KUN}, you've finally done it.\p"
	.string "When I heard that you defeated your\n"
	.string "own father at the PETALBURG GYM,\l"
	.string "I thought perhaps you had a chance…\p"
	.string "But to think you've actually become\n"
	.string "the CHAMPION!\p"
	.string "Ah, yes!\p"
	.string "What became of your POKéDEX?\n"
	.string "Here, let me see.$"

Elena_Text_BirchCongratulations:
	.string "PROF. BIRCH: Anyways,\n"
	.string "congratulations!\p"
	.string "Now, go proudly into the final room!$"

Elena_Text_ElenaComeWithMe:
	.string "ELENA: {PLAYER}{KUN}…\p"
	.string "Come with me. NOW!$"

Elena_Text_ElenaWaitOutside:
	.string "ELENA: I'm sorry, but…\p"
	.string "From here on, only those TRAINERS who\n"
	.string "have become CHAMPIONS may enter.\p"
	.string "You'll have to wait outside with\n"
	.string "PROF. BIRCH.$"

Elena_Text_MayCongratulations:
	.string "MAY: Groan…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "I'm just joking! That's okay!\n"
	.string "That's the rule!\p"
	.string "{PLAYER}{KUN}!\n"
	.string "Honestly, congratulations!$"

Elena_Text_BrendanCongratulations:
	.string "BRENDAN: Whaaaat?! … … … … …\n"
	.string "… … … … … … … …\p"
	.string "It can't be helped if that's the rule.\p"
	.string "{PLAYER}, way to go!\n"
	.string "Congratulations!$"
