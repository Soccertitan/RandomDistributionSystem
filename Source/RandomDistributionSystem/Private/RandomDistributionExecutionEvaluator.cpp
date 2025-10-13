// Copyright Soccertitan


#include "RandomDistributionExecutionEvaluator.h"

#include "RandomDistributionTypes.h"
#include "Engine/AssetManager.h"
#include "Evaluator/DistributionItemSelectedEvaluator.h"
#include "Evaluator/PostResultEvaluator.h"
#include "Evaluator/PreResultEvaluator.h"
#include "Evaluator/RandomizerEvaluator.h"


URandomDistributionExecutionEvaluator::URandomDistributionExecutionEvaluator()
{
	Randomizer = CreateDefaultSubobject<URandomizerEvaluator>("RandomizerEvaluator");
}

bool URandomDistributionExecutionEvaluator::GenerateResults(const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& OutResults)
{
	if (!IsValid(ExecutionParams.DataTable) ||
		!ExecutionParams.DataTable->GetRowStruct()->IsChildOf(FRandomDistributionDataTable::StaticStruct()) ||
		!Randomizer ||
		ExecutionParams.Count <= 0)
	{
		return false;
	}

	OutResults.Empty();
	
	EvaluateTable(ExecutionParams.DataTable, ExecutionParams.Count, ExecutionParams, OutResults);

	if (OutResults.Num() == 0)
	{
		return false;
	}
	
	for (TObjectPtr<UPostResultEvaluator>& Evaluator : PostResultEvaluators)
	{
		if (Evaluator)
		{
			Evaluator->EvaluatePostResult(ExecutionParams, OutResults);
		}
	}
	
	return true;
}

void URandomDistributionExecutionEvaluator::EvaluateTable(const UDataTable* Table, int32 Count, const FRandomDistributionExecutionParams& ExecutionParams,
	TArray<TInstancedStruct<FDistributionItem>>& Results)
{
	//----------------------------------------------------------------------------------------
	// 1. Make a mutable copy of the rows from the DataTable.
	// Then run the PreResultEvaluators to give designers a chance to modify the Row's value
	// before running the randomizer.
	//----------------------------------------------------------------------------------------
	TArray<FRandomDistributionRow> MutableRows;
	for (const auto& It : Table->GetRowMap())
	{
		FRandomDistributionRow MutableRow = FRandomDistributionRow(It.Key, *(FRandomDistributionDataTable*)It.Value);

		for (TObjectPtr<UPreResultEvaluator>& Evaluator : PreResultEvaluators)
		{
			if (Evaluator)
			{
				Evaluator->EvaluateRowPreResult(ExecutionParams, MutableRow);
			}
		}
		MutableRows.Add(MutableRow);
	}
	
	if (MutableRows.Num() == 0)
	{
		return;
	}

	for (TObjectPtr<UPreResultEvaluator>& Evaluator : PreResultEvaluators)
	{
		if (Evaluator)
		{
			Evaluator->EvaluateTablePreResult(ExecutionParams, MutableRows);
		}
	}

	//----------------------------------------------------------------------------------------
	// 2. Add all MutableRows that are AlwaysPicked and Enabled.
	// Also add the other enabled rows to a SelectableRows array. This will get passed to the
	// randomizer for processing.
	//----------------------------------------------------------------------------------------
	TArray<FRandomDistributionRow> SelectableRows;
	for (FRandomDistributionRow& Row : MutableRows)
	{
		if (Row.bAlwaysPick && Row.bEnabled)
		{
			Count--;
			AddItemToResults(Row.Item, ExecutionParams, Results);

			if (!Row.bIsUnique)
			{
				SelectableRows.Add(Row);
			}
		}
		else if (Row.bEnabled)
		{
			SelectableRows.Add(Row);
		}
	}

	//----------------------------------------------------------------------------------------
	// 3. Continue only if there are counts left to process and SelectableRows is greater than 0.
	// Each loop for the CurrentCount the Randomizer will select a row to be added to the results.
	// Then, if the SelectedRow is unique, remove it from the SelectableRows array. This ensures
	// Unique results cannot be selected twice.
	//----------------------------------------------------------------------------------------
	if (Count > 0 && SelectableRows.Num() > 0)
	{
		for (int32 CurrentCount = 0; CurrentCount < Count; CurrentCount++)
		{
			FRandomDistributionRow SelectedRow = Randomizer->SelectRow(ExecutionParams, SelectableRows);

			if (SelectedRow.bIsUnique)
			{
				// Removed based on the FName in the SelectedRow. Which should be unique from a DataTable.
				SelectableRows.Remove(SelectedRow);
			}
			AddItemToResults(SelectedRow.Item, ExecutionParams, Results);
		}
	}
}

void URandomDistributionExecutionEvaluator::AddItemToResults(TInstancedStruct<FDistributionItem> Item, const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& Results)
{
	// Must have a valid Item to be added to the result.
	if (Item.IsValid())
	{
		for (auto& Evaluator : DistributionItemSelectedEvaluators)
		{
			if (Evaluator)
			{
				Evaluator->OnItemSelected(ExecutionParams, Item);
			}
		}
		
		if (const FDistributionItem_Table* Table = Item.GetPtr<FDistributionItem_Table>())
		{
			if (!Table->DataTable.Get())
			{
				UAssetManager::Get().LoadAssetList({Table->DataTable.ToSoftObjectPath()})->WaitUntilComplete();
			}
			if (Table->Count > 0)
			{
				EvaluateTable(Table->DataTable.Get(), Table->Count, ExecutionParams, Results);
			}
		}
		else
		{
			// Only add Non Table items to the Results.
			Results.Add(Item);
		}
	}
}
