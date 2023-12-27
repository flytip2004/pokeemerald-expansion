.set LOCALID_NURSE, 1

BlessedCityCenter1f_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BlessedCityCenter1f_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

BlessedCityCenter1f_OnTransition::
	setrespawn HEAL_LOCATION_BLESSEDCITY
	end

Pokecenter_Employee_Simple3::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end
