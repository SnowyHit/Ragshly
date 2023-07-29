// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoom.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class RAGSHLY_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		ADungeonRoom* GetCurrentRoomByLocation();
	UFUNCTION()
		bool NeighbourExists(FVector2D roomPosition, FVector actorForwardVector);
	bool IsOccupied(FVector2D position);
	bool IsUnlocked(FVector2D position);
	void SpawnRoom(FVector actorForwardVector);
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<ADungeonRoom*> SpawnedRooms;
	UPROPERTY(EditAnywhere, Category = "Rooms")
	FVector offsetVector;
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<TSubclassOf<ADungeonRoom>> dungeonRooms;
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<FVector2D> occupiedPositions;
	UPROPERTY(EditAnywhere, Category = "Rooms")
	TArray<FVector2D> unlockedPositions;

	TWeakObjectPtr<ARagshlyCharacter> PlayerCharacterPtr;
};
