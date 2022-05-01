#include "TAPlayerHUD.h"
#include "Engine/Canvas.h"

void ATAPlayerHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void ATAPlayerHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);

	const float HalfLineSize = 3.f;
	const float LineThickness = 1.f;

	const FLinearColor LineColor = FLinearColor::White;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
