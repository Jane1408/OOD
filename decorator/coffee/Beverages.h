#pragma once

#include "IBeverage.h"

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

// Чай
class CTea : public CBeverage
{
public:
	CTea(SortOfTea sort);

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

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(VolumeOfMilkshake volume);

	double GetCost() const override;
private:
	VolumeOfMilkshake m_volume;
};