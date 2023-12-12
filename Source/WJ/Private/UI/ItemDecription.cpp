// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemDecription.h"
#include "Components/TextBlock.h"

void UItemDecription::SetFocus(const bool _result) noexcept
{
}

void UItemDecription::SetDescriptionTitle(const FString& _title) noexcept
{
	auto widget = Cast<UTextBlock>(GetWidgetFromName(FName("TextBlock")));
	if (widget == nullptr)
		return;
	
	widget->SetText(FText::FromString(_title));
}
