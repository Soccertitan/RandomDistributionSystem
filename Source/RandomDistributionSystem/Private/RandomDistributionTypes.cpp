// Copyright Soccertitan 2025


#include "RandomDistributionTypes.h"


FRandomDistributionData::FRandomDistributionData(FName InName, const FRandomDistributionRow& TableRow)
{
	Name = InName;
	Probability = TableRow.Probability;
	bIsUnique = TableRow.bIsUnique;
	bAlwaysPick = TableRow.bAlwaysPick;
	bEnabled = TableRow.bEnabled;
	OwnedTags = TableRow.OwnedTags;
	Item = TableRow.Item;
	Guid = FGuid::NewGuid();
}
