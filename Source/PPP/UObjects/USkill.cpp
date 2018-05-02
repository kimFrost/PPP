// Fill out your copyright notice in the Description page of Project Settings.

#include "USkill.h"


USkill::USkill()
{
	Level = 0;
	XP = 0;
	NextLevelXP = 10;
	MaxXP = 1000;
}

USkill::~USkill()
{}


int32 USkill::SetXP(int32 _Value)
{
	XP = _Value;
	return ClampValue();
}

int32 USkill::AddXP(int32 Amount)
{
	XP += Amount;
	return ClampValue();
}

int32 USkill::SubtractXP(int32 Amount)
{
	XP -= Amount;
	return ClampValue();
}

int32 USkill::ClampValue()
{
	XP = FMath::Clamp(XP, 0, MaxXP);
	UpdateLevel();
	return XP;
}

int32 USkill::UpdateLevel()
{
	float Constant = 0.5;
	Level = FMath::FloorToInt(Constant * sqrt(XP));
	return Level;
}



/*
lv.1 0-5
lv.2 5-15
lv.3 15-30
lv.3 30-50
lv.4 50-75
lv.5 75-105
*/


/*
level = constant * sqrt(XP)
Level   XP      Difference
1       0       -
2       100     100
3       300     200
4       600     300
5       1000    400
*/

//x^3/sqrt(x^2+100)


//Traits
/*
Fast learner +50% xp


*/

//exp = level^const_value
//XP = (level / constant)^2
//XP = pow(level / constant, 2)