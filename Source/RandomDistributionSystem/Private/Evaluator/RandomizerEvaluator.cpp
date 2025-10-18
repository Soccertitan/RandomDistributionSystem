// Copyright Soccertitan 2025


#include "Evaluator/RandomizerEvaluator.h"

#include "RandomDistributionExecution.h"

URandomizerEvaluator::URandomizerEvaluator()
{
}

FRandomDistributionData URandomizerEvaluator::SelectRow_Implementation(
	const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionData>& SelectableRows)
{
	/**
	 * Adds up all the Row's probability values.
	 */
	float TotalProbability = 0.f;
	for (const FRandomDistributionData& Row : SelectableRows)
	{
		TotalProbability += Row.Probability;
	}

	float HitValue = FMath::FRandRange(0.f, TotalProbability);
	float RunningValue = 0.f;
	for (const FRandomDistributionData& Row : SelectableRows)
	{
		// Count up until we find the first item that exceeds the HitValue.
		RunningValue += Row.Probability;
		if (HitValue <= RunningValue)
		{
			return Row;
		}
	}

	return FRandomDistributionData();
}
