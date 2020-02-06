// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Outro.generated.h"


UCLASS()
class OUTRO2D_API AOutro : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOutro();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "Camera")
		class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintREadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmCamera;
	

	

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
		void Colisao(AActor* Actor,AActor* OtherActor);
	UFUNCTION()
		void Dashing();
	UFUNCTION()
		void Matar();
	UFUNCTION()
		void FazerDash();
	UFUNCTION()
		void FimEscada(AActor* Actor, AActor* OtherActor);
	UFUNCTION()
		void SubirEscada(float Eixo);
	UFUNCTION()
		void Shoot();
	UFUNCTION()
		void EndShoot();
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ABalas>SHootBall;

	FTimerHandle Temporizador;
	FTimerHandle Dash;
	FTimerHandle Invencibilidade;
	FTimerHandle CandieTemp;
	FTimerHandle canshootball;
	int time = 0;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool bSalto;
	bool bDuploSalto;
	bool PodeMatar;
	float Saltos;
	bool bCanDash=true;
	bool bCanDie=true;
	bool bcanShoot = true;
	bool bShootMode = false;

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInvencible;

	

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bIsMovingRight;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UParticleSystemComponent* Particulas;

	bool bPodeSubir;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float subir = 50;
	
	UFUNCTION()
		bool EstaInvencivel(bool invencivel);
	UFUNCTION()
		void JaNaoEstaInvencivel();
	UFUNCTION()
		void CanDie();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPaperFlipbookComponent* animation;

	

};
