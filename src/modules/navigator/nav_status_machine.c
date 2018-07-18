/*
 * status_machine.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "nav_status_machine.h"

static nav_state_block_s _nav_init;
static nav_state_block_s _nav_takeoff;
static nav_state_block_s _nav_mission;
static nav_state_block_s _nav_loiter;
static nav_state_block_s _nav_rtl;
static nav_state_block_s _nav_failoff;
static nav_state_block_s _nav_failsafe;

static int param_mis_fin_do = 0;

void nav_st_machine_init(void)
{
	param_get("NAV_MIS_FIN_DO", &param_mis_fin_do);

	_nav_init.p_on_init = nav_init_on_init;
	_nav_init.p_on_desc = nav_init_on_desc;
	_nav_init.p_on_inactive = nav_init_on_inactive;
	_nav_init.p_on_activation = nav_init_on_activation;
	_nav_init.p_on_active = nav_init_on_active;
	_nav_init.p_is_finished = nav_init_is_finished;

	_nav_takeoff.p_on_init = nav_takeoff_on_init;
	_nav_takeoff.p_on_desc = nav_takeoff_on_desc;
	_nav_takeoff.p_on_inactive = nav_takeoff_on_inactive;
	_nav_takeoff.p_on_activation = nav_takeoff_on_activation;
	_nav_takeoff.p_on_active = nav_takeoff_on_active;
	_nav_takeoff.p_is_finished = nav_takeoff_is_finished;

	_nav_mission.p_on_init = nav_mission_on_init;
	_nav_mission.p_on_desc = nav_mission_on_desc;
	_nav_mission.p_on_inactive = nav_mission_on_inactive;
	_nav_mission.p_on_activation = nav_mission_on_activation;
	_nav_mission.p_on_active = nav_mission_on_active;
	_nav_mission.p_is_finished = nav_mission_is_finished;

	_nav_loiter.p_on_init = nav_loiter_on_init;
	_nav_loiter.p_on_desc = nav_loiter_on_desc;
	_nav_loiter.p_on_inactive = nav_loiter_on_inactive;
	_nav_loiter.p_on_activation = nav_loiter_on_activation;
	_nav_loiter.p_on_active = nav_loiter_on_active;
	_nav_loiter.p_is_finished = nav_loiter_is_finished;

	_nav_rtl.p_on_init = nav_rtl_on_init;
	_nav_rtl.p_on_desc = nav_rtl_on_desc;
	_nav_rtl.p_on_inactive = nav_rtl_on_inactive;
	_nav_rtl.p_on_activation = nav_rtl_on_activation;
	_nav_rtl.p_on_active = nav_rtl_on_active;
	_nav_rtl.p_is_finished = nav_rtl_is_finished;

	_nav_failoff.p_on_init = nav_failoff_on_init;
	_nav_failoff.p_on_desc = nav_failoff_on_desc;
	_nav_failoff.p_on_inactive = nav_failoff_on_inactive;
	_nav_failoff.p_on_activation = nav_failoff_on_activation;
	_nav_failoff.p_on_active = nav_failoff_on_active;
	_nav_failoff.p_is_finished = nav_failoff_is_finished;

	_nav_failsafe.p_on_init = nav_failsafe_on_init;
	_nav_failsafe.p_on_desc = nav_failsafe_on_desc;
	_nav_failsafe.p_on_inactive = nav_failsafe_on_inactive;
	_nav_failsafe.p_on_activation = nav_failsafe_on_activation;
	_nav_failsafe.p_on_active = nav_failsafe_on_active;
	_nav_failsafe.p_is_finished = nav_failsafe_is_finished;
}

void nav_st_machine_run(void)
{
	nav_state_block_s *nav_block = &_nav_init;
	main_state_s *main_state = NULL;
	nav_state_s *nav_state = NULL;
	uint8_t nav_state_last = NAV_STATE_INIT;

	_nav_init.p_on_init();
	_nav_takeoff.p_on_init();
	_nav_mission.p_on_init();
	_nav_loiter.p_on_init();
	_nav_rtl.p_on_init();
	_nav_failoff.p_on_init();
	_nav_failsafe.p_on_init();

	while (1)
	{
		usleep(100 * 1000);

		main_state = navigator_get_main_state();

		nav_state = navigator_get_nav_state();

		if (main_state == NULL)
		{
			continue;
		}

		if (nav_state == NULL)
		{
			continue;
		}

		if (nav_state->state != nav_state_last)
		{
			nav_block->p_on_inactive();
		}

		switch (nav_state->state)
		{
			case NAV_STATE_INIT:
				nav_block = &_nav_init;
				break;

			case NAV_STATE_TAKEOFF:
				nav_block = &_nav_takeoff;
				break;

			case NAV_STATE_MISSION:
				nav_block = &_nav_mission;
				break;

			case NAV_STATE_LOITER:
				nav_block = &_nav_loiter;
				break;

			case NAV_STATE_RTL:
				nav_block = &_nav_rtl;
				break;

			case NAV_STATE_FAILOFF:
				nav_block = &_nav_failoff;
				break;

			default:
				nav_block = &_nav_failsafe;
				break;
		}

		if (nav_state->state != nav_state_last)
		{
			nav_state_last = nav_state->state;

			nav_block->p_on_activation();
		}
		else
		{
			nav_block->p_on_active();
		}

		if (nav_state->state == NAV_STATE_MISSION && nav_block->p_is_finished())
		{
			if (param_mis_fin_do == 1)
			{
				nav_state->state = NAV_STATE_LOITER;
			}
			else if (param_mis_fin_do == 2)
			{
				nav_state->state = NAV_STATE_RTL;
			}
		}
	}

	_nav_init.p_on_desc();
	_nav_takeoff.p_on_desc();
	_nav_mission.p_on_desc();
	_nav_loiter.p_on_desc();
	_nav_rtl.p_on_desc();
	_nav_failoff.p_on_desc();
	_nav_failsafe.p_on_desc();

}
