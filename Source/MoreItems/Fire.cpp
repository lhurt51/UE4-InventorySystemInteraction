// Fill out your copyright notice in the Description page of Project Settings.

#include "MoreItems.h"
#include "MoreItemsCharacter.h"
#include "Engine.h"
#include "Fire.h"


// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TB_Fire = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	TB_Fire->bGenerateOverlapEvents = true;
	TB_Fire->OnComponentBeginOverlap.AddDynamic(this, &AFire::TriggerEnter);
	TB_Fire->OnComponentEndOverlap.AddDynamic(this, &AFire::TriggerExit);
	TB_Fire->SetRelativeScale3D(FVector(3.0f, 3.0f, 1.0f));

	RootComponent = TB_Fire;

	SM_Fire = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fire Mesh"));
	SM_Fire->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PS_Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));
	PS_Fire->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	PS_Fire->SetVisibility(false);

	ResetTime = 10;
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AFire::AdvancedTimer, 1.0f, true);
	PS_Fire->SetVisibility(false);
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPlayerController != NULL)
	{
		if (CurrentPlayerController->bIsInteracting && bPlayerIsWithinRange && CurrentPlayerController->Inventory.Contains("Matches") && !bFireIsLit)
		{
			Light();
		}
	}
}

void AFire::GetPlayer(AActor * Player)
{
	CurrentPlayerController = Cast<AMoreItemsCharacter>(Player);
}

void AFire::Light()
{
	int32 XpGained = FMath::RandRange(10, 100);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("The fire has been lit. You gain %dXp."), XpGained));
	CurrentPlayerController->Inventory.RemoveSingle("Matches");
	bFireIsLit = true;
	PS_Fire->SetVisibility(true);
}

void AFire::AdvancedTimer()
{
	if (bFireIsLit)
	{
		--ResetTime;

		if (ResetTime < 1)
		{
			TimerHasFinnished();
		}
	}
}

void AFire::TimerHasFinnished()
{
	PS_Fire->SetVisibility(false);
	bFireIsLit = false;
	ResetTime = 10;
}

void AFire::TriggerEnter(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GetPlayer(OtherActor);
	bPlayerIsWithinRange = true;

	if (CurrentPlayerController->Inventory.Contains("Matches"))
	{
		if (!bFireIsLit)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, HelpText);
	}
	else
	{
		if (!bFireIsLit)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You need matches to light the fire."));
	}
}

void AFire::TriggerExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bPlayerIsWithinRange = false;
}

