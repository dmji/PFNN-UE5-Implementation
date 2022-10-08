// Copyright 2019-2020 Gamemakin LLC. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "LintRules/LintRule_Blueprint_Base.h"

#include "Engine/Blueprint.h"

#include "LintRule_Blueprint_Vars_NonAtomic.generated.h"


UCLASS(BlueprintType, Blueprintable, Abstract)
class LINTER_API ULintRule_Blueprint_Vars_NonAtomic : public ULintRule_Blueprint_Base
{
    GENERATED_BODY()

public:
    explicit ULintRule_Blueprint_Vars_NonAtomic(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    static bool IsVariableAtomic(FBPVariableDescription& VarDesc);

protected:
    virtual bool PassesRule_Internal_Implementation(UObject* ObjectToLint, const ULintRuleSet* ParentRuleSet, TArray<FLintRuleViolation>& OutRuleViolations) const override;
};
