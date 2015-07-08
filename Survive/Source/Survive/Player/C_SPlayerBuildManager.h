// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SBuildable.h"
#include "C_SPlayerBuildManager.generated.h"

//NO MIRAR
// GOD DON'T YOU KILL ME FOR THIS, AN STRANGE ERROR IS THE CULPRIT
//Esto se sabe mirando el archivo Config/DefaultEngine.ini, y encontrado la l�nea donde est� definido :)
#define PlayerMovingTraceChannel   ECC_GameTraceChannel1
#define PlayerPointingTraceChannel ECC_GameTraceChannel4
//


UENUM(BlueprintType)
enum PlayerBuildingState
{
	Pointing,
	Moving
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVE_API UC_SPlayerBuildManager : public UActorComponent
{
	GENERATED_BODY()

	ACharacter *character;
	PlayerBuildingState currentState;

	bool rotateInputDown;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *targetBuildable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Buildable")
		ASBuildable *lastTargetBuildable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Point")
		FVector targetPoint;

	UC_SPlayerBuildManager();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OnInputMoveBuildable();
	void OnInputRotateBuildableDown();
	void RotateTargetBuildable();
	void OnInputRotateBuildableUp();
	void OnInputRemoveBuildable();

	//Fills the targetBuildable and targetPoint variables, tracing the rays and stuff
	UFUNCTION(BlueprintCallable, Category = "Player Building Target")
		void FillTargetInfo();

	UFUNCTION(BlueprintCallable, Category = "Player Building State")
		PlayerBuildingState GetCurrentBuildingState();

	FORCEINLINE bool Trace(TArray<AActor*> &actorsToIgnore,
						   const FVector& Start, const FVector& End, FHitResult& HitOut, ECollisionChannel TraceChannel);
};
