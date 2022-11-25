// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KERNALLIBRARY_API UBinaryFloatFileReader
{
    UBinaryFloatFileReader() = delete;

public:
    UBinaryFloatFileReader(const FString arg_FileName, ...);
    ~UBinaryFloatFileReader();

    FFloat32 readItem();
    bool isOpen();
    int32 nErrorsOnRead();

private:
    IFileHandle* m_FileHandle;
    int32 m_Errors;
};