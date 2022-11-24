// Fill out your copyright notice in the Description page of Project Settings.


#include "TensorObject.h"


DEFINE_LOG_CATEGORY(LogPFNNTensor);


void UTensorObject::Delete()
{
    if(!Deleted)
    {
        EigenUtils::Delete(Ptr);
        Deleted = true;
    }
}

int UTensorObject::GetRows() const
{
    return EigenUtils::GetRows(Ptr);
}

int UTensorObject::GetCols() const
{
    return EigenUtils::GetCols(Ptr);
}

void UTensorObject::SetZero()
{
    EigenUtils::SetZero(Ptr);
}

void UTensorObject::SetSize(int rows, int cols)
{
    EigenUtils::SetSize(Ptr, rows, cols);
}

void UTensorObject::SetValue(int row, int col, float value)
{
    if(row >= GetRows() || col >= GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Setting out of bounds at [%d, %d]."), row, col);
        return;
    }
    EigenUtils::SetValue(Ptr, row, col, value);
}

float UTensorObject::GetValue(int row, int col) const
{
    if(row >= GetRows() || col >= GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Getting out of bounds at [%d, %d]."), row, col);
        return 0.f;
    }
    return EigenUtils::GetValue(Ptr, row, col);
}

static UTensorObject Add(UTensorObject lhs, UTensorObject rhs, UTensorObject pOut)
{
    if(lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Incompatible tensor dimensions."));
    }
    else
    {
        EigenUtils::Add(lhs.Ptr, rhs.Ptr, pOut.Ptr);
    }
    return pOut;
}

static UTensorObject Subtract(UTensorObject lhs, UTensorObject rhs, UTensorObject pOut)
{
    if(lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Incompatible tensor dimensions."));
    }
    else
    {
        EigenUtils::Subtract(lhs.Ptr, rhs.Ptr, pOut.Ptr);
    }
    return pOut;
}

static UTensorObject Product(UTensorObject lhs, UTensorObject rhs, UTensorObject pOut)
{
    if(lhs.GetCols() != rhs.GetRows())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Incompatible tensor dimensions."));
    }
    else
    {
        EigenUtils::Product(lhs.Ptr, rhs.Ptr, pOut.Ptr);
    }
    return pOut;
}

static UTensorObject Scale(UTensorObject lhs, float value, UTensorObject pOut)
{
    EigenUtils::Scale(lhs.Ptr, value, pOut.Ptr);
    return pOut;
}

static UTensorObject PointwiseProduct(UTensorObject lhs, UTensorObject rhs, UTensorObject pOut)
{
    if(lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Incompatible tensor dimensions."));
    }
    else
    {
        EigenUtils::PointwiseProduct(lhs.Ptr, rhs.Ptr, pOut.Ptr);
    }
    return pOut;
}

static UTensorObject PointwiseQuotient(UTensorObject lhs, UTensorObject rhs, UTensorObject pOut)
{
    if(lhs.GetRows() != rhs.GetRows() || lhs.GetCols() != rhs.GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Incompatible tensor dimensions."));
    }
    else
    {
        EigenUtils::PointwiseQuotient(lhs.Ptr, rhs.Ptr, pOut.Ptr);
    }
    return pOut;
}

static UTensorObject PointwiseAbsolute(UTensorObject pIn, UTensorObject pOut)
{
    EigenUtils::PointwiseAbsolute(pIn.Ptr, pOut.Ptr);
    return pOut;
}

float UTensorObject::RowMean(int row) const
{
    if(row >= GetRows())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::RowMean(Ptr, row);
}

float UTensorObject::ColMean(int col) const
{
    if(col >= GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::ColMean(Ptr, col);
}

float UTensorObject::RowStd(int row) const
{
    if(row >= GetRows())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::RowStd(Ptr, row);
}

float UTensorObject::ColStd(int col) const
{
    if(col >= GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::ColStd(Ptr, col);
}

float UTensorObject::RowSum(int row) const
{
    if(row >= GetRows())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::RowSum(Ptr, row);
}

float UTensorObject::ColSum(int col) const
{
    if(col >= GetCols())
    {
        UE_LOG(LogPFNNTensor, Log, TEXT("Accessing out of bounds."));
        return 0.f;
    }
    return EigenUtils::ColSum(Ptr, col);
}

void UTensorObject::Print() const
{
    FString output;
    output.Empty();
    for(int i = 0; i < GetRows(); i++)
    {
        for(int j = 0; j < GetCols(); j++)
        {
            output += FString::SanitizeFloat(GetValue(i, j)) + TEXT(" ");
        }
        output += TEXT("\n");
    }
    UE_LOG(LogPFNNTensor, Log, TEXT("%s"), *output);
}