// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "LintRules/LintRule_Blueprint_Base.h"

#include "LintRule_Collection.generated.h"


UCLASS(BlueprintType, Blueprintable, Abstract)
class LINTER_API ULintRule_Collection : public ULintRule
{
    GENERATED_BODY()

public:
    explicit ULintRule_Collection(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TArray<TSubclassOf<ULintRule>> SubRules;

protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
