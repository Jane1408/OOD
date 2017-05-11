#include <iostream>
#include <boost/format.hpp>
#include "Constants.h"
#include "NaiveGumBallMachine.h"

namespace naive
{

	CGumballMachine::CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::NoQuarterAndSoldOut)
		, m_quarterCount(0)
	{
	}

	void CGumballMachine::InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			++m_quarterCount;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarterCount < QUARTER_LIMIT)
			{
				cout << "You inserted a quarter\n";
				++m_quarterCount;
			}
			else
				cout << "You can't insert another quarter\n";
			break;
		case State::Sold:
			cout << "You inserted a quarter\n";
			++m_quarterCount;
			m_state = State::HasQuarter;
			break;
		}
	}

	void CGumballMachine::EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			cout << "Quarter returned\n";
			m_state = State::NoQuarter;
			m_quarterCount = 0;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank\n";
			break;
		case State::HasQuarterAndSoldOut:
			cout << "Quarter returned\n";
			m_quarterCount = 0;
			break;
		case State::NoQuarterAndSoldOut:
			cout << "You can't eject, you haven't inserted a quarter yet\n";
			break;
		}
	}

	void CGumballMachine::TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			--m_quarterCount;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void CGumballMachine::Refill(unsigned numBalls)
	{
		m_count = numBalls;
		if (numBalls > 0)
			m_state = m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter;
		else
			m_state = m_quarterCount > 0 ? State::HasQuarterAndSoldOut : State::NoQuarterAndSoldOut;
		std::cout << "Refill gumballs count " << m_count << "\n";
	}

	std::string CGumballMachine::ToString() const
	{
		std::string state =
			(m_state == State::HasQuarterAndSoldOut || m_state == State::NoQuarterAndSoldOut) ? "sold out" :
			(m_state == State::NoQuarter) ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			: "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Quarters count: %3%
Machine is %4%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % state).str();
	}

	void CGumballMachine::Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = (m_quarterCount == 0) ? State::NoQuarterAndSoldOut : State::HasQuarterAndSoldOut;
			}
			else
			{
				m_state = (m_quarterCount == 0) ? State::NoQuarter : State::HasQuarter;
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

}