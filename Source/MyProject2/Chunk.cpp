// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunk.h"


// Sets default values
AChunk::AChunk() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(Scene);

	Mesh_Block = CreateDefaultSubobject<UStaticMesh>(TEXT("SM_Cube"));

	this->HISMC = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
	this->HISMC->RegisterComponent();
	this->HISMC->SetStaticMesh(Mesh_Block);
	this->HISMC->SetFlags(RF_Transactional);
	this->HISMC->SetWorldLocation(FVector(100, 100, 100));

	this->HISMC->AttachTo(Scene);
	*/
	//this->AddInstanceComponent(this->hismc);

	//Create a Static Mesh for our Actor
	//SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	this->HISMC = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HierarchicalInstancedStaticMesh"));

	SetRootComponent(this->HISMC);
}

// Called when the game starts or when spawned
void AChunk::BeginPlay() {
	Super::BeginPlay();
	/*
	// First block
	this->HISMC->AddInstance(FTransform(FVector(200, 200, 200)));

	// Second block
	this->HISMC->AddInstance(FTransform(FVector(500, 200, 0)));

	// Third block
	this->HISMC->AddInstance(FTransform(FVector(200, 500, 500)));
	*/
}

// Called every frame
void AChunk::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AChunk::OnConstruction(const FTransform & Transform) {

	/*if(this->HISMC->GetInstanceCount() > 0) {
		return;
	}*/

	// Register all the components
	RegisterAllComponents();

	// Build blocks
	/*for(int32 i = 0; i < blockNum; i++) {
		this->blocks[i] = 1;
	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Blocks created"));

	this->HISMC->ClearInstances();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Instances cleared"));
	Blocky::MapCreator<EdgeLength> mapCreator;

	mapCreator.CreateLandscape(blocks);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Blocks rendered"));

	this->HISMC->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->HISMC->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	this->HISMC->OnComponentBeginOverlap.AddDynamic(this, &AChunk::OnOverlapBegin);
	this->HISMC->OnComponentHit.AddDynamic(this, &AChunk::OnHit);

	for(size_t x = 0; x < EdgeLength; ++x) {
		for(size_t y = 0; y < EdgeLength; ++y) {
			for(size_t z = 0; z < EdgeLength; ++z) {

				switch(blocks[x][y][z]) {
					case 1:
						this->HISMC->AddInstance(FTransform(FVector(x * 200, z * 200, y * 200)));
						break;
				}

			}
		}
	}
	/*
	for(int32 i = 0; i < blockNum; i++) {
		FVector Location;
		std::array<int32, 3> pos;

		pos = GetBlock3DPos(i);

		Location.X = pos[0] * 200;
		Location.Y = pos[1] * 200;
		Location.Z = pos[2] * 200;

		this->HISMC->AddInstance(FTransform(Location));
	}
	*/
}

void AChunk::OnOverlapBegin(class UPrimitiveComponent * srcComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString(TEXT("Block Overlap Index: %s")) + srcComp->GetFullName());
		}
	}
}

void AChunk::OnHit(class UPrimitiveComponent * srcComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	if((OtherActor != nullptr) && (OtherActor != this)) {
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hit: "));
		}
	}
}

/*
void AChunk::CreateLandscape() {
	noise::module::Perlin myModule;
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;

	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(EdgeLength, EdgeLength);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();


	for(int x = 0; x < EdgeLength; ++x) {
		for(int z = 0; z < EdgeLength; ++z) {
			// Use the noise library to get the height value of x, z
			//float height = m_pChunkManager->GetNoiseValue(x, z);

			// Use the height map texture to get the height value of x, z
			float height = (heightMap.GetValue(x, z) * (EdgeLength - 1) * 1.0f) * 1.0f;

			for(int y = 0; y < height; y++) {
				//blocks[x][y][z].SetActive(true);
				blocks[x][y][z] = 1;
			}
		}
	}
}
*/
/*
int32 AChunk::GetBlockIndex(int32 x, int32 y, int32 z) {
	return x + y * EdgeLength + z * EdgeLength * EdgeLength;
}

std::array<int32, 3> AChunk::GetBlock3DPos(int32 index) {
	std::array<int32, 3> res;

	res[0] = index / (EdgeLength*EdgeLength); // X
	res[1] = index % (EdgeLength*EdgeLength) /EdgeLength; // Y
	res[2] = index - res[1] * EdgeLength - res[0] * (EdgeLength*EdgeLength); // Z

	return res;
}
*/
