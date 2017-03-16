#include <map>
#include <string>
#include "Beverages.h"

static const std::map <SortOfTea, std::string> TeaMap = {
	{ SortOfTea::Ceylon, "Ceylon" },
	{ SortOfTea::Carcade, "Carcade" },
	{ SortOfTea::Green, "Green" },
	{ SortOfTea::White, "White" },
};

static const std::map <VolumeOfMilkshake, std::string> MilkshakeMap = {
	{ VolumeOfMilkshake::Big, "Big" },
	{ VolumeOfMilkshake::Middle, "Middle" },
	{ VolumeOfMilkshake::Small, "Small" },
};

static const std::map <VolumeOfMilkshake, double> MilkshakeCostMap = {
	{ VolumeOfMilkshake::Big, 80 },
	{ VolumeOfMilkshake::Middle, 60 },
	{ VolumeOfMilkshake::Small, 50 },
};

CMilkshake::CMilkshake(VolumeOfMilkshake volume)
	:CBeverage(MilkshakeMap.find(volume)->second + "Milkshake")
	, m_volume(volume)
{}

double CMilkshake::GetCost() const
{
	return MilkshakeCostMap.find(m_volume)->second;
}

CTea::CTea(SortOfTea sort)
	: CBeverage(TeaMap.find(sort)->second + "Tea")
{}