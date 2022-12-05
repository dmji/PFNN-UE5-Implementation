// Fill out your copyright notice in the Description page of Project Settings.


#include "PFNN_NeuralNetwork.h"

PFNN_NeuralNetwork::PFNN_NeuralNetwork()
{
}

PFNN_NeuralNetwork::~PFNN_NeuralNetwork()
{
}

float PFNN_NeuralNetwork::Repeat(float t, float length)
{
    return FMath::Clamp(t - FMath::Floor(t / length) * length, 0.f, length);
}

void PFNN_NeuralNetwork::Predict()
{
    //Normalise Input
    Normalise(X, Xmean, Xstd, Y);

    //Process PFNN
    int index = (int)((Phase / (2.f * PI)) * 50.f);
    ELU(Layer(Y, W0[index], b0[index], Y));
    ELU(Layer(Y, W1[index], b1[index], Y));
    Layer(Y, W2[index], b2[index], Y);

    //Renormalise Output
    Renormalise(Y, Ymean, Ystd, Y);

    //Update Phase

    Phase = Repeat(Phase + (1.f - Damping) * GetOutput(PhaseIndex) * 2.f * PI, 2.f * PI);
}

void PFNN_NeuralNetwork::SetDamping(float value)
{
    Damping = value;
}

float PFNN_NeuralNetwork::GetPhase()
{
    return Phase / (2.f * PI);
}

void PFNN_NeuralNetwork::StoreParametersDerived()
{
    Parameters->Store(Folder + "/Xmean.bin", XDim, 1, "Xmean");
    Parameters->Store(Folder + "/Xstd.bin", XDim, 1, "Xstd");
    Parameters->Store(Folder + "/Ymean.bin", YDim, 1, "Ymean");
    Parameters->Store(Folder + "/Ystd.bin", YDim, 1, "Ystd");
    for(int i = 0; i < 50; i++)
    {
        FString sIdx = FString::Printf(TEXT("%3d"), i);
        Parameters->Store(Folder + "/W0_" + sIdx + ".bin", HDim, XDim, "W0_" + sIdx);
        Parameters->Store(Folder + "/W1_" + sIdx + ".bin", HDim, HDim, "W1_" + sIdx);
        Parameters->Store(Folder + "/W2_" + sIdx + ".bin", YDim, HDim, "W2_" + sIdx);
        Parameters->Store(Folder + "/b0_" + sIdx + ".bin", HDim, 1, "b0_" + sIdx);
        Parameters->Store(Folder + "/b1_" + sIdx + ".bin", HDim, 1, "b1_" + sIdx);
        Parameters->Store(Folder + "/b2_" + sIdx + ".bin", YDim, 1, "b2_" + sIdx);
    }
}

void PFNN_NeuralNetwork::LoadParametersDerived()
{
    Xmean = CreateTensor(Parameters->Load("Xmean"));
    Xstd = CreateTensor(Parameters->Load("Xstd"));
    Ymean = CreateTensor(Parameters->Load("Ymean"));
    Ystd = CreateTensor(Parameters->Load("Ystd"));
    constexpr int32 size = 50;
    W0.SetNum(size);
    W1.SetNum(size);
    W2.SetNum(size);
    b0.SetNum(size);
    b1.SetNum(size);
    b2.SetNum(size);
    for(int i = 0; i < size; i++)
    {
        auto sIdx = FString::Printf(TEXT("%3d"), i);
        W0[i] = CreateTensor(Parameters->Load("W0_" + sIdx));
        W1[i] = CreateTensor(Parameters->Load("W1_" + sIdx));
        W2[i] = CreateTensor(Parameters->Load("W2_" + sIdx));
        b0[i] = CreateTensor(Parameters->Load("b0_" + sIdx));
        b1[i] = CreateTensor(Parameters->Load("b1_" + sIdx));
        b2[i] = CreateTensor(Parameters->Load("b2_" + sIdx));
    }
    X = CreateTensor(XDim, 1, "X");
    Y = CreateTensor(YDim, 1, "Y");
    Phase = 0.f;
    Damping = 0.f;
}