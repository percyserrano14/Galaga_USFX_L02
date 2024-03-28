// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Galaga_USFX_L02GameMode.generated.h"

class ANaveEnemiga;
class ANaveEnemigaCaza;
class ANaveEnemigaTransporte;

UCLASS(MinimalAPI)
class AGalaga_USFX_L02GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGalaga_USFX_L02GameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ANaveEnemiga* NaveEnemiga01;
	ANaveEnemigaCaza* NaveEnemigaCaza01;
	ANaveEnemigaCaza* NaveEnemigaCaza02;
	ANaveEnemigaTransporte* NaveEnemigaTransporte01;
	ANaveEnemigaTransporte* NaveEnemigaTransporte02;

public:
	TArray<ANaveEnemiga*> TANavesEnemigas;
	TArray<ANaveEnemigaCaza*> TANavesEnemigasCaza;
	TArray<ANaveEnemigaTransporte*> TANavesEnemigasTransporte;
	UPROPERTY()
	TMap<ANaveEnemiga*, FVector> TMPosicionesNavesEnemigas;


	void MostrarPosicionesNavesEnemigas();
public:
	FTimerHandle TimerHandle_EliminarEnemigos;
	FTimerHandle TimerHandle_SpawnearEnemigos;
	FTimerHandle TimerHandle_ListarEnemigos;
	FTimerHandle TimerHandle_DetenerProceso;
	/*float DetenerProceso;
	float ListarEnemigos;
	float SpawnearEnemigos;
	float EliminarEnemigos;*/
public:
	void DetenerProceso();
	void EliminarEnemigos();
	void SpawnearEnemigos();
	void ListarEnemigos();

};





