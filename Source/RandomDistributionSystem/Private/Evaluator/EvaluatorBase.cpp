// Copyright Soccertitan


#include "Evaluator/EvaluatorBase.h"

#include "RandomDistributionExecution.h"

UEvaluatorBase::UEvaluatorBase()
{
}

URandomDistributionExecution* UEvaluatorBase::K2_GetRandomDistributionExecution() const
{
	return Cast<URandomDistributionExecution>(GetOuter());
}
