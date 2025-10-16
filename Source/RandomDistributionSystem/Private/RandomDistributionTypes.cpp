// Copyright Soccertitan


#include "RandomDistributionTypes.h"


FRandomDistributionRow::FRandomDistributionRow()
{
	Guid = FGuid::NewGuid();
}

FRandomDistributionRow::FRandomDistributionRow(FName InName, const FRandomDistributionDataTable& TableRow)
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
