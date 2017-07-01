// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "McCharacter.generated.h"

UCLASS()
class MYPROJECT2_API AMcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles moving forward/backward
	UFUNCTION()
	void MoveX(float Val);
	//handles strafing
	UFUNCTION()
	void MoveY(float Val);
	// Sets jump flag when key is pressed.
	UFUNCTION()
	void StartJump();
	// Clears jump flag when key is released.
	UFUNCTION()
	void StopJump();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
		USphereComponent* BaseCollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		UStaticMesh* CollisionMesh;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent * srcComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
