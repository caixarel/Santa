// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Personagem.generated.h"

UCLASS()
class OUTRO2D_API APersonagem : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APersonagem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Corpo")
	class UBoxComponent* Capsula;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Corpo")
	class UBoxComponent* Capsula2;

	UPROPERTY(EditAnywhere, Category = "Corpo")
		class UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere, Category = "Corpo")
		class UPaperFlipbookComponent* flipBook;

	



	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector direction;
	int distancia;
	float TempoExecucao;
	float alturaDelta;

	//speed of the movement
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Velocidade = 500;
	//time used for moving the actor in one direction
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float DuracaoDoMovimento = 1.5f;
	
};
