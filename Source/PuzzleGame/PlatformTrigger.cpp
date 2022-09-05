// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::TriggerOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::TriggerOverlapEnd);
	
}

void APlatformTrigger::TriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin!!"));
	if (MovingPlatform.Num() != 0) {
		// 설정한 MovingPlatform array가 비어있지 않다면
		for (int i = 0; i < MovingPlatform.Num(); i++) {
			AMovingPlatform* ConnectMovingPlatform = Cast<AMovingPlatform>(MovingPlatform[i]);
			if (ConnectMovingPlatform) {
				ConnectMovingPlatform->Activate();
			}
		}
	}

}

void APlatformTrigger::TriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End!!"));
	if (MovingPlatform.Num() != 0) {
		// 설정한 MovingPlatform array가 비어있지 않다면
		for (int i = 0; i < MovingPlatform.Num(); i++) {
			AMovingPlatform* ConnectMovingPlatform = Cast<AMovingPlatform>(MovingPlatform[i]);
			if (ConnectMovingPlatform) {
				ConnectMovingPlatform->DeActivate();
			}
		}
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

