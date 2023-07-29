// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TriggerCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractTrigger"));
	TriggerCollisionComponent->SetSphereRadius(40);
	TriggerCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
	TriggerCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);

	MaxInteractDistance = 1000;
	bIsActive = false;
	bIsInteracted = false;
	// ...
}
// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	if (const auto PC = UGameplayStatics::GetPlayerController(GetOwner()->GetWorld(), 0))
	{
		PlayerCharacterPtr = MakeWeakObjectPtr(Cast<ARagshlyCharacter>(PC->GetPawn()));

		if (PlayerCharacterPtr.IsValid())
		{
			InputComponentPtr = MakeWeakObjectPtr(PlayerCharacterPtr->GetEnhancedInputComponent());
		}
	}
	// ...
	
}
// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UInteractableComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	/** Only this interactable binds to action when is in trigger */
	if (InputComponentPtr.IsValid() && OtherActor == PlayerCharacterPtr)
	{
		InputActionBindHandle = InputComponentPtr->BindAction(PlayerCharacterPtr -> InteractAction, ETriggerEvent::Completed, this,
			&ThisClass::OnInteractionSelected).GetHandle();
	}
}

void UInteractableComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	bIsInteracted = false; /** Reset interacted state, in case player already selected and re-enters zone */
	StopCheck();
}

void UInteractableComponent::OnInteractionSelected()
{
	bIsInteracted = true;

	StopCheck();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Interaction Selected"));

	OnInteracted.Broadcast(this);
}

void UInteractableComponent::StopCheck()
{
	/** Unbind from input action */
	if (InputComponentPtr.IsValid())
	{
		InputComponentPtr->RemoveBindingByHandle(InputActionBindHandle);
	}

}