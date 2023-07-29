// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableComponent.h"
#include "NextRoomButton.generated.h"

UCLASS()
class RAGSHLY_API ANextRoomButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANextRoomButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, Category = "Selector")
		class UInteractableComponent* InteractableComponent;

	UPROPERTY(EditAnywhere, Category = "Selector")
		USceneComponent* SceneRootComponent;
	UPROPERTY(EditAnywhere, Category = "Selector")
		FVector orientation;
	UFUNCTION()
		void OnSelected(UInteractableComponent* InInteractable);
	virtual void Tick(float DeltaTime) override;

};
