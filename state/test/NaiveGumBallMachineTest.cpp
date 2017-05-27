#include "stdafx.h"
#include <boost/format.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "../gumball_machine/NaiveGumBallMachine.h"

std::string CheckOutput(unsigned ballCount, unsigned quarterCount, std::string state)
{
	auto test = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Quarters count: %3%
Machine is %4%
)");
	return (test % ballCount % (ballCount != 1 ? "s" : "") % quarterCount % state).str();
}

struct empty_naive_machine_without_quarters
{
	boost::test_tools::output_test_stream out;
	naive::CGumballMachine machine = naive::CGumballMachine(out, 0);
};

BOOST_FIXTURE_TEST_SUITE(naive_gumball_machine_is_empty_without_quarters, empty_naive_machine_without_quarters);
	BOOST_AUTO_TEST_CASE(naive_machine_has_no_balls_and_no_quarters_and_sold_out_state)
	{
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 0, "sold out"));
	}
	BOOST_AUTO_TEST_CASE(naive_machine_can_be_refilled_and_get_waiting_for_quarter_state)
	{
		machine.Refill(10);
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(10, 0, "waiting for quarter"));
	}
	BOOST_AUTO_TEST_CASE(naive_machine_can_not_eject_quarter)
	{
		machine.EjectQuarter();
	BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 0, "sold out"));
	}
	BOOST_AUTO_TEST_CASE(naive_machine_can_not_insert_quarter)
	{
		machine.InsertQuarter();
		BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 0, "sold out"));
	}

	struct not_empty_naive_machine_without_quarters : empty_naive_machine_without_quarters
	{
		not_empty_naive_machine_without_quarters()
		{
			machine.Refill(5);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(naive_gumball_machine_is_not_empty_without_quarters, not_empty_naive_machine_without_quarters);
		BOOST_AUTO_TEST_CASE(naive_machine_has_5_balls_and_no_quarters_and_waiting_for_quarter_state)
		{
			BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 0, "waiting for quarter"));
		}

		BOOST_AUTO_TEST_CASE(naive_machine_can_not_eject_quarter)
		{
			machine.EjectQuarter();
			BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 0, "waiting for quarter"));
		}

		BOOST_AUTO_TEST_CASE(naive_machine_can_be_refilled)
		{
			machine.Refill(10);
			BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(10, 0, "waiting for quarter"));
		}

		struct not_empty_machine_with_quarters : not_empty_naive_machine_without_quarters
		{
			not_empty_machine_with_quarters()
			{
				machine.InsertQuarter();
				machine.InsertQuarter();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(naive_gumball_machine_is_not_empty_with_quarters, not_empty_machine_with_quarters);
			BOOST_AUTO_TEST_CASE(naive_machine_has_waiting_for_turn_of_crank_state)
			{
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 2, "waiting for turn of crank"));
			}
			BOOST_AUTO_TEST_CASE(naive_machine_can_get_gumball_and_get_waiting_for_turn_of_crank_state)
			{
				machine.TurnCrank();
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(4, 1, "waiting for turn of crank"));
			}
			BOOST_AUTO_TEST_CASE(naive_machine_can_eject_all_quarters_and_get_waiting_for_quarter_state)
			{
				machine.EjectQuarter();
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 0, "waiting for quarter"));
			}
		BOOST_AUTO_TEST_SUITE_END();

		struct not_empty_machine_with_max_limit_quarters : not_empty_naive_machine_without_quarters
		{
			not_empty_machine_with_max_limit_quarters()
			{
				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
				machine.InsertQuarter();
			}
		};

		BOOST_FIXTURE_TEST_SUITE(naive_gumball_machine_is_not_empty_with_max_limit_quarters, not_empty_machine_with_max_limit_quarters);
			BOOST_AUTO_TEST_CASE(naive_machine_has_waiting_for_turn_of_crank_state)
			{
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 5, "waiting for turn of crank"));
			}
			BOOST_AUTO_TEST_CASE(naive_machine_can_not_insert_quarter)
			{
				machine.InsertQuarter();
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 5, "waiting for turn of crank"));
			}
			BOOST_AUTO_TEST_CASE(naive_machine_can_eject_all_quarters_and_get_waiting_for_quarter_state)
			{
				machine.EjectQuarter();
				BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(5, 0, "waiting for quarter"));
			}

			struct empty_machine_with_max_limit_quarters : not_empty_machine_with_max_limit_quarters
			{
				empty_machine_with_max_limit_quarters()
				{
					machine.Refill(0);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(naive_gumball_machine_was_refilled_to_0_balls_with_max_limit_quarters, empty_machine_with_max_limit_quarters);
				BOOST_AUTO_TEST_CASE(naive_machine_has_sold_out_state)
				{
					BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 5, "sold out"));
				}
				BOOST_AUTO_TEST_CASE(naive_machine_can_eject_all_quarter_from_sold_out_state)
				{
					machine.EjectQuarter();
					BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 0, "sold out"));
				}
				BOOST_AUTO_TEST_CASE(naive_machine_can_not_turn_of_crank)
				{
					machine.TurnCrank();
					BOOST_CHECK_EQUAL(machine.ToString(), CheckOutput(0, 5, "sold out"));
				}

			BOOST_AUTO_TEST_SUITE_END();

		BOOST_AUTO_TEST_SUITE_END();

	BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();