// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class TPSPROJECT_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp = nullptr;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound = nullptr;	
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitParticle = nullptr;
	UPROPERTY(EditAnywhere)
	float MaxRange{5000.f};
	UPROPERTY(EditAnywhere)
	float Damage{10};
	bool GunShotTrace(FHitResult& HitResult, FVector& ShotDir) const;
	AController* GetOwnerContrlr() const;
};