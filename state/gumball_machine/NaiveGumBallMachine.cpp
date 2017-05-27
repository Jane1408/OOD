#include "stdafx.h"
#include <iostream>
#include <boost/format.hpp>
#include "Constants.h"
#include "NaiveGumBallMachine.h"

namespace naive
{

	CGumballMachine::CGumballMachine(std::ostream & out,unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::NoQuarterAndSoldOut)
		, m_quarterCount(0)
		, m_out(out)
	{
	}

	CGumballMachine::CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::NoQuarterAndSoldOut)
		, m_quarterCount(0)
		, m_out(std::cout)
	{
	}

	void CGumballMachine::InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
			m_out << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			m_out << "You inserted a quarter\n";
			++m_quarterCount;
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_quarterCount < QUARTER_LIMIT)
			{
				m_out << "You inserted a quarter\n";
				++m_quarterCount;
			}
			else
				m_out << "You can't insert another quarter\n";
			break;
		case State::Sold:
			m_out << "You inserted a quarter\n";
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
			m_out << "Quarter returned\n";
			m_state = State::NoQuarter;
			m_quarterCount = 0;
			break;
		case State::NoQuarter:
			m_out << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_out << "Sorry you already turned the crank\n";
			break;
		case State::HasQuarterAndSoldOut:
			m_out << "Quarter returned\n";
			m_quarterCount = 0;
			break;
		case State::NoQuarterAndSoldOut:
			m_out << "You can't eject, you haven't inserted a quarter yet\n";
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
			m_out << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			m_out << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			m_out << "You turned...\n";
			--m_quarterCount;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			m_out << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void CGumballMachine::Refill(unsigned numBalls)
	{
		using namespace std;
		numBalls = numBalls >= 0 ? numBalls : 0;
		switch (m_state)
		{
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
		case State::NoQuarter:
		case State::HasQuarter:
			m_count = numBalls;
			m_out << "Refill gumballs count " << m_count << "\n";
			break;
		case State::Sold:
			m_out << "You can't refill gumball machine\n";
			break;
		}
		if (m_count > 0)
			m_state = m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter;
		else
			m_state = m_quarterCount > 0 ? State::HasQuarterAndSoldOut : State::NoQuarterAndSoldOut;
		
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
			m_out << "A gumball comes rolling out the slot\n";
			--m_count;
			if (m_count == 0)
			{
				m_out << "Oops, out of gumballs\n";
				m_state = (m_quarterCount == 0) ? State::NoQuarterAndSoldOut : State::HasQuarterAndSoldOut;
			}
			else
			{
				m_state = (m_quarterCount == 0) ? State::NoQuarter : State::HasQuarter;
			}
			break;
		case State::NoQuarter:
			m_out << "You need to pay first\n";
			break;
		case State::NoQuarterAndSoldOut:
		case State::HasQuarterAndSoldOut:
		case State::HasQuarter:
			m_out << "No gumball dispensed\n";
			break;
		}
	}

}