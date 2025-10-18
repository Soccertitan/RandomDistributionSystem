// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Engine/DataTable.h"
#include "RandomDistributionTypes.generated.h"

/**
 * The base struct that defines an item. Can be subclassed in C++ to allow new types of data to be
 * defined in the RandomDistributionDataTable.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem
{
	GENERATED_BODY()
};

/**
 * A special struct that links to a RandomDistributionDataTable. Allows for sub nested DataTables that will be evaluated
 * when selected during execution.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Table : public FDistributionItem
{
	GENERATED_BODY()

	/**
	 * The maximum number of entries expected in the result. The final count of items in the result may be lower
	 * if some of the entries return a null result (no drop).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** The RandomDistributionDataTable to evaluate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionRow"))
	TObjectPtr<UDataTable> DataTable;
};

/**
 * Contains a gameplay tag and value pair.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_TagValue : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Value = 0;
};

/**
 * A DistributionItem that holds an object.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Object : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr<UObject> Object;
};

/**
 * A DistributionItem that holds a class.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Class : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSoftClassPtr<UObject> Class;
};

/**
 * A DataTable struct containing data that will be copied to the execution.
 */
USTRUCT()
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionRow : public FTableRowBase
{
	GENERATED_BODY()

	/** If false, this row cannot be selected. */
	UPROPERTY(EditAnywhere, Category = "Row")
	bool bEnabled = true;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, Category = "Row", meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** If true, this row can only be selected once. */
	UPROPERTY(EditAnywhere, Category = "Row")
	bool bIsUnique = false;
	/** If true, this row will always be in the result at least once. */
	UPROPERTY(EditAnywhere, Category = "Row")
	bool bAlwaysPick = false;
	/** GameplayTags this row has. */
	UPROPERTY(EditAnywhere, Category = "Row")
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. Leave empty to return nothing. */
	UPROPERTY(EditAnywhere, Category = "Row", meta = (ExcludeBaseStruct))
	TInstancedStruct<FDistributionItem> Item;
};

/**
 * A mutable copy of the RandomDistributionRow used in the RandomDistributionExecution.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionData
{
	GENERATED_BODY()

	FRandomDistributionData() {}
	FRandomDistributionData(FName InName, const FRandomDistributionRow& TableRow);

	/** The name of the row from the RandomDistributionDataTable */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName Name = NAME_None;
	/** If false, this row cannot be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bEnabled = true;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** If true, this row can only be selected once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bIsUnique = false;
	/** If true, this row will always be in the result at least once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool bAlwaysPick = false;
	/** GameplayTags this row has. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. Leave empty to return nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (ExcludeBaseStruct))
	TInstancedStruct<FDistributionItem> Item;

private:

	/** The unique GUID generated for this row to determine equality between rows. */
	UPROPERTY()
	FGuid Guid = FGuid();

public:
	friend bool operator==(const FRandomDistributionData& X, const FRandomDistributionData& Y)
	{
		return X.Guid == Y.Guid;
	}
	friend bool operator!=(const FRandomDistributionData& X, const FRandomDistributionData& Y)
	{
		return X.Guid != Y.Guid;
	}
};

/**
 * Struct that is used by the RandomDistributionExecution to generate results.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionExecutionParams
{
	GENERATED_BODY()

	/** The RandomDistributionDataTable to execute. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params", meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionRow"))
	TObjectPtr<UDataTable> DataTable;

	/**
	 * The number of results to return from the DataTable. The actual final result can be higher or lower depending on
	 * if there are 'misses' or sub nested DataTables that can generate additional results.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params", meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** Can contain custom information to pass along to evaluators. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	TObjectPtr<UObject> Context;
};
