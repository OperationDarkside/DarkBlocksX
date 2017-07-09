// Fill out your copyright notice in the Description page of Project Settings.
#include "McCharacter.h"
#include "MyProject2.h"


// Sets default values
AMcCharacter::AMcCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// GetMesh()->SetCollisionProfileName(FName("OverlapAll"));

	BaseCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("PunchSphere"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/M_Floor.M_Floor'"));

	if(Material.Object != NULL) {
		UMaterial* TheMaterial = (UMaterial*) Material.Object;
		UMaterialInstanceDynamic* TheMaterial_Dyn = UMaterialInstanceDynamic::Create(TheMaterial, BaseCollisionComp);
		BaseCollisionComp->SetMaterial(0, TheMaterial_Dyn);
	}

	BaseCollisionComp->SetCollisionProfileName(FName("OverlapAll"));
	BaseCollisionComp->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	BaseCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMcCharacter::OnOverlapBegin);
	BaseCollisionComp->AddRelativeLocation(FVector(200, 0, -100));
	BaseCollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	BaseCollisionComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AMcCharacter::BeginPlay() {
	Super::BeginPlay();

	if(GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using McCharacter!"));
	}
}

// Called every frame
void AMcCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	InputComponent->BindAxis("MoveX", this, &AMcCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMcCharacter::MoveY);

	PlayerInputComponent->BindAxis("MouseX", this, &AMcCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &AMcCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMcCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMcCharacter::StopJump);
}

void AMcCharacter::MoveX(float Val) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Val);
}

void AMcCharacter::MoveY(float Val) {
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Val);
}

void AMcCharacter::StartJump() {
	bPressedJump = true;
}

void AMcCharacter::StopJump() {
	bPressedJump = false;
}

void AMcCharacter::OnOverlapBegin(UPrimitiveComponent * srcComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		if(GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Character Overlap Index: "));
		}
	}
}
