// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "RandomDistributionExecutionEvaluator.h"
#include "UObject/Object.h"
#include "EvaluatorBase.generated.h"

class URandomDistributionExecutionEvaluator;

/**
 * The parent class for the different types of Evaluators. Contains helper functions.
 */
UCLASS(Abstract, EditInlineNew, DefaultToInstanced, NotBlueprintType, NotBlueprintable)
class RANDOMDISTRIBUTIONSYSTEM_API UEvaluatorBase : public UObject
{
	GENERATED_BODY()

public:
	UEvaluatorBase();

	/** Retrieves the outer of this Evaluator and casts to the passed in ExecutionClass. */
	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType=ExecutionClass), Category = "Random Distribution System|Evaluator", DisplayName = "GetRandomDistributionEvaluator")
	URandomDistributionExecutionEvaluator* K2_GetRandomDistributionEvaluator(const TSubclassOf<URandomDistributionExecutionEvaluator> ExecutionClass) const;

	/** Retrieves the outer of this Evaluator and casts to the passed in type. */
	template<class T>
	T* GetRandomDistributionEvaluator() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, const URandomDistributionExecutionEvaluator>::Value,
			"'T' template parameter to GetRandomDistributionEvaluator must be derived from URandomDistributionExecutionEvaluator");
		return (T*)GetOuter();
	}
};
