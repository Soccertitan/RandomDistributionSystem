// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "RandomDistributionTypes.h"
#include "RandomizerEvaluator.generated.h"


/**
 * The algorithm to use when selecting a row from a collection. The basic implementation adds up the probabilities and
 * returns the first Item that exceeds the threshold.
 */
UCLASS(BlueprintType, Blueprintable)
class RANDOMDISTRIBUTIONSYSTEM_API URandomizerEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:
	URandomizerEvaluator();

	/**
	 * Randomly picks a Row from the SelectableRows.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param SelectableRows The rows that can be selected.
	 * @return A copy of the Row that was chosen.
	 */
	UFUNCTION(BlueprintNativeEvent)
	FRandomDistributionData SelectRow(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) TArray<FRandomDistributionData>& SelectableRows);
};
