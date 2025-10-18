// Copyright Soccertitan 2025


#include "Evaluator/DistributionItemSelectedEvaluator.h"

#include "RandomDistributionExecution.h"

UDistributionItemSelectedEvaluator::UDistributionItemSelectedEvaluator()
{
}

void UDistributionItemSelectedEvaluator::OnItemSelected(const FRandomDistributionExecutionParams& ExecutionParams, TInstancedStruct<FDistributionItem>& Item)
{
	K2_OnItemSelected(ExecutionParams, Item);
}
