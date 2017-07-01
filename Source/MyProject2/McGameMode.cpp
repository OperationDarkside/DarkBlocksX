// Fill out your copyright notice in the Description page of Project Settings.

#include "McGameMode.h"
#include "McCharacter.h"

AMcGameMode::AMcGameMode() {
	DefaultPawnClass = AMcCharacter::StaticClass();
}