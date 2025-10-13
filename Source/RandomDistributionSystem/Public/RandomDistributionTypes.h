// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"

#include "RandomDistributionTypes.generated.h"

/**
 * The base struct that defines an item. Must be subclassed in C++ to allow new types of data to be
 * defined in the RandomDistributionDataTable.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem
{
	GENERATED_BODY()
};

/**
 * A special struct that links to a RandomDistributionDataTable. Allows for sub nested DataTables that will be executed
 * when selected in the ExecutionEvaluator.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Table : public FDistributionItem
{
	GENERATED_BODY()

	/**
	 * The maximum number of entries expected in the result. The final count of items in the result may be lower
	 * if some of the entries return a null result (no drop).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** The RandomDistributionDataTable to evaluate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionDataTable"))
	TSoftObjectPtr<UDataTable> DataTable;
};

/**
 * Contains a gameplay tag and value pair.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_TagValue : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
};

/**
 * A DistributionItem holding a single object.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Object : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UObject> Object;
};

/**
 * A DistributionItem holding a soft reference to a subclass.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FDistributionItem_Class : public FDistributionItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UObject> Class;
};

/**
 * A DataTable struct containing data used for determining results.
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
	/** If true, this row can only be selected once in the ExecutionEvaluator. */
	UPROPERTY(EditAnywhere)
	bool bIsUnique = false;
	/** If true, this row will always be in the result. */
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
 * A mutable struct used in the RandomDistributionExecutionEvaluator. Contains a copy of a row from the RandomDistributionDataTable.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionRow
{
	GENERATED_BODY()

	FRandomDistributionRow(){}
	FRandomDistributionRow(FName InName, const FRandomDistributionDataTable& TableRow);

	/** If false, this row cannot be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnabled = true;
	/** The likelihood this entry will be selected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	float Probability = 0.f;
	/** If true, this row can only be selected once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnique = false;
	/** If true, this row will always be in the result at least once. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAlwaysPick = false;
	/** GameplayTags this row has. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer OwnedTags;
	/** The actual item you want to return. Leave empty to return nothing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExcludeBaseStruct))
	TInstancedStruct<FDistributionItem> Item;

	FName GetRowName() const {return Name;}
	
private:
	/** The unique name of the row from the RandomDistributionDataTable */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FName Name = NAME_None;

public:
	friend bool operator==(const FRandomDistributionRow& X, const FRandomDistributionRow& Y)
	{
		return X.Name == Y.Name;
	}
	friend bool operator!=(const FRandomDistributionRow& X, const FRandomDistributionRow& Y)
	{
		return X.Name != Y.Name;
	}
};

/**
 * Struct that is used by the ExecutionEvaluator to generate results.
 */
USTRUCT(BlueprintType)
struct RANDOMDISTRIBUTIONSYSTEM_API FRandomDistributionExecutionParams
{
	GENERATED_BODY()

	/** The RandomDistributionDataTable to execute. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RequiredAssetDataTags = "RowStructure=/Script/RandomDistributionSystem.RandomDistributionDataTable"))
	TObjectPtr<UDataTable> DataTable;

	/**
	 * The number of results to return from the DataTable. The actual final result can be higher or lower depending on
	 * if there are 'misses' or sub nested DataTables that can generate additional results.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1, UIMin = 1))
	int32 Count = 1;

	/** Can contain custom information to pass along to evaluators. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UObject> Context;
};
