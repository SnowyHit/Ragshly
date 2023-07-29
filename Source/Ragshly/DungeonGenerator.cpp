// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include "DungeonRoom.h"
#include "Math/NumericLimits.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	ADungeonRoom* spawnedRoom = GetWorld()-> SpawnActor<ADungeonRoom>(dungeonRooms[0], SpawnLocation, SpawnRotation);
	spawnedRoom->SpawnButtons(FVector(0,0,0));
	spawnedRoom->roomPosition = FVector2D(0, 0);
	occupiedPositions.AddUnique(spawnedRoom->roomPosition);
	SpawnedRooms.Add(spawnedRoom);
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ADungeonRoom* ADungeonGenerator::GetCurrentRoomByLocation()
{
	ADungeonRoom* currentRoom = SpawnedRooms[0];

	FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	float CurrentSmallestDistance = 1000000;
	for (int i = 0; i < SpawnedRooms.Num(); i++)
	{
		if (CurrentSmallestDistance > FVector::Distance(SpawnedRooms[i]->GetActorLocation(), location))
		{
			currentRoom = SpawnedRooms[i];
			CurrentSmallestDistance = FVector::Distance(SpawnedRooms[i]->GetActorLocation(), location);
		}
	}

	return currentRoom;
}
bool ADungeonGenerator::NeighbourExists(FVector2D roomPosition ,FVector actorForwardVector)
{
	for (int i = 0; i < SpawnedRooms.Num(); i++)
	{
		if (SpawnedRooms[i]->roomPosition.Equals(roomPosition + FVector2D(actorForwardVector.X, actorForwardVector.Y)))
		{
			for (int j = 0; j < SpawnedRooms[i]->SpawnedNextRoomButtons.Num(); j++)
			{
				if (SpawnedRooms[i]->SpawnedNextRoomButtons[j]->orientation.Equals(actorForwardVector * -1))
				{
					SpawnedRooms[i]->SpawnedNextRoomButtons[j]->Destroy();
				}
			}
			return true;
		}
	}
	return false;
}
bool ADungeonGenerator::IsOccupied(FVector2D position)
{
	for (int i = 0; i < occupiedPositions.Num(); i++)
	{
		if (occupiedPositions[i].Equals(position))
		{
			return true;
		}
	}
	return false;
}
bool ADungeonGenerator::IsUnlocked(FVector2D position)
{
	for (int i = 0; i < unlockedPositions.Num(); i++)
	{
		if (unlockedPositions[i].Equals(position))
		{
			return true;
		}
	}
	return false;
}
void ADungeonGenerator::SpawnRoom(FVector actorForwardVector)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("SpawnRoomWorked"));
	ADungeonRoom* currentRoom = GetCurrentRoomByLocation();
	currentRoom->RemoveButton(actorForwardVector);
	ADungeonRoom* spawnedRoom = GetWorld()->SpawnActor<ADungeonRoom>(dungeonRooms[0], currentRoom->GetActorLocation(), GetActorRotation());
	spawnedRoom->SetActorLocation(currentRoom->GetActorLocation() + (actorForwardVector * spawnedRoom->roomSize * 100));
	spawnedRoom->roomPosition = currentRoom->roomPosition + FVector2D(actorForwardVector.X, actorForwardVector.Y);
	occupiedPositions.AddUnique(spawnedRoom->roomPosition);
	spawnedRoom->SpawnButtons(actorForwardVector);
	SpawnedRooms.Add(spawnedRoom);
}

