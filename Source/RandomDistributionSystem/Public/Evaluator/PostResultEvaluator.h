// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "PostResultEvaluator.generated.h"

class URandomDistributionExecutionEvaluator;
struct FRandomDistributionExecutionParams;
struct FRandomDistributionRow;

/**
 * Occurs after the result has been calculated and the result set is complete, but before
 * the RandomDistributionExecutionEvaluator exits.
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class RANDOMDISTRIBUTIONSYSTEM_API UPostResultEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:
	UPostResultEvaluator();

	/**
	 * Allows you to make further changes to the Result before the ExecutionEvaluator finishes.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Result A collection of all the rows that were selected.
	 */
	virtual void EvaluatePostResult(
		const FRandomDistributionExecutionParams& ExecutionParams,
		TArray<TInstancedStruct<FDistributionItem>>& Result
	);

protected:
	
	/**
	 * Allows you to make further changes to the Result before the ExecutionEvaluator finishes.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Result A collection of all the rows that were selected.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluatePostResult")
	void K2_EvaluatePostResult(
		UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams,
		UPARAM(ref) TArray<TInstancedStruct<FDistributionItem>>& Result
	);
};
