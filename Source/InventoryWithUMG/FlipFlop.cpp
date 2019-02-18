// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipFlop.h"

FFlipFlop::FFlipFlop()
{
	Reset();
}

FFlipFlop::~FFlipFlop()
{
}

bool FFlipFlop::GetIsA() const
{
	return IsA;
}

bool FFlipFlop::Switch()
{
	return IsA = !IsA;
}

void FFlipFlop::Reset()
{
	IsA = false;
}
