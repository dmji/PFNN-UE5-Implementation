// Fill out your copyright notice in the Description page of Project Settings.


#include "ParametersObject.h"
#include "FileHandlersUtil.h"

DEFINE_LOG_CATEGORY(LogPFNNParameters);

UMatrixObject::UMatrixObject(int rows, int cols, FString id)
    : Rows(rows), Cols(cols), ID(id)
{
    Values.AddZeroed(rows);
    for(int i = 0; i < rows; i++)
        Values[i].AddZeroed(cols);
}

bool UParametersObject::Validate()
{
    for(int i = 0; i < Matrices.Num(); i++)
    {
        if(!Matrices[i].isNull())
            return false;
    }
    return true;
}

void UParametersObject::Store(FString fn, int rows, int cols, FString id)
{
    for(int i = 0; i < Matrices.Num(); i++)
    {
        if(Matrices.IsValidIndex(i) && !Matrices[i].isNull())
        {
            if(Matrices[i].ID == id)
            {
                UE_LOG(LogPFNNParameters, Error, TEXT("Matrix with ID %d already contained."), *id);
                return;
            }
        }
    }
    Matrices.Add(ReadBinary(fn, rows, cols, id));
}

UMatrixObject UParametersObject::Load(FString id)
{
    UMatrixObject* matrix = Matrices.FindByPredicate([id](const auto& mx) { return mx.ID == id; });
    if(matrix == nullptr)
    {
        UE_LOG(LogPFNNParameters, Error, TEXT("Matrix with ID %s not found."), *id);
    }
    return *matrix;
}

void UParametersObject::Clear()
{
    Matrices.Empty();
}

UMatrixObject UParametersObject::ReadBinary(FString fn, int rows, int cols, FString id)
{
    UBinaryFloatFileReader file(fn);
    if(file.isOpen())
    {
        UMatrixObject matrix(rows, cols, id);
        for(int32 x = 0; x < rows; x++)
        {
            for(int32 y = 0; y < cols; y++)
                matrix.Values[x][y] = file.readItem().FloatValue;
        }

        if(file.nErrorsOnRead() > 0)
        {
            UE_LOG(LogPFNNParameters, Error, TEXT("There were %d errors reading file at path %s."), file.nErrorsOnRead(), *fn);
            return UMatrixObject(0, 0, "");
        }
        else
        {
            return matrix;
        }
    }
    else
    {
        UE_LOG(LogPFNNParameters, Error, TEXT("File at path %s does not exist."), *fn);
        return UMatrixObject(0, 0, "");
    }
}
