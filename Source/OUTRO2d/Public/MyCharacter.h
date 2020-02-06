// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class OUTRO2D_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Corpo")
	class UCapsuleComponent* Capsula;
	UPROPERTY(EditAnywhere, Category = "Corpo")
	class UBoxComponent* Caixa;



	UFUNCTION()
	void Direita(float Eixo);
	UFUNCTION()
		void Salto();
	UFUNCTION()
		void AcabouSalto();
	UFUNCTION()
		void SaltaUmaVez();
	UFUNCTION()
		void ResetSalto();
	UFUNCTION()
		void OnOverlapBegins(AActor* actor,AActor* otherActor);
	UFUNCTION()
	void Morre(AActor* actor, AActor* otherActor);
	
	

	UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "Camera")
		class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "rayo")
		FVector Raio = FVector(0.f, 0.f, -40.f);
	bool bSalto;
	bool bDuploSalto;
	float Forca = 100.f;
	float Saltos;
};
