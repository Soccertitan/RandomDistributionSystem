// Copyright Soccertitan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EvaluatorBase.generated.h"

class URandomDistributionExecution;

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
	UFUNCTION(BlueprintPure, Category = "Random Distribution System|Evaluator", DisplayName = "GetRandomDistributionExecution")
	URandomDistributionExecution* K2_GetRandomDistributionExecution() const;

	/** Retrieves the outer of this Evaluator and casts to the passed in type. */
	template<class T>
	T* GetRandomDistributionExecution() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, const URandomDistributionExecution>::Value,
			"'T' template parameter to GetRandomDistributionExecution must be derived from URandomDistributionExecution");
		return (T*)GetOuter();
	}
};
