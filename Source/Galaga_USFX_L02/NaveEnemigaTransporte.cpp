// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaTransporte.h"

void ANaveEnemigaTransporte::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}

ANaveEnemigaTransporte::ANaveEnemigaTransporte()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	mallaNaveEnemiga->SetStaticMesh(malla.Object);

	dimensionCargaOcupada = 300.0f;
	dimensionCargaDisponible = 700.0f;
}

void ANaveEnemigaTransporte::Mover(float DeltaTime)
{
	// Obtiene la posici�n actual del actor
	FVector PosicionActual = GetActorLocation();

	// Genera nuevas coordenadas X e Y aleatorias
	float NuevaX = FMath::RandRange(-1000.0f, 1000.0f) * (DeltaTime / 1000.0f);
	float NuevaY = FMath::RandRange(-1000.0f, 1000.0f) * (DeltaTime / 1000.0f);
	float NuevaZ = FMath::RandRange(-1000.0f, 1000.0f) * DeltaTime;

	// Crea un nuevo vector de posici�n con las coordenadas aleatorias y la misma Z que la posici�n actual
	FVector NuevaPosicion = FVector(PosicionActual.X + NuevaX, PosicionActual.Y + NuevaY, PosicionActual.Z + NuevaZ);

	// Establece la nueva posici�n del actor
	SetActorLocation(NuevaPosicion);
}

void ANaveEnemigaTransporte::Cargar(float dimensionCarga, float pesoCarga)
{
	dimensionCargaOcupada = dimensionCargaDisponible - dimensionCarga;
}
