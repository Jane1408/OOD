#pragma once

#include "IBeverage.h"
#include <map>
#include <string>

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

enum class TypeOfCoffee
{
	Standart,
	Double,
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(TypeOfCoffee type)
		: m_typeOfCoffee(type)
		, CCoffee(m_typeOfCoffee == TypeOfCoffee::Standart ? "StandartCapuccino" : "DoubleCapuccino")

	{}

	double GetCost() const override 
	{
		return m_typeOfCoffee == TypeOfCoffee::Standart ? 80 : 120;
	}
private:
	TypeOfCoffee m_typeOfCoffee;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(TypeOfCoffee typeOfCoffee)
		: m_typeOfCoffee(typeOfCoffee)
		, CCoffee(m_typeOfCoffee == TypeOfCoffee::Standart ? "StandartLatte" : "DoubleLatte")
	{}

	double GetCost() const override 
	{
		return m_typeOfCoffee == TypeOfCoffee::Standart ? 90 : 130;
	}
private:
	TypeOfCoffee m_typeOfCoffee;
};

enum class SortOfTea
{
	Ceylon,
	Carcade,
	Green,
	White,
};

std::map <SortOfTea, std::string> TeaMap = {
	{ SortOfTea::Ceylon, "Ceylon" },
	{ SortOfTea::Carcade, "Carcade" },
	{ SortOfTea::Green, "Green" },
	{ SortOfTea::White, "White" },
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(SortOfTea sort)
		:CBeverage(TeaMap.find(sort)->second + "Tea")
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

enum class VolumeOfMilkshake
{
	Big,
	Middle,
	Small,
};

std::map <VolumeOfMilkshake, std::string> MilkshakeMap = {
	{ VolumeOfMilkshake::Big, "Big"},
	{ VolumeOfMilkshake::Middle, "Middle" },
	{ VolumeOfMilkshake::Small, "Small" },
};

std::map <VolumeOfMilkshake, double> MilkshakeCostMap = {
	{ VolumeOfMilkshake::Big, 80 },
	{ VolumeOfMilkshake::Middle, 60 },
	{ VolumeOfMilkshake::Small, 50 },
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(VolumeOfMilkshake volume)
		:CBeverage(MilkshakeMap.find(volume)->second + "Milkshake")
		, m_volume(volume)
	{}

	double GetCost() const override 
	{ 
		return MilkshakeCostMap.find(m_volume)->second;
	}
private:
	VolumeOfMilkshake m_volume;
};
