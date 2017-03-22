#include <map>
#include <string>
#include "Beverages.h"

static const std::map <SortOfTea, std::string> TEA_MAP = {
	{ SortOfTea::Ceylon, "Ceylon" },
	{ SortOfTea::Carcade, "Carcade" },
	{ SortOfTea::Green, "Green" },
	{ SortOfTea::White, "White" },
};

static const std::map <VolumeOfMilkshake, std::string> MILKSHAKE_MAP = {
	{ VolumeOfMilkshake::Big, "Big" },
	{ VolumeOfMilkshake::Middle, "Middle" },
	{ VolumeOfMilkshake::Small, "Small" },
};

static const std::map <VolumeOfMilkshake, double> MILKSHAKE_COST_MAP = {
	{ VolumeOfMilkshake::Big, 80 },
	{ VolumeOfMilkshake::Middle, 60 },
	{ VolumeOfMilkshake::Small, 50 },
};

CMilkshake::CMilkshake(VolumeOfMilkshake volume)
	:CBeverage(MILKSHAKE_MAP.at(volume) + "Milkshake")
	, m_volume(volume)
{}

double CMilkshake::GetCost() const
{
	return MILKSHAKE_COST_MAP.at(m_volume);
}

CTea::CTea(SortOfTea sort)
	: CBeverage(TEA_MAP.at(sort) + "Tea")
{}