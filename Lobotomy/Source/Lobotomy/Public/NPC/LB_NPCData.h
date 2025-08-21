// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LB_NPCData.generated.h"

 // ---------- ----- For Monster ----- ----------
UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Investigation UMETA(DisplayName = "Investigation"),
	Chase UMETA(DisplayName = "Chase"),
	Disappeared UMETA(DisplayName = "Disappeared"),
};
// ---------- ---------- ---------- ---------- ----------

 // ---------- ----- For Patient ----- ----------
UENUM(BlueprintType)
enum class EPatientState : uint8
{
	None UMETA(DisplayName = "None"),
	Strafe UMETA(DisplayName = "Strafe"),
	Action UMETA(DisplayName = "Action"),
};
// ---------- ---------- ---------- ---------- ----------