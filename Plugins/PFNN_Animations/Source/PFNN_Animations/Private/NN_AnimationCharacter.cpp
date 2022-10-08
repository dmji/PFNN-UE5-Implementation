// Fill out your copyright notice in the Description page of Project Settings.


#include "NN_AnimationCharacter.h"

// Sets default values
ANN_AnimationCharacter::ANN_AnimationCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANN_AnimationCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANN_AnimationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANN_AnimationCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

