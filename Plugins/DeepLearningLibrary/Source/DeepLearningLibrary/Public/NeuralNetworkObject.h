// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TensorObject.h"
#include "ParametersObject.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPFNNBaseNeuralNetwork, Log, All);


/**
 * 
 */
class DEEPLEARNINGLIBRARY_API    NeuralNetworkObject
{
public:
	NeuralNetworkObject();
	virtual ~NeuralNetworkObject();

    virtual void Predict() = 0;

    void StoreParameters();
    void LoadParameters();
    UTensorObject* CreateTensor(int rows, int cols, FString id);
    UTensorObject* CreateTensor(UMatrixObject matrix);
    

    void DeleteTensor(UTensorObject* T)
    {
        int index = Tensors.IndexOfByKey(T);
        if(index == -1)
        {
            UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("UTensorObject not found."));
            return;
        }

        Tensors[index];
        delete Tensors[index];
        Tensors.RemoveAt(index);
    }

    UTensorObject* GetTensor(FString id)
    {
        return *Tensors.FindByPredicate([&id](const UTensorObject* x){ return x->ID == id; });
    }

    FString GetID(const UTensorObject* T)
    {
        int index = Tensors.IndexOfByKey(T);
        if(index == -1)
        {
            return "";
        }
        return Tensors[index]->ID;
    }

    void ResetPivot()
    {
        Pivot = -1;
    }

    void SetInput(int index, float value)
    {
        Pivot = index;
        X->SetValue(index, 0, value);
    }

    float GetInput(int index)
    {
        Pivot = index;
        return X->GetValue(index, 0);
    }

    void SetOutput(int index, float value)
    {
        Pivot = index;
        Y->SetValue(index, 0, value);
    }



    void Feed(float value)
    {
        SetInput(Pivot + 1, value);
    }

    void Feed(TArray<float>& values)
    {
        for(int i = 0; i < values.Num(); i++)
        {
            Feed(values[i]);
        }
    }

    void Feed(FVector2d vector)
    {
        Feed(vector.X);
        Feed(vector.Y);
    }

    void Feed(FVector3d vector)
    {
        Feed(vector.X);
        Feed(vector.Y);
        Feed(vector.Z);
    }

    float GetOutput(int index)
    {
        Pivot = index;
        return Y->GetValue(index, 0);
    }

    float Read()
    {
        return GetOutput(Pivot + 1);
    }

    TArray<float> Read(int count)
    {
        TArray<float> values;
        values.SetNum(count);
        for(int i = 0; i < count; i++)
            values[i] = Read();
        return values;
    }

    UTensorObject* Normalise(UTensorObject* in, UTensorObject* mean, UTensorObject* std, UTensorObject* out);
    UTensorObject* Renormalise(UTensorObject* in, UTensorObject* mean, UTensorObject* std, UTensorObject* out);
    UTensorObject* Layer(UTensorObject* in, UTensorObject* W, UTensorObject* b, UTensorObject* out);
    UTensorObject* Blend(UTensorObject* T, UTensorObject* W, float w);

    UTensorObject* ELU(UTensorObject* T)
    {
        EigenUtils::ELU(T->Ptr);
        return T;
    }

    UTensorObject* Sigmoid(UTensorObject* T)
    {
        EigenUtils::Sigmoid(T->Ptr);
        return T;
    }

    UTensorObject* TanH(UTensorObject* T)
    {
        EigenUtils::TanH(T->Ptr);
        return T;
    }

    UTensorObject* SoftMax(UTensorObject* T)
    {
        EigenUtils::SoftMax(T->Ptr);
        return T;
    }

    UTensorObject* LogSoftMax(UTensorObject* T)
    {
        EigenUtils::LogSoftMax(T->Ptr);
        return T;
    }

    UTensorObject* SoftSign(UTensorObject* T)
    {
        EigenUtils::SoftSign(T->Ptr);
        return T;
    }

    UTensorObject* Exp(UTensorObject* T)
    {
        EigenUtils::Exp(T->Ptr);
        return T;
    }

protected:
    virtual void StoreParametersDerived() = 0;
    virtual void LoadParametersDerived() = 0;

public:
    FString Folder;
    FString Destination;
    TUniquePtr<UParametersObject> Parameters;

    UTensorObject* X;
    UTensorObject* Y;

private:
    int32 Pivot = -1;
    TArray<UTensorObject*> Tensors;
};
