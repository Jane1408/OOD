#include <boost/format.hpp>
#include <iostream>
#include "Constants.h"
#include "GumBallMachineWithState.h"

namespace with_state
{

	CSoldState::CSoldState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}
	void CSoldState::InsertQuarter()
	{
		if (m_gumballMachine.GetQuarterCount() < QUARTER_LIMIT)
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		else
			std::cout << "Quarter count more than limit, you can't insert quarter\n";
	}
	void CSoldState::EjectQuarter()
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void CSoldState::TurnCrank()
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void CSoldState::Dispense()
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
				m_gumballMachine.SetHasQuarterState();
			else
				m_gumballMachine.SetNoQuarterState();
		}
	}

	void CSoldState::Refill(unsigned numBalls)
	{
		std::cout << "You can't refill gumball machine\n";
	}

	std::string CSoldState::ToString() const
	{
		return "delivering a gumball";
	}



	CSoldOutState::CSoldOutState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void CSoldOutState::InsertQuarter()
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void CSoldOutState::EjectQuarter()
	{
		if (m_gumballMachine.GetQuarterCount() > 0)
		{
			std::cout << "Quarter returned\n";
			m_gumballMachine.SetNoQuarterState();
		}
		else
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void CSoldOutState::TurnCrank()
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void CSoldOutState::Dispense()
	{
		std::cout << "No gumball dispensed\n";
	}

	void CSoldOutState::Refill(unsigned numBalls)
	{
		numBalls = numBalls >= 0 ? numBalls : 0;
		m_gumballMachine.SetBallCount(numBalls);
		if (numBalls > 0)
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
				m_gumballMachine.SetHasQuarterState();
			else
				m_gumballMachine.SetNoQuarterState();
		}
		else
			m_gumballMachine.SetSoldState();
		std::cout << "Refill gumballs count " << numBalls << "\n";
	}

	std::string CSoldOutState::ToString() const
	{
		return "sold out";
	}



	CHasQuarterState::CHasQuarterState(IGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void CHasQuarterState::InsertQuarter()
	{
		if (m_gumballMachine.GetQuarterCount() < QUARTER_LIMIT)
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		else
			std::cout << "Quarter count more than limit, you can't insert quarter\n";
	}
	void CHasQuarterState::EjectQuarter()
	{
		std::cout << "Quarter returned\n";
		m_gumballMachine.SetNoQuarterState();
	}
	void CHasQuarterState::TurnCrank()
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SetSoldState();
	}
	void CHasQuarterState::Dispense()
	{
		std::cout << "No gumball dispensed\n";
	}

	void CHasQuarterState::Refill(unsigned numBalls)
	{
		numBalls = numBalls >= 0 ? numBalls : 0;
		m_gumballMachine.SetBallCount(numBalls);
		if (numBalls > 0)
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
				m_gumballMachine.SetHasQuarterState();
			else
				m_gumballMachine.SetNoQuarterState();
		}
		else
			m_gumballMachine.SetSoldState();
		std::cout << "Refill gumballs count " << numBalls << "\n";
	}

	std::string CHasQuarterState::ToString() const
	{
		return "waiting for turn of crank";
	}



	CNoQuarterState::CNoQuarterState(IGumballMachine & gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void CNoQuarterState::InsertQuarter()
	{
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.AddQuarter();
		m_gumballMachine.SetHasQuarterState();
	}
	void CNoQuarterState::EjectQuarter()
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void CNoQuarterState::TurnCrank()
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void CNoQuarterState::Dispense()
	{
		std::cout << "You need to pay first\n";
	}

	void CNoQuarterState::Refill(unsigned numBalls)
	{
		numBalls = numBalls >= 0 ? numBalls : 0;
		m_gumballMachine.SetBallCount(numBalls);
		if (numBalls > 0)
		{
			if (m_gumballMachine.GetQuarterCount() > 0)
				m_gumballMachine.SetHasQuarterState();
			else
				m_gumballMachine.SetNoQuarterState();
		}
		else
			m_gumballMachine.SetSoldState();
		std::cout << "Refill gumballs count " << numBalls << "\n";
	}

	std::string CNoQuarterState::ToString() const
	{
		return "waiting for quarter";
	}


	CGumballMachine::CGumballMachine(unsigned numBalls)
		: m_soldState(*this)
		, m_soldOutState(*this)
		, m_noQuarterState(*this)
		, m_hasQuarterState(*this)
		, m_state(&m_soldOutState)
		, m_count(numBalls)
	{
		if (m_count > 0)
		{
			m_state = &m_noQuarterState;
		}
	}
	void CGumballMachine::EjectQuarter()
	{
		m_state->EjectQuarter();
	}
	void CGumballMachine::InsertQuarter()
	{
		m_state->InsertQuarter();
	}
	void CGumballMachine::TurnCrank()
	{
		m_state->TurnCrank();
		m_state->Dispense();
	}

	void CGumballMachine::Refill(unsigned numBalls)
	{
		m_state->Refill(numBalls);
	}

	std::string CGumballMachine::ToString()const
	{
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters count: %3%
Machine is %4%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % m_state->ToString()).str();
	}

	unsigned CGumballMachine::GetBallCount() const
	{
		return m_count;
	}
	unsigned CGumballMachine::GetQuarterCount() const
	{
		return m_quarterCount;
	}
	void CGumballMachine::ReleaseBall()
	{
		if (m_count != 0)
		{
			std::cout << "A gumball comes rolling out the slot...\n";
			--m_count;
		}
	}
	void CGumballMachine::SetSoldOutState()
	{
		m_state = &m_soldOutState;
	}
	void CGumballMachine::SetNoQuarterState()
	{
		m_quarterCount = 0;
		m_state = &m_noQuarterState;
	}
	void CGumballMachine::SetSoldState()
	{
		--m_quarterCount;
		m_state = &m_soldState;
	}
	void CGumballMachine::SetHasQuarterState()
	{
		m_state = &m_hasQuarterState;
	}

	void CGumballMachine::AddQuarter()
	{
		++m_quarterCount;
	}

	void CGumballMachine::SetBallCount(unsigned numBalls)
	{
		m_count = numBalls;
	}

	
}
