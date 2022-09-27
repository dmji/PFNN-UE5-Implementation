// Fill out your copyright notice in the Description page of Project Settings.


#include "PFNNAnimInstance.h"
#include "PFNNCharacter.h"
#include "DrawDebugHelpers.h"

void UPFNNAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	APFNNCharacter* OwningCharacter = Cast<APFNNCharacter>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningTrajectoryComponent = OwningCharacter->GetTrajectoryComponent();
	}

}

void UPFNNAnimInstance::NativeUpdateAnimation(float arg_DeltaTimeX)
{
	Super::NativeUpdateAnimation(arg_DeltaTimeX);

	APFNNCharacter* OwningCharacter = Cast<APFNNCharacter>(TryGetPawnOwner());
	if(OwningCharacter)
	{
		OwningTrajectoryComponent = OwningCharacter->GetTrajectoryComponent();
	}
}

UTrajectoryComponent* UPFNNAnimInstance::GetOwningTrajectoryComponent()
{
	return OwningTrajectoryComponent;
}
