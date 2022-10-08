// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UI/SAssetLinkWidget.h"

#include "LinterStyle.h"

#include "AssetRegistryModule.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/SBoxPanel.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAssetLinkWidget::Construct(const FArguments& Args)
{
	const float PaddingAmount = FLinterStyle::Get()->GetFloat("Linter.Padding");
	AssetData = Args._AssetData;

	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(SHyperlink)
			.Text(FText::FromName(AssetData.Get().AssetName))
			.OnNavigate_Lambda([&]()
			{
				FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
				FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
				TArray<FAssetData> AssetDatas;
				AssetDatas.Push(AssetRegistryModule.Get().GetAssetByObjectPath(AssetData.Get().ObjectPath));
				ContentBrowserModule.Get().SyncBrowserToAssets(AssetDatas);
			})
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
