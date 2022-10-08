// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "AnyObject_LinterDummyClass.generated.h"


UCLASS(BlueprintType, Blueprintable)
class UAnyObject_LinterDummyClass : public UObject
{
	GENERATED_BODY()

public:

	explicit UAnyObject_LinterDummyClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
