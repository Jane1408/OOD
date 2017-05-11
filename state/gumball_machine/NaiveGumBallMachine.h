#pragma once

#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
		HasQuarterAndSoldOut,	// Жвачка закончилась, но есть монетки
		NoQuarterAndSoldOut,	// Жвачка закончилась, монеток нет
	};

	CGumballMachine(unsigned count);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString()const;

private:
	void Dispense();

	unsigned m_count;	// Количество шариков
	unsigned m_quarterCount;
	State m_state = State::NoQuarterAndSoldOut;
};
}