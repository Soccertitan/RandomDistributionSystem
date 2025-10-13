// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "RandomDistributionExecutionEvaluator.h"
#include "PreResultEvaluator.generated.h"

struct FRandomDistributionExecutionParams;
struct FRandomDistributionRow;

/**
 * This class has an opportunity to modify a copy of the DistributionDataTable and the DistributionRows before any Items
 * are added to the Result.
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class RANDOMDISTRIBUTIONSYSTEM_API UPreResultEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:

	UPreResultEvaluator();

	/**
	 * Allows you to modify the value of the DistributionRow before it is added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	virtual void EvaluateRowPreResult(const FRandomDistributionExecutionParams& ExecutionParams, FRandomDistributionRow& Row);

	/**
	 * Called after all rows have been evaluated in EvaluateRowPreResult. Allows you to modify the Rows array and
	 * other parameters before any rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	virtual void EvaluateTablePreResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionRow>& Rows);

protected:
	
	/**
	 * Allows you to modify the values of the DistributionRow before any Rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluateRowPreResult")
	void K2_EvaluateRowPreResult(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) FRandomDistributionRow& Row);

	/**
	 * Called after all rows have been evaluated in EvaluateRowPreResult. Allows you to modify the Rows array and
	 * other parameters before any rows are added to the result.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluateTablePreResult")
	void K2_EvaluateTablePreResult(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) TArray<FRandomDistributionRow>& Rows);
};
