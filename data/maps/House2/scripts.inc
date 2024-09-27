House2_MapScripts::
	.byte 0

House_EventScript_Elena::
	trainerbattle_single TRAINER_ELENA, House_Text_ElenaIntro, House_Text_ElenaDefeat
	msgbox House_Text_ElenaPostBattle, MSGBOX_AUTOCLOSE
	end


