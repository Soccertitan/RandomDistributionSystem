// Copyright Soccertitan 2025

#pragma once

#include "CoreMinimal.h"
#include "EvaluatorBase.h"
#include "UObject/Object.h"
#include "RandomDistributionTypes.h"
#include "DistributionItemSelectedEvaluator.generated.h"


/**
 * These functions are called anytime an Item is selected during Execution.
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class RANDOMDISTRIBUTIONSYSTEM_API UDistributionItemSelectedEvaluator : public UEvaluatorBase
{
	GENERATED_BODY()

public:
	UDistributionItemSelectedEvaluator();

	/**
	 * Allows you to react when a Row is selected and about to be added to Results.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Item The selected item.
	 */
	virtual void OnItemSelected(const FRandomDistributionExecutionParams& ExecutionParams, TInstancedStruct<FDistributionItem>& Item);

protected:
	
	/**
	 * Allows you to react when a Row is selected and about to be added to Results.
	 * @param ExecutionParams The context of the Evaluator.
	 * @param Item The selected item.
	 */
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnItemSelected")
	void K2_OnItemSelected(UPARAM(ref) const FRandomDistributionExecutionParams& ExecutionParams, UPARAM(ref) TInstancedStruct<FDistributionItem>& Item);
};
