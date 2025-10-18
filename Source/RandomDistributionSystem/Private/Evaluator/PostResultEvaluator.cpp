// Copyright Soccertitan 2025


#include "Evaluator/PostResultEvaluator.h"

#include "RandomDistributionExecution.h"

UPostResultEvaluator::UPostResultEvaluator()
{
}

void UPostResultEvaluator::EvaluatePostResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& Result)
{
	K2_EvaluatePostResult(ExecutionParams, Result);
}
