// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_PickBackDroppedFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/Food.h"

EBTNodeResult::Type UBT_PickBackDroppedFood::CodeToExecute()
{	
	AFood* FoodDropped = Cast<AFood>(BlackboardComponent->GetValueAsObject("FoodDropped"));

	if(FoodDropped == nullptr)
	{
		BlackboardComponent->ClearValue("SpotLocationToGo");
		return EBTNodeResult::Failed;
	}
	float DistFromFood = FVector::Dist(FoodDropped->GetActorLocation(), AICharacter->GetActorLocation());

	if(DistFromFood <= 175)
	{
		AICharacter->SetNearFoodActor(FoodDropped);
		AICharacter->InteractWithItem();
		BlackboardComponent->SetValueAsObject("FoodCarrying", FoodDropped);
		BlackboardComponent->ClearValue("FoodDropped");
		return EBTNodeResult::Succeeded;
	}	

	//init RayCast
	FVector StartLineTrace = AIController->GetPawn()->GetActorLocation();
	FVector DirectionTowardFood = (FoodDropped->GetActorLocation() - StartLineTrace).GetSafeNormal();
	FVector EndLineTrace = StartLineTrace + (DirectionTowardFood * AIController->GetSightDistance());
	
	FHitResult* HitResult = new FHitResult();
	
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	TraceParams->AddIgnoredActor(AIController->GetPawn());
	
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartLineTrace, EndLineTrace, ECollisionChannel::ECC_WorldStatic, *TraceParams))
	{
		AFood* FoodHitted = Cast<AFood>(HitResult->GetActor());

		UE_LOG(LogTemp, Warning, TEXT("cast hitted this : %s"), *HitResult->GetActor()->GetName())
		
		if (FoodHitted == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Food not in sight"))
			BlackboardComponent->ClearValue("FoodDropped");
			return EBTNodeResult::Failed;
		}

		if(FoodHitted != FoodDropped)
		{
			UE_LOG(LogTemp, Warning, TEXT("Wrong food"))
			BlackboardComponent->ClearValue("FoodDropped");
			return EBTNodeResult::Failed;
		}
		
		BlackboardComponent->SetValueAsVector("FoodDroppedLocation", FoodHitted->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	
	BlackboardComponent->ClearValue("FoodDropped");
	return EBTNodeResult::Failed;
}
