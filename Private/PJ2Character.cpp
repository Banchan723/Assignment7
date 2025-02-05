#include "PJ2Character.h"
#include "PJ2PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


APJ2Character::APJ2Character() // 생성자
{	
	PrimaryActorTick.bCanEverTick = false; // Tick 비활성화

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent); // 루트 컴포넌트에 붙히기
	SpringArmComp->TargetArmLength = 300.0f; // 길이는 300
	SpringArmComp->bUsePawnControlRotation = true; // 마우스로 화면을 회전하면 스프링 암도 따라가게 (활성화)

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName); // 스프링암 마지막에 카메라 부착
	CameraComp->bUsePawnControlRotation = false; // 마우스로 화면을 회전하면 카메라는 안따라게 (비활성화)

}


void APJ2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // 입력 컴포넌트 함수
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// EnhancedInput 컴포넌트를 사용일때
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{   // 플레이어컨트롤러를 현재 컨트롤러일때
		if (APJ2PlayerController* PlayerController = Cast<APJ2PlayerController>(GetController()))
		{   // MoveInput이 설정 되어있으면 MoveAction이 플레이어컨트롤러
			if (PlayerController->MoveAction)
			{
				// MoveAction이 실행할때 AP2Character::Move함수가 실행
				EnhancedInput->BindAction( 
					PlayerController->MoveAction, // 플레이어 컨트롤에있는 이동액션
					ETriggerEvent::Triggered,     // 트리거 이벤트
					this,                         // 실행 대상(W, A, S, D)
					&APJ2Character::Move          // 실행 함수
				);
			}

			// JumpInput이 되어있으면 점프액션 호출
			if (PlayerController->JumpAction)
			{
				// 점프 시작(키) 시 AP2Character::StartJump가 호출
				EnhancedInput->BindAction(
					PlayerController->JumpAction, // 점프 액션
					ETriggerEvent::Triggered,     // 트리거 이벤트
					this,                         
					&APJ2Character::StartJump     
				);

				// 점프 종료(떨어질때) 시 AP2Character::StopJump가 호출
				EnhancedInput->BindAction(
					PlayerController->JumpAction, // 점프 액션
					ETriggerEvent::Completed,	  // 트리거 이벤트
					this,
					&APJ2Character::StopJump
				);
			}

			// 카메라를 마우스로 회전하는 설정이 되어있으면 look액션 호출
			if (PlayerController->LookAction)
			{
				// Look액션이 발생하면 PJ2Character::Look 함수 실행
				EnhancedInput->BindAction(
					PlayerController->LookAction,  // 보기 액션
					ETriggerEvent::Triggered,	   // 트리거 이벤트
					this,
					&APJ2Character::Look
				);
			}
		}
	}
}

void APJ2Character::Move(const FInputActionValue& value)
{
	if (!Controller) return; // 컨트롤러가 없으면 리턴
	const FVector2D MoveInput = value.Get<FVector2D>(); // MoveInput은 2D 벡터로 값을 들고옴

	// X축 입력이 있으면 캐릭터가 앞뒤으로 이동
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	// Y축 입력이 있으면 캐릭터가 좌우로 이동
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void APJ2Character::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>()) // 입력이 true면 점프함
	{
		Jump();
	}
}

void APJ2Character::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>()) // 입력이 거짓이면 점프 멈춤
	{
		StopJumping();
	}
}

void APJ2Character::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>(); // LookInput은 2D 벡터로 값을 들고옴

	// X축 입력으로 좌우 회전 (Yaw)
	AddControllerYawInput(LookInput.X);

	// Y축 입력으로 상하 회전 (Pitch)
	AddControllerPitchInput(LookInput.Y);
}
