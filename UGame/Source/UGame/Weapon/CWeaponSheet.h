#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "CWeaponSheet.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSheet : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		FName Socket;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		FString Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		float Power;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		FString Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		float PlayRate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "WeaponSheet")
		FString AnimInstance;

};

UCLASS()
class UGAME_API UCWeaponSheet : public UObject
{
	GENERATED_BODY()

public:
	UCWeaponSheet();

	const FWeaponSheet* GetRowFromIndex(int rowIndex);
	const FWeaponSheet* GetRowFromName(FString Vaule);

	int GetRowCount() { return DataArray.Num(); }
	const TArray<FWeaponSheet*>& GetDataArray() { return DataArray; }

	FString GetFullWeaponClassPath(FString Name);
	FString GetFullMontagePath(FString Name);
	FString GetFullAnimInstancePath(FString Name);
private:
	UDataTable* DataTable;
	TArray<FWeaponSheet*> DataArray;
};
