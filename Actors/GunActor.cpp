#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "TPSProject/Characters/CharShooter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = RootComp;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::Shoot()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
	FHitResult HRes;
	FVector ShotDirection;
	bool bTraceSuccessful = GunShotTrace(OUT HRes, OUT ShotDirection);
	if(bTraceSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("Trace Success"));
		//DrawDebugPoint(GetWorld(), HitRes.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HRes.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, HRes.Location);
		//Calling Damage functions.
		AActor* HitActor = HRes.GetActor();
		if(HitActor == nullptr)	return;
		FPointDamageEvent DamageEvent(Damage, HRes, ShotDirection, nullptr);
		AController* OwnerController = GetOwnerContrlr();
		if(OwnerController == nullptr) return;
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
	
}

bool AGunActor::GunShotTrace(FHitResult& HitResult, FVector& ShotDir) const
{
	AController* OwnerController = GetOwnerContrlr();
	FVector PTransform;
	FRotator PRotator;
	OwnerController->GetPlayerViewPoint(OUT PTransform, OUT PRotator);
	//DrawDebugCamera(GetWorld(), PTransform, PRotator, 90, 2.0f, FColor::Red, true);
	const FVector EndPoint = PTransform + PRotator.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	ShotDir = -PRotator.Vector();
	return GetWorld()->LineTraceSingleByChannel(HitResult, PTransform, EndPoint, ECC_GameTraceChannel1, Params);
	
}

AController* AGunActor::GetOwnerContrlr() const
{
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if(PlayerPawn == nullptr) return nullptr;
	return PlayerPawn->GetController();
}