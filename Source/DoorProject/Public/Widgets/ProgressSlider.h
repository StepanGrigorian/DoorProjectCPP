// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressSlider.generated.h"

class UBorder;
class UImage;

UCLASS()
class DOORPROJECT_API UProgressSlider : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UBorder> Border = nullptr;
	UPROPERTY(meta = (BindWidget))
		TObjectPtr<UImage> SliderImage = nullptr;
};
