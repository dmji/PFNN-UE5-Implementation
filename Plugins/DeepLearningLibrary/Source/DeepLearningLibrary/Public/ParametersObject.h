// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API UMatrixObject
{
public:
    UMatrixObject(int rows, int cols, FString id);

public:
    TArray<TArray<float>> Values;
    int32 Rows, Cols;
    FString ID;
};

/**
 * 
 */
class DEEPLEARNINGLIBRARY_API UParametersObject
{
public:
    /*
    void Store(FString fn, int rows, int cols, FString id)
    {
        for(int i = 0; i < Matrices.Num(); i++)
        {
            if(Matrices[i] != null)
            {
                if(Matrices[i].ID == id)
                {
                    Debug.Log("Matrix with ID " + id + " already contained.");
                    return;
                }
            }
        }
        ArrayExtensions.Add(ref Matrices, ReadBinary(fn, rows, cols, id));
    }

    public Matrix Load(string id)
    {
        Matrix matrix = System.Array.Find(Matrices, x = > x.ID == id);
        if(matrix == null)
        {
            Debug.Log("Matrix with ID " + id + " not found.");
        }
        return matrix;
    }

    void Clear()
    {
        ArrayExtensions.Resize(ref Matrices, 0);
    }

    private Matrix ReadBinary(string fn, int rows, int cols, string id)
    {
        if(File.Exists(fn))
        {
            Matrix matrix = new Matrix(rows, cols, id);
            BinaryReader reader = new BinaryReader(File.Open(fn, FileMode.Open));
            int errors = 0;
            for(int x = 0; x < rows; x++)
            {
                for(int y = 0; y < cols; y++)
                {
                    try
                    {
                        matrix.Values[x].Values[y] = reader.ReadSingle();
                    }
                    catch
                    {
                        errors += 1;
                    }
                }
            }
            reader.Close();
            if(errors > 0)
            {
                Debug.Log("There were " + errors + " errors reading file at path " + fn + ".");
                return null;
            }
            else
            {
                return matrix;
            }
        }
        else
        {
            Debug.Log("File at path " + fn + " does not exist.");
            return null;
        }
    }
    */
    bool Validate()
    {
        for(int i = 0; i < Matrices.Num(); i++)
        {
            if(!Matrices.IsValidIndex(i))
                return false;
        }
        return true;
    }

public:
    TArray<UMatrixObject> Matrices;
};
