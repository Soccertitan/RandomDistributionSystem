// Copyright Soccertitan


#include "Evaluator/RandomizerEvaluator.h"

#include "RandomDistributionExecution.h"

URandomizerEvaluator::URandomizerEvaluator()
{
}

FRandomDistributionRow URandomizerEvaluator::SelectRow_Implementation(
	const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionRow>& SelectableRows)
{
	/**
	 * Adds up all the Row's probability values.
	 */
	float TotalProbability = 0.f;
	for (const FRandomDistributionRow& Row : SelectableRows)
	{
		TotalProbability += Row.Probability;
	}

	float HitValue = FMath::FRandRange(0.f, TotalProbability);
	float RunningValue = 0.f;
	for (const FRandomDistributionRow& Row : SelectableRows)
	{
		// Count up until we find the first item that exceeds the HitValue.
		RunningValue += Row.Probability;
		if (HitValue <= RunningValue)
		{
			return Row;
		}
	}

	return FRandomDistributionRow();
}
