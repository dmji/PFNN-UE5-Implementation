// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPFNNParameters, Log, All);

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API UMatrixObject
{
public:
    UMatrixObject(int rows, int cols, FString id);
    bool isNull()
    {
        return Rows <= 0 || Cols <= 0;
    }
public:
    TArray<TArray<float>> Values;
    int32 Rows, Cols;
    FString ID;
};

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API UParametersObject : UDataAsset
{
public:
    static void operator delete(void* self)
    {
        ((UParametersObject*)self)->Matrices.Empty();
        delete self;
    }

    bool Validate();
    void Store(FString fn, int rows, int cols, FString id);

    UMatrixObject Load(FString id);
    void Clear();

private:
    UMatrixObject ReadBinary(FString fn, int rows, int cols, FString id);

public:
    TArray<UMatrixObject> Matrices;
};
