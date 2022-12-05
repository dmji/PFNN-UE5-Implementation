// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeuralNetworkObject.h"

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API PFNN_NeuralNetwork: public NeuralNetworkObject
{
public:
    PFNN_NeuralNetwork();
    ~PFNN_NeuralNetwork();

    static float Repeat(float t, float length);
    void Predict() override;
    void SetDamping(float value);
    float GetPhase();

protected:
    void StoreParametersDerived() override;
    void LoadParametersDerived() override;

public:
    int32 XDim = 0;
    int32 HDim = 0;
    int32 YDim = 0;

    int32 PhaseIndex = 0;

private:
    UTensorObject* Xmean; 
    UTensorObject* Xstd;
    UTensorObject* Ymean;
    UTensorObject* Ystd;

private:
    TArray<UTensorObject*> W0, W1, W2, b0, b1, b2;

    float Phase;
    float Damping;
};
