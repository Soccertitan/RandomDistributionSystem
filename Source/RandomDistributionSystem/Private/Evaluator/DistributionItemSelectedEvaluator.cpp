// Copyright Soccertitan


#include "Evaluator/DistributionItemSelectedEvaluator.h"

#include "RandomDistributionExecutionEvaluator.h"

UDistributionItemSelectedEvaluator::UDistributionItemSelectedEvaluator()
{
}

void UDistributionItemSelectedEvaluator::OnItemSelected(const FRandomDistributionExecutionParams& ExecutionParams, TInstancedStruct<FDistributionItem>& Item)
{
	K2_OnItemSelected(ExecutionParams, Item);
}
