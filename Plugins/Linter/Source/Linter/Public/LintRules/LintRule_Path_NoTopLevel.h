// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "LintRules/LintRule_Blueprint_Base.h"

#include "LintRule_Path_NoTopLevel.generated.h"


UCLASS(BlueprintType, Blueprintable, Abstract)
class LINTER_API ULintRule_Path_NoTopLevel : public ULintRule
{
    GENERATED_BODY()

public:
    explicit ULintRule_Path_NoTopLevel(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UPROPERTY(EditDefaultsOnly, Category = "Display")
    FText ZeroTopLevelFoldersRecommendedAction;

    UPROPERTY(EditDefaultsOnly, Category = "Display")
    FText PleaseUseThisFolderRecommendedAction;

protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
