#include "CWeaponSheet.h"
#include "Global.h"

UCWeaponSheet::UCWeaponSheet()
{
	FString path = L"";
	path = L"DataTable'/Game/Weapon/Weapon.Weapon'";

	ConstructorHelpers::FObjectFinder<UDataTable> table(*path);
	if (table.Succeeded())
	{
		DataTable = table.Object;
		DataTable->GetAllRows(L"", DataArray);
	}
}

const FWeaponSheet * UCWeaponSheet::GetRowFromIndex(int rowIndex)
{
	return DataArray[rowIndex];
}

const FWeaponSheet * UCWeaponSheet::GetRowFromName(FString Vaule)
{
	for (FWeaponSheet* sheet : DataArray)
	{
		if (sheet->Name == Vaule)
			return sheet;
	}
	return NULL;
}

FString UCWeaponSheet::GetFullWeaponClassPath(FString Name)
{
	FString temp = "";
	temp.Append("Blueprint'/Game/Weapon/");
	temp.Append(Name);
	temp.Append(".");
	temp.Append(Name);
	temp.Append("_C'");

	return temp;
}

FString UCWeaponSheet::GetFullMontagePath(FString Name)
{
	FString temp = "";
	temp.Append("AnimMontage'/Game/Character/Montages/");
	temp.Append(Name);
	temp.Append(".");
	temp.Append(Name);
	temp.Append("'");

	return temp;
}

FString UCWeaponSheet::GetFullAnimInstancePath(FString Name)
{
	//AnimBlueprint'/Game/Player/BP_CPlayer_Bow.BP_CPlayer_Bow'
	FString temp = "";
	temp.Append("AnimBlueprint'/Game/Player/");
	temp.Append(Name);
	temp.Append(".");
	temp.Append(Name);
	temp.Append("_C'");

	return temp;
}
