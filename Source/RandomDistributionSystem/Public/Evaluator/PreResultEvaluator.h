// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "PreResultEvaluator.generated.h"

struct FRandomDistributionExecutionParams;
struct FRandomDistributionData;

/**
 * This class can modify the values of the DistributionRows before they are processed in the Execution.
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class RANDOMDISTRIBUTIONSYSTEM_API UPreResultEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:

	UPreResultEvaluator();

	/**
	 * Allows you to modify the values in the Row before it is processed in the Execution.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	virtual void EvaluateRowPreResult(const FRandomDistributionExecutionParams& ExecutionParams, FRandomDistributionData& Row);

	/**
	 * Called after all rows have been evaluated in EvaluateRowPreResult. Allows you to modify the Rows array and
	 * make further modifications before the Execution processes the Rows.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	virtual void EvaluateTablePreResult(const FRandomDistributionExecutionParams& ExecutionParams, TArray<FRandomDistributionData>& Rows);

protected:
	
	/**
	 * Allows you to modify the values in the Row before it is processed in the Execution.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Row The mutable row to update.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluateRowPreResult")
	void K2_EvaluateRowPreResult(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) FRandomDistributionData& Row);

	/**
	 * Called after all rows have been evaluated in EvaluateRowPreResult. Allows you to modify the Rows array and
	 * make further modifications before the Execution processes the Rows.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Rows The mutable array of rows.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "EvaluateTablePreResult")
	void K2_EvaluateTablePreResult(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) TArray<FRandomDistributionData>& Rows);
};
