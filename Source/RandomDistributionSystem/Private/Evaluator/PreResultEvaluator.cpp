// Copyright Soccertitan 2025


#include "Evaluator/PreResultEvaluator.h"

#include "RandomDistributionExecution.h"

UPreResultEvaluator::UPreResultEvaluator()
{
}

void UPreResultEvaluator::EvaluateRowPreResult(const FRandomDistributionExecutionParams& ExecutionParams, FRandomDistributionData& Row)
{
	K2_EvaluateRowPreResult(ExecutionParams, Row);
}

void UPreResultEvaluator::EvaluateTablePreResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionData>& Rows)
{
	K2_EvaluateTablePreResult(ExecutionParams, Rows);
}
