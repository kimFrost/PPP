// Fill out your copyright notice in the Description page of Project Settings.

#include "UStat.h"


UStat::UStat()
{
	MaxValue = 1;
	ConsumeMultiplier = 1;
	Value = MaxValue;
}

UStat::~UStat()
{}


float UStat::Add(float Amount)
{
	Value += Amount;
	return ClampValue();
}

float UStat::Subtract(float Amount)
{
	Value -= Amount;
	return ClampValue();
}

float UStat::ClampValue()
{
	if (Value < 0)
	{
		Value = 0;
	}
	else if (Value > MaxValue)
	{
		Value = MaxValue;
	}
	UpdatePercentage();
	return Value;
}

float UStat::UpdatePercentage()
{
	return Percentage = FPlatformMath::CeilToFloat(Value / MaxValue); //* 100
}
