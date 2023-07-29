// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRoom.h"
#include "NextRoomButton.h"
#include "DungeonGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADungeonRoom::ADungeonRoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonRoom::SpawnButtons(FVector incomingDirection)
{
	for (int i = 0; i < doorTransforms.Num(); i++)
	{
		if (FMath::RandRange(0, 100) > 50)
		{
			AActor* actorref = UGameplayStatics::GetActorOfClass(GetWorld(), ADungeonGenerator::StaticClass());
			ADungeonGenerator* genref = Cast<ADungeonGenerator>(actorref);
			FVector Forward = UKismetMathLibrary::GetForwardVector(FRotator(doorTransforms[i].GetRotation()));
			bool doesNeighborExist = genref->NeighbourExists(roomPosition, Forward);
			if(!genref->IsUnlocked(roomPosition + FVector2D(Forward.X, Forward.Y)))
			{
				genref->occupiedPositions.Add(roomPosition + FVector2D(Forward.X, Forward.Y));
				continue;
			}
		}

		FVector SpawnLocation = GetActorLocation() + doorTransforms[i].GetLocation();
		FRotator SpawnRotation = FRotator(doorTransforms[i].GetRotation());

		if (incomingDirection.Equals(UKismetMathLibrary::GetForwardVector(SpawnRotation) * -1))
			continue;

		AActor* DungeonGenActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ADungeonGenerator::StaticClass());
		ADungeonGenerator* DungeonGenReference = Cast<ADungeonGenerator>(DungeonGenActorRef);
		FVector forwardVector = UKismetMathLibrary::GetForwardVector(SpawnRotation);
		bool doesNeighborExist = DungeonGenReference->NeighbourExists(roomPosition, forwardVector);
		bool isOccupied = DungeonGenReference->IsOccupied(roomPosition+ FVector2D(forwardVector.X,forwardVector.Y));
		if (!doesNeighborExist && !isOccupied)
		{
			ANextRoomButton* roombuttonRef = GetWorld()->SpawnActor<ANextRoomButton>(nextRoomButtonRef, SpawnLocation, SpawnRotation);
			roombuttonRef->orientation = roombuttonRef->GetActorForwardVector();
			DungeonGenReference->unlockedPositions.AddUnique(roomPosition + FVector2D(forwardVector.X, forwardVector.Y));
			SpawnedNextRoomButtons.Add(roombuttonRef);
		}
	}
}
void ADungeonRoom::RemoveButton(FVector direction)
{
	for (int i = 0; i < SpawnedNextRoomButtons.Num(); i++)
	{
		if (SpawnedNextRoomButtons[i]->orientation.Equals(direction))
		{
			ANextRoomButton* refButton = SpawnedNextRoomButtons[i];
			SpawnedNextRoomButtons.RemoveAt(i);
			refButton->Destroy();
		}
		
	}
	
}

