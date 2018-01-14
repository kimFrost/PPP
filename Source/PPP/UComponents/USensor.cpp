// Fill out your copyright notice in the Description page of Project Settings.

#include "USensor.h"
#include "ACharacters/APerson.h"



USensor::USensor()
{
	//bShouldSensorBlock = true;
	//bShouldSensorPlayer = false;

	//Blueprint'/Game/MerchantTD/Blueprint/Characters/BP_Merchant.BP_Merchant'
	//static ConstructorHelpers::FObjectFinder<UTexture2D> HealthBarTextureObj(TEXT("Texture2D'/Game/UI/HealthBar.HealthBar'"));
	//HealthBarTexture = HealthBarTextureObj.Object;

	InitBoxExtent(FVector(100.f, 100.f, 20.f));
	//SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap); // Overlap BlockObjectChannel 
	//SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap); // Overlap BlockTraceChannel
	//SetCollisionProfileName();
	SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	//SetHiddenInGame(false);
}



void USensor::SensorTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APerson* Person = Cast<APerson>(OtherActor);
	if (Person)
	{
		OnPersonSensored.Broadcast(Person);
	}
}

// Called when the game starts or when spawned
void USensor::BeginPlay()
{
	Super::BeginPlay();

	//FComponentBeginOverlapSignature, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult &, SweepResult
	//Order->OnOrderResolved.AddUniqueDynamic(this, &AOrderVisualizer::OnOrderResolved);
	OnComponentBeginOverlap.AddDynamic(this, &USensor::SensorTriggered);
}