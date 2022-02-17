// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharShooter.generated.h"

class AGunActor;

UCLASS()
class TPSPROJECT_API ACharShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharShooter();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsCharDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void FireAt();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpRate(float Value);
	void LookRightRate(float Value);
	UPROPERTY(EditAnywhere)
	float Rate = 10;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunActor> GunClassRef;
	UPROPERTY()
	AGunActor* GunActor = nullptr;
	UPROPERTY(EditDefaultsOnly)
	float MaxHP{100.f};
	UPROPERTY(EditDefaultsOnly)
	float CurrentHP{0};
	bool bIsPlayerDead = false;
	
	
};
