// Copyright Soccertitan


#include "Evaluator/PostResultEvaluator.h"

#include "RandomDistributionExecutionEvaluator.h"

UPostResultEvaluator::UPostResultEvaluator()
{
}

void UPostResultEvaluator::EvaluatePostResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<TInstancedStruct<FDistributionItem>>& Result)
{
	K2_EvaluatePostResult(ExecutionParams, Result);
}
