// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MoreItemsCharacter.h"
#include "Fire.generated.h"

UCLASS()
class MOREITEMS_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UShapeComponent* TB_Fire;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* SM_Fire;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* PS_Fire;
	
	AMoreItemsCharacter* CurrentPlayerController;

	UPROPERTY(EditAnywhere)
		FString HelpText = FString(TEXT("Press F to activate the fire"));

	int32 ResetTime;

	bool bPlayerIsWithinRange = false;
	bool bFireIsLit = false;

	void GetPlayer(AActor* Player);
	void Light();
	void AdvancedTimer();
	void TimerHasFinnished();

	FTimerHandle CountdownTimerHandle;

	UFUNCTION()
		void TriggerEnter(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
