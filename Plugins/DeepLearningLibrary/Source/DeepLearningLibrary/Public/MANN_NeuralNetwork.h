// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkObject.h"

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API MANN_NeuralNetwork: public NeuralNetworkObject
{
public:
	MANN_NeuralNetwork();
	~MANN_NeuralNetwork();

	void Predict() override;

protected:
	void StoreParametersDerived() override;
	void LoadParametersDerived() override;
	void OnValidate() 
	{
		ControlNeurons.SetNum(XDimBlend);
	}
public:
	int32 XDim = 0;
	int32 HDim = 0;
	int32 YDim = 0;

	int32 XDimBlend = 0;
	int32 HDimBlend = 0;
	int32 YDimBlend = 0;

	TArray<int32> ControlNeurons;

private:
	UTensorObject* Xmean;
	UTensorObject* Xstd;
	UTensorObject* Ymean;
	UTensorObject* Ystd;

	UTensorObject* BX;
	UTensorObject* BY;

	UTensorObject* BW0;
	UTensorObject* BW1;
	UTensorObject* BW2;
	UTensorObject* Bb0;
	UTensorObject* Bb1;
	UTensorObject* Bb2;

	TArray<UTensorObject*> CW;

	UTensorObject* W0;
	UTensorObject* W1;
	UTensorObject* W2;
	UTensorObject* b0;
	UTensorObject* b1;
	UTensorObject* b2;
};





	
