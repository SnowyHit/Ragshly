// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NextRoomButton.h"
#include "DungeonRoom.generated.h"

UCLASS()
class RAGSHLY_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void SpawnButtons(FVector incomingDirection);

	void RemoveButton(FVector direction);

	UPROPERTY(EditAnywhere, category = "Data")
		TSubclassOf<ANextRoomButton> nextRoomButtonRef;
;	UPROPERTY(EditAnywhere, category = "Data")
		TArray<FTransform> doorTransforms;
	UPROPERTY(EditAnywhere, category = "Data")
		FVector roomSize;
	UPROPERTY(EditAnywhere, category = "Data")
		FVector2D roomPosition;
	UPROPERTY(EditAnywhere, category = "Data")
		TArray<ANextRoomButton*> SpawnedNextRoomButtons;
};
