// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "RandomDistributionTypes.h"
#include "UObject/Object.h"
#include "RandomDistributionExecution.generated.h"

class URandomizerEvaluator;
class UPostResultEvaluator;
class UDistributionItemSelectedEvaluator;
class UPreResultEvaluator;

/**
 * URandomDistributionExecution
 *
 * An object to easily randomly select items from a RandomDistributionDataTable. There are three different types of
 * evaluators that are used through the GenerateResults process. They are called in order PreResult, Randomizer,
 * and PostResult evaluators.
 *
 * PreResultEvaluator:
 *		- Has two functions,
 *			- OnPreResultRowEvaluation, it is called for each Row in the DataTable. You can adjust any parameter you like.
 *			- OnPreResultTableEvaluation, it is called after each Row has been evaluated. Allowing you to further modify
 *				values or add new rows.
 *
 * RandomizerEvaluator:
 *		- The ExecutionEvaluator requires a valid Randomizer to function. Its primary purpose is to choose a row to return.
 *		- You have mutable access to the SelectableRows array, you can continue to modify properties if desired.
 *
 * PostResultEvaluator:
 *		- Provides a place to modify the Results after evaluation or call other functions.
 *
 * DistributionItemSelectedEvaluator:
 *		- Provides an opportunity to trigger responses whenever an item is selected from the row.
 */

/**
 * A class that can take a RandomDistributionDataTable and returns an array of DistributionItems that were chosen
 * by the RandomizerEvaluator.
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class RANDOMDISTRIBUTIONSYSTEM_API URandomDistributionExecution : public UObject
{
	GENERATED_BODY()

public:
	URandomDistributionExecution();
	
	/**
	 * Generates an array of Results from a RandomDistributionDataTable.
	 * @param ExecutionParams Contains the parameters to evaluate a RandomDistributionDataTable.
	 * @param OutResults All the rows that were selected by the evaluator.
	 * @return True, if at least one result was returned.
	 */
	UFUNCTION(BlueprintCallable, Category = "Random Distribution System")
	bool GenerateResults(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& OutResults);

protected:

	/** The randomizer to use when selecting a row. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, NoClear, Category = "Evaluator")
	TObjectPtr<URandomizerEvaluator> Randomizer;
	
	/** Called on each row in the DataTable and the DataTable itself prior to adding the rows to the array of SelectableRows. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Evaluator")
	TArray<TObjectPtr<UPreResultEvaluator>> PreResultEvaluators;

	/** Called when a row is selected from the DataTable. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Evaluator")
	TArray<TObjectPtr<UDistributionItemSelectedEvaluator>> DistributionItemSelectedEvaluators;

	/** Called at the end of GenerateResults. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Evaluator")
	TArray<TObjectPtr<UPostResultEvaluator>> PostResultEvaluators;

private:

	/**
	 * Runs through the process of adding Items to the Results. Calling OnRowSelected when a row is added to the Results.
	 * 1. Makes a mutable copy of the RandomDistributionDataTable.
	 * 2. Runs the PreResultEvaluators on each Row then the RandomDistributionDataTable itself.
	 *		The first opportunity to modify the Row's values before selection occurs.
	 * 3. Add all Rows where AlwaysPick and Enabled is true to the Results.
	 * 4. Invokes the RandomizerEvaluator equal to the Count number - the number of Results added in Step 3.
	 * 5. AddItemToResult
	 * @param Table The RandomDistributionRow DataTable.
	 * @param Count The number of attempts to try and select an item from the row.
	 * @param ExecutionParams Context of the Execution.
	 * @param Results All the results that have been selected.
	 */
	void EvaluateTable(const UDataTable* Table, int32 Count, const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& Results);

	/**
	 * Adds the Item to the Results. If a DistributionItem_Table is the item from the passed in row. It will trigger EvaluateTable.
	 * @param Item The item to add to Result.
	 * @param ExecutionParams Context of the Execution.
	 * @param Results All the results that have been selected.
	 */
	void AddItemToResults(TInstancedStruct<FDistributionItem> Item, const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& Results);
};
