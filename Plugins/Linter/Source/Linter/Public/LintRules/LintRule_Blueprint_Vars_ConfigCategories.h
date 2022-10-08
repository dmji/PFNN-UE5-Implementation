// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "LintRules/LintRule_Blueprint_Base.h"

#include "LintRule_Blueprint_Vars_ConfigCategories.generated.h"


UCLASS(BlueprintType, Blueprintable, Abstract)
class LINTER_API ULintRule_Blueprint_Vars_ConfigCategories : public ULintRule_Blueprint_Base
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    int32 NumVariablesToRequireCategorization = 5;

public:
    explicit ULintRule_Blueprint_Vars_ConfigCategories(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
