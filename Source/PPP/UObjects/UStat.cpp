// Fill out your copyright notice in the Description page of Project Settings.

#include "UStat.h"


UStat::UStat()
{
	MinValue = -10;
	MaxValue = 10;
	ConsumeMultiplier = 1;
	Value = 0;
}

UStat::~UStat()
{}


int32 UStat::Set(int32 _Value)
{
	Value = _Value;
	return ClampValue();
}

int32 UStat::Add(int32 Amount)
{
	Value += Amount;
	return ClampValue();
}

int32 UStat::Subtract(int32 Amount)
{
	Value -= Amount;
	return ClampValue();
}

int32 UStat::ClampValue()
{
	Value = FMath::Clamp(Value, MinValue, MaxValue);
	/*
	if (Value < 0)
	{
		Value = 0;
	}
	else if (Value > MaxValue)
	{
		Value = MaxValue;
	}
	*/
	UpdatePercentage();
	return Value;
}

float UStat::UpdatePercentage()
{
	return Percentage = FPlatformMath::CeilToFloat(Value / MaxValue); //* 100
}
