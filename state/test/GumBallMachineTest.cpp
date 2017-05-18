#include "stdafx.h"
#include <boost/format.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "../gumball_machine/GumBallMachineWithState.h"

std::string CheckOutput(unsigned ballCount, unsigned quarterCount, std::string state)
{
	auto test = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Quarters count: %3%
Machine is %4%
)");
	return (test % ballCount % (ballCount != 1 ? "s" : "") % quarterCount % state).str();
}

struct test_machine_10_balls 
{
	boost::test_tools::output_test_stream out;
	with_state::CGumballMachine machine = with_state::CGumballMachine(out, 10);
	
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_test, test_machine_10_balls);
	BOOST_AUTO_TEST_CASE(machine_has_10_balls_and_no_quarters)
	{		
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(10, 0, "waiting for quarter"));
	}

	struct test_machine_10_balls_1_quarter : test_machine_10_balls
	{
		test_machine_10_balls_1_quarter()
		{
			machine.InsertQuarter();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(gumball_machine_has_10_balls_and_add_1_quarters, test_machine_10_balls_1_quarter);
		BOOST_AUTO_TEST_CASE(add_to_machine_1_quarter)
		{
			machine.InsertQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(10, 2, "waiting for turn of crank"));
		}
		BOOST_AUTO_TEST_CASE(machine_was_refill_5_balls_and_2_quarters_remained)
		{
			machine.Refill(5);
			BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 1, "waiting for turn of crank"));
		}
	BOOST_AUTO_TEST_SUITE_END();

	struct test_machine_1_ball_2_quarters : test_machine_10_balls
	{
		test_machine_1_ball_2_quarters()
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.Refill(1);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(gumball_machine_has_1_ball_and_add_2_quarters, test_machine_1_ball_2_quarters);
	BOOST_AUTO_TEST_CASE(pick_up_the_last_ball_and_2_quarters_remained)
	{
		machine.TurnCrank();
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 1, "sold out"));
	}
	BOOST_AUTO_TEST_SUITE_END();

	struct test_machine_0_balls_1_quarters : test_machine_10_balls
	{
		test_machine_0_balls_1_quarters()
		{
			machine.InsertQuarter();
			machine.Refill(0);			
		}
	};
	BOOST_FIXTURE_TEST_SUITE(gumball_machine_has_no_balls_and_1_quarters, test_machine_0_balls_1_quarters);
	BOOST_AUTO_TEST_CASE(eject_quarter_when_balls_sold_out)
	{
		machine.EjectQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 0, "sold out"));
	}
	BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();