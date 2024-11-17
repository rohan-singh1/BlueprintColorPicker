//
// Blueprint Color Picker
// 
// Slate color picker exposed to Blueprints
//
// The MIT License (MIT)
//
// Copyright (c) 2024 Rohan Singh
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "ColorPicker.generated.h"

class SColorPicker;

/**
 *
 */
UCLASS(BlueprintType)
class BLUEPRINTCOLORPICKER_API UColorPicker : public UWidget
{
	GENERATED_BODY()

public:
	// Function to construct the Slate widget
	virtual TSharedRef<SWidget> RebuildWidget() override;

	// Function to release Slate resources
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	// Constructor
	UColorPicker(const FObjectInitializer& ObjectInitializer);

	// Declare a dynamic multicast delegate for search text changes
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnColorChanged, const FLinearColor&, NewColor);

	// Delegate to signal different color selected by the user
	UPROPERTY(BlueprintAssignable, Category = "Blueprint Color Picker")
	FOnColorChanged OnColorChanged;

	// The initial color selected when the Color Picker widget is constructed (To show the existing color of an object)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	FLinearColor InitialColor;

	// Background color of the Color Picker widget area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	FLinearColor BackgroundColor;

	// To specify whether to show a compact version of the color picker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bShowInline;

	// To allow user to select color with transparency value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bUseAlpha;

	// To specify whether to close the parent window (true in case of context menu)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Blueprint Color Picker")
	bool bForContextMenu;

private:
	TSharedPtr<SColorPicker> SlateColorPickerWidget;

	void HandleColorChanged(const FLinearColor& NewColor);
	void HandleColorOkClicked();
	void HandleColorCancelClicked(const FLinearColor& PreviousColor);
};
