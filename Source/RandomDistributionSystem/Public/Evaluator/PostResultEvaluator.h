// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "PostResultEvaluator.generated.h"

class URandomDistributionExecution;
struct FRandomDistributionExecutionParams;
struct FRandomDistributionRow;

/**
 * Occurs after the Execution has finished and the result set is complete, but before
 * the RandomDistributionExecution exits.
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class RANDOMDISTRIBUTIONSYSTEM_API UPostResultEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:
	UPostResultEvaluator();

	/**
	 * Allows you to make further changes to the Result before the Execution finishes.
	 * @param ExecutionParams The context of the Execution.
	 * @param Result A collection of all the rows that were selected.
	 */
	virtual void EvaluatePostResult(
		const FRandomDistributionExecutionParams& ExecutionParams,
		TArray<TInstancedStruct<FDistributionItem>>& Result
	);

protected:
	
	/**
	 * Allows you to make further changes to the Result before the Execution finishes.
	 * @param ExecutionParams The context of the Execution.
	 * @param Result A collection of all the rows that were selected.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluatePostResult")
	void K2_EvaluatePostResult(
		UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams,
		UPARAM(ref) TArray<TInstancedStruct<FDistributionItem>>& Result
	);
};
