// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../ThirdParty/Eigen/Dense"
class EIGENKERNAL_API EigenUtils
{
public:
	typedef Eigen::MatrixXf Tensor;
	typedef Tensor* TensorPtr;

	static TensorPtr Create(int rows, int cols);
	static void Delete(TensorPtr ptr);
	static int GetRows(TensorPtr ptr);
	static int GetCols(TensorPtr ptr);
	static void SetZero(TensorPtr ptr);
	static void SetSize(TensorPtr ptr, int rows, int cols);
	static void Add(TensorPtr lhs, TensorPtr rhs, TensorPtr out);
	static void Subtract(TensorPtr lhs, TensorPtr rhs, TensorPtr out);
	static void Product(TensorPtr lhs, TensorPtr rhs, TensorPtr out);
	static void Scale(TensorPtr lhs, float value, TensorPtr out);
	static void SetValue(TensorPtr ptr, int row, int col, float value);
	static float GetValue(TensorPtr ptr, int row, int col);
	static void PointwiseProduct(TensorPtr lhs, TensorPtr rhs, TensorPtr out);
	static void PointwiseQuotient(TensorPtr lhs, TensorPtr rhs, TensorPtr out);
	static void PointwiseAbsolute(TensorPtr in, TensorPtr out);
	static float RowSum(TensorPtr ptr, int row);
	static float ColSum(TensorPtr ptr, int col);
	static float RowMean(TensorPtr ptr, int row);
	static float ColMean(TensorPtr ptr, int col);
	static float RowStd(TensorPtr ptr, int row);
	static float ColStd(TensorPtr ptr, int col);
	static void Normalise(TensorPtr ptr, TensorPtr mean, TensorPtr std, TensorPtr out);
	static void Renormalise(TensorPtr ptr, TensorPtr mean, TensorPtr std, TensorPtr out);
	static void Layer(TensorPtr in, TensorPtr W, TensorPtr b, TensorPtr out);
	static void Blend(TensorPtr in, TensorPtr W, float w);
	static void BlendAll(TensorPtr in, TensorPtr* W, float* w, int length);
	static void RELU(TensorPtr ptr);
	static void ELU(TensorPtr ptr);
	static void Sigmoid(TensorPtr ptr);
	static void TanH(TensorPtr ptr);
	static void SoftMax(TensorPtr ptr);
	static void LogSoftMax(TensorPtr ptr);
	static void SoftSign(TensorPtr ptr);
	static void Exp(TensorPtr ptr);
};