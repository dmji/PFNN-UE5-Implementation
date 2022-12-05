// Fill out your copyright notice in the Description page of Project Settings.


#include "NeuralNetworkObject.h"

DEFINE_LOG_CATEGORY(LogPFNNBaseNeuralNetwork);



NeuralNetworkObject::NeuralNetworkObject()
{
}

NeuralNetworkObject::~NeuralNetworkObject()
{
}

void NeuralNetworkObject::StoreParameters()
{
    StoreParametersDerived();
    if(!Parameters->Validate())
    {
        Parameters.Release();
    }
    else
    {
//         PlanTODO: Create Asset
//#if UNITY_EDITOR
//            AssetDatabase.CreateAsset(Parameters, Destination + "/Parameters.asset");
//#endif
    }
}

void NeuralNetworkObject::LoadParameters()
{
    if(!Parameters.IsValid())
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Building PFNN failed because no parameters were saved."));
    }
    else
    {
        LoadParametersDerived();
    }
}

UTensorObject* NeuralNetworkObject::CreateTensor(int rows, int cols, FString id)
{
    if(UTensorObject* t = *Tensors.FindByPredicate([&id](const UTensorObject* x){ return x->ID == id; }))
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Tensor with ID %s already contained."), *id);
        return t;
    }
    UTensorObject* T = new UTensorObject(rows, cols, id);
    Tensors.Add(T);
    return T;
}

UTensorObject* NeuralNetworkObject::CreateTensor(UMatrixObject matrix)
{
    if(UTensorObject* t = *Tensors.FindByPredicate([&matrix](const UTensorObject* x){ return x->ID == matrix.ID; }))
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Tensor with ID %s already contained."), *matrix.ID);
        return t;
    }
    UTensorObject* T = new UTensorObject(matrix.Rows, matrix.Cols, matrix.ID);
    for(int x = 0; x < matrix.Rows; x++)
    {
        for(int y = 0; y < matrix.Cols; y++)
        {
            T->SetValue(x, y, matrix.Values[x][y]);
        }
    }
    Tensors.Add(T);
    return T;
}

UTensorObject* NeuralNetworkObject::Normalise(UTensorObject* in, UTensorObject* mean, UTensorObject* std, UTensorObject* out)
{
    if(in->GetRows() != mean->GetRows() 
       || in->GetRows() != std->GetRows() 
       || in->GetCols() != mean->GetCols() 
       || in->GetCols() != std->GetCols())
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Incompatible dimensions for normalisation."));
        return in;
    }
    else
    {
        EigenUtils::Normalise(in->Ptr, mean->Ptr, std->Ptr, out->Ptr);
        return out;
    }
}

UTensorObject* NeuralNetworkObject::Renormalise(UTensorObject* in, UTensorObject* mean, UTensorObject* std, UTensorObject* out)
{
    if(in->GetRows() != mean->GetRows() 
       || in->GetRows() != std->GetRows() 
       || in->GetCols() != mean->GetCols() 
       || in->GetCols() != std->GetCols())
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Incompatible dimensions for renormalisation."));
        return in;
    }
    else
    {
        EigenUtils::Renormalise(in->Ptr, mean->Ptr, std->Ptr, out->Ptr);
        return out;
    }
}

UTensorObject* NeuralNetworkObject::Layer(UTensorObject* in, UTensorObject* W, UTensorObject* b, UTensorObject* out)
{
    if(in->GetRows() != W->GetCols() || W->GetRows() != b->GetRows() || in->GetCols() != b->GetCols())
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Incompatible dimensions for feed-forward."));
        return in;
    }
    else
    {
        EigenUtils::Layer(in->Ptr, W->Ptr, b->Ptr, out->Ptr);
        return out;
    }
}

UTensorObject* NeuralNetworkObject::Blend(UTensorObject* T, UTensorObject* W, float w)
{
    if(T->GetRows() != W->GetRows() || T->GetCols() != W->GetCols())
    {
        UE_LOG(LogPFNNBaseNeuralNetwork, Log, TEXT("Incompatible dimensions for blending."));
        return T;
    }
    else
    {
        EigenUtils::Blend(T->Ptr, W->Ptr, w);
        return T;
    }
}