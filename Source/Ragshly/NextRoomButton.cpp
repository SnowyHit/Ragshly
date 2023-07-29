// Fill out your copyright notice in the Description page of Project Settings.


#include "NextRoomButton.h"
#include "DungeonGenerator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANextRoomButton::ANextRoomButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRootComponent);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(FName(GetActorNameOrLabel()));
	/**NOTE: Nested component's children must be added within Actor. attaching in the owner component does not work??? */
	InteractableComponent->TriggerCollisionComponent->SetRelativeScale3D(FVector(3, 3, 3));
	InteractableComponent->TriggerCollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANextRoomButton::BeginPlay()
{
	Super::BeginPlay();
	InteractableComponent->OnInteracted.AddDynamic(this, &ThisClass::OnSelected);
}

// Called every frame
void ANextRoomButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANextRoomButton::OnSelected(UInteractableComponent* InInteractable)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Interacted" + GetActorNameOrLabel()));

	AActor* DungeonGenActorRef = UGameplayStatics::GetActorOfClass(GetWorld(), ADungeonGenerator::StaticClass());
	ADungeonGenerator* DungeonGenReference = Cast<ADungeonGenerator>(DungeonGenActorRef);

	if (DungeonGenReference)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z = 0;
		FRotator SpawnRotation = GetActorRotation();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, GetActorForwardVector().ToString());
		DungeonGenReference->SpawnRoom(GetActorForwardVector());
	}
}

