// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "LintRules/LintRule_Blueprint_Base.h"

#include "LintRule_Texture_Size_NotTooBig.generated.h"


UCLASS(BlueprintType, Blueprintable, Abstract)
class LINTER_API ULintRule_Texture_Size_NotTooBig : public ULintRule
{
    GENERATED_BODY()

public:
    explicit ULintRule_Texture_Size_NotTooBig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    int32 MaxTextureSizeX = 8192;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    int32 MaxTextureSizeY = 8192;

    virtual bool PassesRule(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;

protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
