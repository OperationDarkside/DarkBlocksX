// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// STD
#include <array>

#include "MapCreator.h"

// Unreal
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

UCLASS()
class MYPROJECT2_API AChunk : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChunk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	/*The static mesh of our actor*/
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SM;

	const static int32 EdgeLength = 16;

	/*A random seed. Editing this, the editor will generate
	new random locations*/
	UPROPERTY(EditAnywhere, Category = "Construction")
		int32 RandomSeed;

private:

	//UPROPERTY(EditAnywhere)
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
		UHierarchicalInstancedStaticMeshComponent* HISMC;

	UPROPERTY(VisibleAnywhere)
		UStaticMesh* Mesh_Block;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent * srcComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnHit(class UPrimitiveComponent * srcComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	const static int32 blockNum = EdgeLength * EdgeLength * EdgeLength;

	//std::array<unsigned int, blockNum> blocks;
	unsigned int blocks[EdgeLength][EdgeLength][EdgeLength];

	//void CreateLandscape();

	//int32 GetBlockIndex(int32 x, int32 y, int32 z);
	//std::array<int32, 3> GetBlock3DPos(int32 index);
};
