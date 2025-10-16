// Copyright Soccertitan


#include "Evaluator/EvaluatorBase.h"

UEvaluatorBase::UEvaluatorBase()
{
}

URandomDistributionExecution* UEvaluatorBase::K2_GetRandomDistributionExecution(
	const TSubclassOf<URandomDistributionExecution> ExecutionClass) const
{
	if (!ExecutionClass)
	{
		return nullptr;
	}
	return Cast<URandomDistributionExecution>(GetOuter());
}
