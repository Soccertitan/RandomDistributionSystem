// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item", meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** The RandomDistributionDataTable to evaluate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item", meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionDataTable"))
	TObjectPtr<UDataTable> DataTable;
};

/**
 * Contains a gameplay tag and value pair.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_TagValue : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item")
	int32 Value = 0;
};

/**
 * A DistributionItem that holds an object.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Object : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item")
	TSoftObjectPtr<UObject> Object;
};

/**
 * A DistributionItem that holds a class.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Class : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Item")
	TSoftClassPtr<UObject> Class;
};

/**
 * A DataTable struct containing data that will be copied to the execution.
 */
USTRUCT()
struct FRandomDistributionDataTable : public FTableRowBase
{
	GENERATED_BODY()

	/** If false, this row cannot be selected. */
	UPROPERTY(EditAnywhere)
	bool bEnabled = true;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** If true, this row can only be selected once. */
	UPROPERTY(EditAnywhere)
	bool bIsUnique = false;
	/** If true, this row will always be in the result at least once. */
	UPROPERTY(EditAnywhere)
	bool bAlwaysPick = false;
	/** GameplayTags this row has. */
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. Leave empty to return nothing. */
	UPROPERTY(EditAnywhere, meta = (ExcludeBaseStruct))
	TInstancedStruct<FDistributionItem> Item;
};

/**
 * A mutable struct used in the RandomDistributionExecution.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionRow
{
	GENERATED_BODY()

	FRandomDistributionRow();
	FRandomDistributionRow(FName InName, const FRandomDistributionDataTable& TableRow);

	/** If false, this row cannot be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row")
	bool bEnabled = true;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row", meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** If true, this row can only be selected once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row")
	bool bIsUnique = false;
	/** If true, this row will always be in the result at least once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row")
	bool bAlwaysPick = false;
	/** GameplayTags this row has. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row")
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. Leave empty to return nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Row", meta = (ExcludeBaseStruct))
	TInstancedStruct<FDistributionItem> Item;

	FName GetRowName() const {return Name;}
	
private:
	/** The unique name of the row from the RandomDistributionDataTable */
	UPROPERTY(BlueprintReadOnly, Category = "Random Distribution System|Row", meta = (AllowPrivateAccess = true))
	FName Name = NAME_None;

	/** The unique GUID generated for this row to determine equality between rows. */
	UPROPERTY()
	FGuid Guid;

public:
	friend bool operator==(const FRandomDistributionRow& X, const FRandomDistributionRow& Y)
	{
		return X.Guid == Y.Guid;
	}
	friend bool operator!=(const FRandomDistributionRow& X, const FRandomDistributionRow& Y)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Execution", meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionDataTable"))
	TObjectPtr<UDataTable> DataTable;

	/**
	 * The number of results to return from the DataTable. The actual final result can be higher or lower depending on
	 * if there are 'misses' or sub nested DataTables that can generate additional results.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Execution", meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** Can contain custom information to pass along to evaluators. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Distribution System|Execution")
	TObjectPtr<UObject> Context;
};
