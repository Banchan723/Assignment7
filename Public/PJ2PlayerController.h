#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PJ2PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECT2_API APJ2PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APJ2PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	// IMC 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	// 움직임 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction*JumpAction;
	// 점프 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	// 마우스로 화면 이동 변수

protected:
	virtual void BeginPlay() override;
};
