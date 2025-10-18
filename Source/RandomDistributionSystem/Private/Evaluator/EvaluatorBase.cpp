// Copyright Soccertitan 2025


#include "Evaluator/EvaluatorBase.h"

#include "RandomDistributionExecution.h"

UEvaluatorBase::UEvaluatorBase()
{
}

URandomDistributionExecution* UEvaluatorBase::K2_GetRandomDistributionExecution() const
{
	return Cast<URandomDistributionExecution>(GetOuter());
}
