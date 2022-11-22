// Fill out your copyright notice in the Description page of Project Settings.

#include "EigenUtils.h"

EigenUtils::TensorPtr EigenUtils::Create(int rows, int cols)
{
	return new Tensor(Tensor::Zero(rows, cols));
}

void EigenUtils::Delete(TensorPtr ptr)
{
	delete(ptr);
}

int EigenUtils::GetRows(TensorPtr ptr)
{
	return (*ptr).rows();
}

int EigenUtils::GetCols(TensorPtr ptr)
{
	return (*ptr).cols();
}

void EigenUtils::SetZero(TensorPtr ptr)
{
	(*ptr).noalias() = (*ptr).Zero((*ptr).rows(), (*ptr).cols());
}

void EigenUtils::SetSize(TensorPtr ptr, int rows, int cols)
{
	(*ptr).conservativeResize(rows, cols);
}

void EigenUtils::Add(TensorPtr lhs, TensorPtr rhs, TensorPtr out)
{
	(*out).noalias() = *lhs + *rhs;
}

void EigenUtils::Subtract(TensorPtr lhs, TensorPtr rhs, TensorPtr out)
{
	(*out).noalias() = *lhs - *rhs;
}

void EigenUtils::Product(TensorPtr lhs, TensorPtr rhs, TensorPtr out)
{
	(*out).noalias() = *lhs * *rhs;
}

void EigenUtils::Scale(TensorPtr lhs, float value, TensorPtr out)
{
	(*out).noalias() = *lhs * value;
}

void EigenUtils::SetValue(TensorPtr ptr, int row, int col, float value)
{
	(*ptr)(row, col) = value;
}

float EigenUtils::GetValue(TensorPtr ptr, int row, int col)
{
	return (*ptr)(row, col);
}

void EigenUtils::PointwiseProduct(TensorPtr lhs, TensorPtr rhs, TensorPtr out)
{
	(*out).noalias() = (*lhs).cwiseProduct(*rhs);
}

void EigenUtils::PointwiseQuotient(TensorPtr lhs, TensorPtr rhs, TensorPtr out)
{
	(*out).noalias() = (*lhs).cwiseQuotient(*rhs);
}

void EigenUtils::PointwiseAbsolute(TensorPtr in, TensorPtr out)
{
	(*out).noalias() = (*in).cwiseAbs();
}

float EigenUtils::RowSum(TensorPtr ptr, int row)
{
	return (*ptr).row(row).sum();
}

float EigenUtils::ColSum(TensorPtr ptr, int col)
{
	return (*ptr).col(col).sum();
}

float EigenUtils::RowMean(TensorPtr ptr, int row)
{
	return (*ptr).row(row).mean();
}

float EigenUtils::ColMean(TensorPtr ptr, int col)
{
	return (*ptr).col(col).mean();
}

float EigenUtils::RowStd(TensorPtr ptr, int row)
{
	Tensor diff = (*ptr).row(row) - (*ptr).row(row).mean() * Tensor::Ones(1, (*ptr).rows());
	diff = diff.cwiseProduct(diff);
	return std::sqrt(diff.sum() / (*ptr).cols());
}

float EigenUtils::ColStd(TensorPtr ptr, int col)
{
	Tensor diff = (*ptr).col(col) - (*ptr).col(col).mean() * Tensor::Ones((*ptr).rows(), 1);
	diff = diff.cwiseProduct(diff);
	return std::sqrt(diff.sum() / (*ptr).rows());
}

void EigenUtils::Normalise(TensorPtr ptr, TensorPtr mean, TensorPtr std, TensorPtr out)
{
	(*out).noalias() = (*ptr - *mean).cwiseQuotient(*std);
}

void EigenUtils::Renormalise(TensorPtr ptr, TensorPtr mean, TensorPtr std, TensorPtr out)
{
	(*out).noalias() = (*ptr).cwiseProduct(*std) + *mean;
}

//void ILayer (TensorPtr X, TensorPtr W, TensorPtr b) {
//	(*X).noalias() = *W * *X + *b;
//}

void EigenUtils::Layer(TensorPtr in, TensorPtr W, TensorPtr b, TensorPtr out)
{
	(*out).noalias() = *W * *in + *b;
}

void EigenUtils::Blend(TensorPtr in, TensorPtr W, float w)
{
	(*in).noalias() += w * *W;
}

void EigenUtils::BlendAll(TensorPtr in, TensorPtr* W, float* w, int length)
{
	if(length == 0)
	{
		SetZero(in);
	}
	else
	{
		switch(length)
		{
		case 1:
			(*in).noalias() = w[0] * *W[0];
			break;
		case 2:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1];
			break;
		case 3:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2];
			break;
		case 4:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3];
			break;
		case 5:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4];
			break;
		case 6:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5];
			break;
		case 7:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6];
			break;
		case 8:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6] + w[7] * *W[7];
			break;
		case 9:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6] + w[7] * *W[7] + w[8] * *W[8];
			break;
		case 10:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6] + w[7] * *W[7] + w[8] * *W[8] + w[9] * *W[9];
			break;
		case 11:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6] + w[7] * *W[7] + w[8] * *W[8] + w[9] * *W[9] + w[10] * *W[10];
			break;
		case 12:
			(*in).noalias() = w[0] * *W[0] + w[1] * *W[1] + w[2] * *W[2] + w[3] * *W[3] + w[4] * *W[4] + w[5] * *W[5] + w[6] * *W[6] + w[7] * *W[7] + w[8] * *W[8] + w[9] * *W[9] + w[10] * *W[10] + w[11] * *W[11];
			break;
		default:
			(*in).noalias() = w[0] * *W[0];
			for(int i = 1; i < length; i++)
			{
				(*in).noalias() += w[i] * *W[i];
			}
			break;
		}
	}
}

void EigenUtils::RELU(TensorPtr ptr)
{
	(*ptr).noalias() = (*ptr).cwiseMax(0.0f);
}

void EigenUtils::ELU(TensorPtr ptr)
{
	(*ptr).noalias() = ((*ptr).array().cwiseMax(0.0f) + (*ptr).array().cwiseMin(0.0f).exp() - 1.0f).matrix();
	//int rows = (*ptr).rows();
	//for (int i = 0; i<rows; i++) {
	//	(*ptr)(i, 0) = (std::max)((*ptr)(i, 0), 0.0f) + std::exp((std::min)((*ptr)(i, 0), 0.0f)) - 1.0f;
	//}
}

void EigenUtils::Sigmoid(TensorPtr ptr)
{
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = 1.0f / (1.0f + std::exp(-(*ptr)(i, 0)));
	}
}

void EigenUtils::TanH(TensorPtr ptr)
{
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = std::tanh((*ptr)(i, 0));
	}
}

void EigenUtils::SoftMax(TensorPtr ptr)
{
	float frac = 0.0f;
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = std::exp((*ptr)(i, 0));
		frac += (*ptr)(i, 0);
	}
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) /= frac;
	}
}

void EigenUtils::LogSoftMax(TensorPtr ptr)
{
	float frac = 0.0f;
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = std::exp((*ptr)(i, 0));
		frac += (*ptr)(i, 0);
	}
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = std::log((*ptr)(i, 0) / frac);
	}
}

void EigenUtils::SoftSign(TensorPtr ptr)
{
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) /= 1 + std::abs((*ptr)(i, 0));
	}
}

void EigenUtils::Exp(TensorPtr ptr)
{
	int rows = (*ptr).rows();
	for(int i = 0; i < rows; i++)
	{
		(*ptr)(i, 0) = std::exp((*ptr)(i, 0));
	}
}