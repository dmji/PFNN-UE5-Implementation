// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EigenUtils.h"
//#include "TensorObject.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPFNNTensor, Log, All);

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API UTensorObject
{
public:
	bool operator==(const UTensorObject& a)
	{
		return a.Ptr == Ptr && a.ID == ID;
	}

	//UTensorObject(const FObjectInitializer&) : UTensorObject(0, 0)	{}
	UTensorObject(const UTensorObject& obj)
	{
		Ptr = EigenUtils::Create(obj.GetRows(), obj.GetCols());
		ID = obj.ID;
		Deleted = obj.Deleted;
	}
	UTensorObject(int rows, int cols, FString id = "") : ID(id), Deleted(false)
	{
		Ptr = EigenUtils::Create(rows, cols);
	}
	~UTensorObject()
	{
		Delete();
	}

	static UTensorObject Add(UTensorObject lhs, UTensorObject rhs, UTensorObject out);
	static UTensorObject Subtract(UTensorObject lhs, UTensorObject rhs, UTensorObject out);
	static UTensorObject Product(UTensorObject lhs, UTensorObject rhs, UTensorObject out);
	static UTensorObject Scale(UTensorObject lhs, float value, UTensorObject out);
	static UTensorObject PointwiseProduct(UTensorObject lhs, UTensorObject rhs, UTensorObject out);
	static UTensorObject PointwiseQuotient(UTensorObject lhs, UTensorObject rhs, UTensorObject out);
	static UTensorObject PointwiseAbsolute(UTensorObject in, UTensorObject out);

	void Delete();
	int GetRows() const;
	int GetCols() const ;
	void SetZero();
	void SetSize(int rows, int cols);
	void SetValue(int row, int col, float value);
	float GetValue(int row, int col) const;

	float RowMean(int row) const;
	float ColMean(int col) const;
	float RowStd(int row) const;
	float ColStd(int col) const;
	float RowSum(int row) const;
	float ColSum(int col) const;
	void Print() const;

public:
	EigenUtils::TensorPtr Ptr;
	FString ID;

private:
	bool Deleted;
};
