//
// Blueprint Color Picker
// 
// Slate color picker exposed to Blueprints
//
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


#include "ColorPicker.h"

TSharedRef<SWidget> UColorPicker::RebuildWidget()
{
    // Create the Slate color picker widget
    SlateColorPickerWidget = SNew(SColorPicker)
        .DisplayInlineVersion(bShowInline)
        .OnColorCommitted_Lambda([this](const FLinearColor& NewColor)
            {
                if (this)
                {
                    HandleColorChanged(NewColor);
                }
            });

    // Create OK and Cancel buttons
    TSharedPtr<SButton> OkButton;
    TSharedPtr<SButton> CancelButton;

    // Create button functionality
    OkButton = SNew(SButton)
        .Text(FText::FromString("OK"))
        .OnClicked_Lambda([this]()
            {
                HandleColorOkClicked();
                return FReply::Handled();
            });

    CancelButton = SNew(SButton)
        .Text(FText::FromString("Cancel"))
        .OnClicked_Lambda([this]()
            {
                HandleColorCancelClicked(InitialColor);
                return FReply::Handled();
            });

    // Add the buttons and the color picker widget to a vertical box
    return SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .AutoHeight()
        [
            SlateColorPickerWidget.ToSharedRef()
        ]
        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(5)
        [
            SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(2)
                [
                    OkButton.ToSharedRef()
                ]
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(2)
                [
                    CancelButton.ToSharedRef()
                ]
        ];
}

void UColorPicker::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    // Reset the Slate search box widget to release it from memory
    SlateColorPickerWidget.Reset();
}

void UColorPicker::HandleColorOkClicked()
{
    RemoveFromParent();
}

void UColorPicker::HandleColorCancelClicked(const FLinearColor& Color)
{
    // Return initial color (Discard current color selection)
    OnColorChanged.Broadcast(Color);
    RemoveFromParent();
}

void UColorPicker::HandleColorChanged(const FLinearColor& NewColor)
{
    // Send currently selected color
    OnColorChanged.Broadcast(NewColor);
}
