// Copyright Soccertitan


#include "Evaluator/PreResultEvaluator.h"

#include "RandomDistributionExecution.h"

UPreResultEvaluator::UPreResultEvaluator()
{
}

void UPreResultEvaluator::EvaluateRowPreResult(const FRandomDistributionExecutionParams& ExecutionParams, FRandomDistributionRow& Row)
{
	K2_EvaluateRowPreResult(ExecutionParams, Row);
}

void UPreResultEvaluator::EvaluateTablePreResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionRow>& Rows)
{
	K2_EvaluateTablePreResult(ExecutionParams, Rows);
}
