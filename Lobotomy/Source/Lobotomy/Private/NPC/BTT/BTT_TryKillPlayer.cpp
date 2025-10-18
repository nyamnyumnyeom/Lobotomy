// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BTT/BTT_TryKillPlayer.h"
#include "AIController.h"
#include "NPC/LB_Monster_ChainSawMan.h"
#include "LB_GM.h"
#include "Kismet/GameplayStatics.h"

UBTT_TryKillPlayer::UBTT_TryKillPlayer()
{
	NodeName = TEXT("Try Kill Player");
}

EBTNodeResult::Type UBTT_TryKillPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)	return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)	return EBTNodeResult::Failed;

	ALB_Monster_ChainSawMan* Monster_ChainSawMan = Cast<ALB_Monster_ChainSawMan>(ControlledPawn);
	if (!Monster_ChainSawMan) return EBTNodeResult::Failed;

	ALB_GM* GM = Cast<ALB_GM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return EBTNodeResult::Failed;

	Monster_ChainSawMan->SetActorRotationToPlayer();

	GM->PlayerDeathLogic(Monster_ChainSawMan->GetActorLocation());

	return EBTNodeResult::Succeeded;
}
