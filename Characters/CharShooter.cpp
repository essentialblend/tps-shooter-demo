
#include "CharShooter.h"

#include "Components/CapsuleComponent.h"
#include "TPSProject/TPSProjectGameModeBase.h"
#include "TPSProject/Actors/GunActor.h"

// Sets default values
ACharShooter::ACharShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharShooter::BeginPlay()
{
	Super::BeginPlay();
	GunActor = GetWorld()->SpawnActor<AGunActor>(GunClassRef);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	
	GunActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	GunActor->SetOwner(this);
	CurrentHP = MaxHP;
}

// Called to bind functionality to input
void ACharShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACharShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACharShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ACharShooter::LookUpRate); //For Joystick.
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ACharShooter::LookRightRate); //For Joystick.
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACharShooter::FireAt);
}

void ACharShooter::MoveForward(const float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ACharShooter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ACharShooter::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * Rate * GetWorld()->GetDeltaSeconds());
}

void ACharShooter::LookRightRate(float Value)
{
	AddControllerYawInput(Value * Rate * GetWorld()->GetDeltaSeconds());
}

void ACharShooter::FireAt()
{
	if(GunActor == nullptr)
	{
		return;
	}
	GunActor->Shoot();
}

float ACharShooter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(DamageCauser == this) return 0.0f;
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(IsCharDead()) return 0.0f;
	DamageToApply = FMath::Min(CurrentHP, DamageToApply);
	CurrentHP -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Actor %s took %f damage! Remaining HP: %f"), *GetName(), DamageToApply, CurrentHP);

	if(IsCharDead())
	{
		ATPSProjectGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATPSProjectGameModeBase>();
		if(GameMode != nullptr) GameMode->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}
	return DamageToApply;
}

bool ACharShooter::IsCharDead() const
{
	return CurrentHP <= 0;
}

float ACharShooter::GetHealthPercent() const
{
	return (CurrentHP / MaxHP);
}



