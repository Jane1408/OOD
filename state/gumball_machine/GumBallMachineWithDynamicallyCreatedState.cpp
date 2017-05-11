#include <iostream>
#include <memory>
#include <boost/format.hpp>
#include "Constants.h"
#include "GumBallMachineWithDynamicallyCreatedState.h"

namespace with_dynamic_state
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
	std::string CNoQuarterState::ToString() const
	{
		return "waiting for quarter";
	}



	CGumballMachine::CGumballMachine(unsigned numBalls)
		: m_count(numBalls)
	{

		if (m_count > 0)
		{
			SetNoQuarterState();
		}
		else
		{
			SetSoldOutState();
		}
	}
	void CGumballMachine::EjectQuarter()
	{
		m_currentState->EjectQuarter();
	}
	void CGumballMachine::InsertQuarter()
	{
		m_currentState->InsertQuarter();
	}
	void CGumballMachine::TurnCrank()
	{
		m_currentState->TurnCrank();
		m_currentState->Dispense();
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
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_quarterCount % m_currentState->ToString()).str();
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
		m_currentState.reset(new CSoldOutState(*this));
	}
	void CGumballMachine::SetNoQuarterState()
	{
		m_quarterCount = 0;
		m_currentState.reset(new CNoQuarterState(*this));
	}
	void CGumballMachine::SetSoldState()
	{
		--m_quarterCount;
		m_currentState.reset(new CSoldState(*this));
	}
	void CGumballMachine::SetHasQuarterState()
	{
		m_currentState.reset(new CHasQuarterState(*this));
	}

	void CGumballMachine::AddQuarter()
	{
		++m_quarterCount;
	}

	void CGumballMachine::Refill(unsigned numBalls)
	{
		m_count = numBalls;
		if (m_count > 0)
		{
			if (m_quarterCount > 0)
				SetHasQuarterState();
			else
				SetNoQuarterState();
		}
		else
			SetSoldState();
		std::cout << "Refill gumballs count " << m_count << "\n";
	}

}
