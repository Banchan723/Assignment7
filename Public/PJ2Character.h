#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PJ2Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class PROJECT2_API APJ2Character : public ACharacter
{
	GENERATED_BODY()

public:
	APJ2Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	// 스프링 암 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	// 카메라 컴포넌트

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	// 이동 함수
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	// 점프 시작 함수
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	// 점프 끝 함수
	UFUNCTION()
	void Look(const FInputActionValue& value);
	// 마우스로 화면 이동 함수
};
