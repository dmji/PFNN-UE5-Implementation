// Fill out your copyright notice in the Description page of Project Settings.


#include "ParametersObject.h"

UMatrixObject::UMatrixObject(int rows, int cols, FString id)
    : Rows(rows), Cols(cols), ID(id)
{
    Values.AddZeroed(rows);
    for(int i = 0; i < rows; i++)
        Values[i].AddZeroed(cols);
}
