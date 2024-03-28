// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L02GameMode.h"
#include "Galaga_USFX_L02Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaCaza.h"
#include "NaveEnemigaTransporte.h"
#include "TimerManager.h"

AGalaga_USFX_L02GameMode::AGalaga_USFX_L02GameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AGalaga_USFX_L02Pawn::StaticClass();
	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L02GameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set the game state to playing
	

	GetWorldTimerManager().SetTimer(TimerHandle_EliminarEnemigos, this, &AGalaga_USFX_L02GameMode::EliminarEnemigos, 15.0f, true);

	// Configurar temporizador para spawnear enemigos cada 10 segundos (después de eliminar los anteriores)
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnearEnemigos, this, &AGalaga_USFX_L02GameMode::SpawnearEnemigos, 10.0f, true, 10.0f);

	// Configurar temporizador para listar enemigos y sus posiciones cada 15 segundos
	GetWorldTimerManager().SetTimer(TimerHandle_ListarEnemigos, this, &AGalaga_USFX_L02GameMode::ListarEnemigos, 15.0f, true, 15.0f);

	// Configurar temporizador para detener el proceso después de 40 segundos
	GetWorldTimerManager().SetTimer(TimerHandle_DetenerProceso, this, &AGalaga_USFX_L02GameMode::DetenerProceso, 40.0f, false);

	//FVector ubicacionInicialNavesEnemigas = FVector(0.0f, 0.0f, 150.0f);
	//FVector ubicacionActualNaveEnemiga = ubicacionInicialNavesEnemigas;
	//FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	//UWorld* const World = GetWorld();
	//if (World != nullptr)
	//{
	//
	//	for (int i = 0; i < 15; i++) {
	//		ANaveEnemigaCaza* NaveEnemigaCazaActual = World->SpawnActor<ANaveEnemigaCaza>(ubicacionActualNaveEnemiga, rotacionNave);
	//		//TANavesEnemigasCaza.Add(NaveEnemigaCazaActual);
	//	/*	NaveEnemigaCazaActual->SetNombre("nave enemiga caza " + FString::FromInt(i));
	//		TANavesEnemigas.Add(NaveEnemigaCazaActual);
	//		TMPosicionesNavesEnemigas.Add(NaveEnemigaCazaActual, ubicacionActualNaveEnemiga);*/

	//		//ubicacionActualNaveEnemiga.Y = ubicacionActualNaveEnemiga.Y + 150.0f;
	//	}

	//	ubicacionActualNaveEnemiga.X = ubicacionActualNaveEnemiga.X -150.0f;
	//	ubicacionActualNaveEnemiga.Y = ubicacionInicialNavesEnemigas.Y;
	//	//for (int j = 0; j < 5; j++) {
	//	//	
	//	//	ANaveEnemigaTransporte* NaveEnemigaTransporteActual = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionActualNaveEnemiga, rotacionNave);
	//	//	//TANavesEnemigasTransporte.Add(NaveEnemigaTransporteActual);
	//	//	NaveEnemigaTransporteActual->SetNombre("nave enemiga transporte" + FString::FromInt(j));
	//	//	TANavesEnemigas.Add(NaveEnemigaTransporteActual);
	//	//	TMPosicionesNavesEnemigas.Add(NaveEnemigaTransporteActual, ubicacionActualNaveEnemiga);

	//	//	ubicacionActualNaveEnemiga.Y = ubicacionActualNaveEnemiga.Y + 150.0f;
	//	//}

	//	FTimerHandle FTHVisualizacionPosicionesNavesEnemigas;

	//	GetWorldTimerManager().SetTimer(FTHVisualizacionPosicionesNavesEnemigas, this, &AGalaga_USFX_L02GameMode::MostrarPosicionesNavesEnemigas, 1.0f, true);
		
	//}
	
}

void AGalaga_USFX_L02GameMode::MostrarPosicionesNavesEnemigas()
{
	for (auto ElementoActual : TMPosicionesNavesEnemigas) {
		ANaveEnemiga* naveEnemigaActual = ElementoActual.Key;
		FVector posicionActualNaveEnemiga = ElementoActual.Value;
		FString mensaje = "La nave " + naveEnemigaActual->GetNombre() + " esta en la posicion> " + posicionActualNaveEnemiga.ToString();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-100, 250.f, FColor::Green, mensaje);

			/*FString mensaje = "Nombre NaveEnemiga: " + Clave->GetNombre() + " Posicion NaveEnemiga: " + Valor.ToString();
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, mensaje);*/

		}

		TMPosicionesNavesEnemigas[naveEnemigaActual] = naveEnemigaActual->GetActorLocation();
	}
}

void AGalaga_USFX_L02GameMode::EliminarEnemigos() {
	if (TANavesEnemigasCaza.Num() >= 2)
	{
		// Crear un conjunto para almacenar índices aleatorios de los enemigos
		TSet<int32> IndicesAleatorios;

		// Generar dos índices aleatorios únicos
		while (IndicesAleatorios.Num() < 2)
		{
			int32 IndiceAleatorio = FMath::RandRange(0, TANavesEnemigasCaza.Num() - 1);
			IndicesAleatorios.Add(IndiceAleatorio);
		}

		// Crear un array para almacenar los índices de las naves a eliminar
		TArray<int32> IndicesAEliminar;
		for (int32 Indice : IndicesAleatorios)
		{
			IndicesAEliminar.Add(Indice);
		}

		// Iterar sobre los índices de las naves a eliminar y destruir las naves correspondientes
		for (int32 Indice : IndicesAEliminar)
		{
			ANaveEnemigaCaza* EnemigoAEliminar = TANavesEnemigasCaza[Indice];
			if (EnemigoAEliminar)
			{
				EnemigoAEliminar->Destroy();
			}
		}

		// Eliminar las naves de la lista después de destruirlas
		for (int32 Indice : IndicesAEliminar)
		{
			TANavesEnemigasCaza.RemoveAt(Indice);
		}
	}
	else
	{
		// Manejar el caso en el que no haya suficientes enemigos para eliminar
		UE_LOG(LogTemp, Warning, TEXT("No hay suficientes enemigos para eliminar"));
	}
}

void AGalaga_USFX_L02GameMode::SpawnearEnemigos() {

	FVector ubicacionInicialNavesEnemigas = FVector(0.0f, 0.0f, 150.0f);
	FVector ubicacionActualNaveEnemiga = ubicacionInicialNavesEnemigas;
	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (int i = 0; i < 3; i++)
		{
			ANaveEnemigaCaza* NaveEnemigaCazaActual = World->SpawnActor<ANaveEnemigaCaza>(ubicacionActualNaveEnemiga, rotacionNave);
			// Aquí puedes agregar la lógica adicional que necesites para configurar las naves enemigas
			// TANavesEnemigasCaza.Add(NaveEnemigaCazaActual);
			// NaveEnemigaCazaActual->SetNombre("nave enemiga caza " + FString::FromInt(i));
			// TANavesEnemigas.Add(NaveEnemigaCazaActual);
			// TMPosicionesNavesEnemigas.Add(NaveEnemigaCazaActual, ubicacionActualNaveEnemiga);

			// Mover la ubicación de spawn para la próxima nave enemiga
			ubicacionActualNaveEnemiga.Y += 150.0f;
		}

		// Configurar un temporizador para mostrar las posiciones de las naves enemigas
		//FTimerHandle FTHVisualizacionPosicionesNavesEnemigas;
		//GetWorldTimerManager().SetTimer(FTHVisualizacionPosicionesNavesEnemigas, this, &AGalaga_USFX_L02GameMode::MostrarPosicionesNavesEnemigas, 1.0f, true);
	}
}

void AGalaga_USFX_L02GameMode::ListarEnemigos() {
	// Verificar si aún estamos dentro del límite de tiempo de 40 segundos
	if (GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle_DetenerProceso) < 300.0f)
	{
		// Listar los enemigos y sus posiciones
	}
}

void AGalaga_USFX_L02GameMode::DetenerProceso() {
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_EliminarEnemigos);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_SpawnearEnemigos);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ListarEnemigos);
}