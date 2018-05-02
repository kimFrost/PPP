// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "USkill.generated.h"


//~~~~~ Forward Declarations ~~~~~//


UCLASS(Blueprintable, BlueprintType)
class PPP_API USkill : public UObject
{
	GENERATED_BODY()
	
public:
	USkill();
	~USkill();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", Meta = (ExposeOnSpawn = true))
	FString ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill", Meta = (ExposeOnSpawn = true))
	FString Title;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
	int32 XP;

	int32 NextLevelXP;

	int32 MaxXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skill")
	float Percentage;


public: 

	int32 SetXP(int32 _Value);

	int32 AddXP(int32 Amount);

	int32 SubtractXP(int32 Amount);

private:

	int32 ClampValue();

	int32 UpdateLevel();

};

