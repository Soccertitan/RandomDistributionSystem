// Copyright Soccertitan


#include "Evaluator/EvaluatorBase.h"

UEvaluatorBase::UEvaluatorBase()
{
}

URandomDistributionExecutionEvaluator* UEvaluatorBase::K2_GetRandomDistributionEvaluator(
	const TSubclassOf<URandomDistributionExecutionEvaluator> ExecutionClass) const
{
	if (!ExecutionClass)
	{
		return nullptr;
	}
	return Cast<URandomDistributionExecutionEvaluator>(GetOuter());
}
