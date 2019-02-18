// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class INVENTORYWITHUMG_API FFlipFlop
{
public:
	FFlipFlop();
	~FFlipFlop();

private:
	bool IsA;

public:
	bool GetIsA() const;

	bool Switch();

	void Reset();
};
