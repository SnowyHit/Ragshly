// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RagshlyCharacter.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "InteractableComponent.generated.h"

/** Event fired if player activated interaction */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableInteractedDelegate, class UInteractableComponent*, InInteractableComponent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAGSHLY_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

	UPROPERTY(BlueprintAssignable)
		FInteractableInteractedDelegate OnInteracted;

	UPROPERTY(EditAnywhere, Category = "Interact")
		float MaxInteractDistance;

	UPROPERTY(EditAnywhere, Category = "Interact")
		USphereComponent* TriggerCollisionComponent;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	uint32 InputActionBindHandle;

	UFUNCTION(BlueprintCallable)
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnInteractionSelected();

	/*void ToggleUIActive(bool InIsActive);*/
	void StopCheck();

	uint8 bIsActive : 1;
	uint8 bIsInteracted : 1;

	TWeakObjectPtr<ARagshlyCharacter> PlayerCharacterPtr;
	TWeakObjectPtr<UEnhancedInputComponent> InputComponentPtr;;
		
};
