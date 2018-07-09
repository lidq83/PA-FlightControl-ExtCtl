/*
 * status_machine.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "cmd_status_machine.h"

static orb_advert_t _pub_sm_st = NULL;
static orb_advert_t _pub_cmd = NULL;
static orb_advert_t _pub_main_state = NULL;
static orb_advert_t _pub_nav_state = NULL;
static orb_advert_t _sub_st = NULL;

static main_state_s _main_state = { 0 };
static nav_state_s _nav_state = { 0 };
static ext_sys_status_s _ext_state = { 0 };

static uint8_t _main_state_last = MAIN_STATE_FAILSAFE;
static uint8_t _nav_state_last = NAV_STATE_FAILSAFE;

static bool _wasland = false;

static void cmd_st_sw_ext_mode();

static void cmd_st_pub_arm(void);

static void cmd_st_pub_disarm(void);

static void cmd_st_init(void);

static void cmd_st_standby(void);

static void cmd_st_auto_fly(void);

static void cmd_st_failsafe(void);

void cmd_st_machine_init(void)
{
	_pub_cmd = orb_advertise(ORB_ID(ext_cmd));
	_pub_main_state = orb_advertise((ORB_ID(main_state)));
	_pub_nav_state = orb_advertise((ORB_ID(nav_state)));
	_sub_st = orb_subscribe(ORB_ID(ext_sys_status));

	_main_state.state = MAIN_STATE_INIT;
	_nav_state.state = NAV_STATE_INIT;
}

void cmd_st_machine_run(void)
{
	while (1)
	{
		bool updated = false;
		orb_check(_sub_st, &updated);
		if (updated)
		{
			orb_copy(ORB_ID(ext_sys_status), _sub_st, &_ext_state);
		}

		switch (_main_state.state)
		{
			case MAIN_STATE_INIT:
				cmd_st_init();
				break;

			case MAIN_STATE_STANDBY:
				cmd_st_standby();
				break;

			case MAIN_STATE_AUTO_FLY:
				cmd_st_auto_fly();
				break;

			default:
				cmd_st_failsafe();
				break;
		}

		if (_main_state.state != _main_state_last)
		{
			orb_publish(ORB_ID(main_state), _pub_main_state, &_main_state);
			_main_state_last = _main_state.state;
		}

		if (_nav_state.state != _nav_state_last)
		{
			orb_publish(ORB_ID(nav_state), _pub_nav_state, &_nav_state);
			_nav_state_last = _nav_state.state;
		}

		usleep(100 * 1000);
	}
}

uint8_t cmd_st_get_main_state(void)
{
	return _main_state.state;
}

void cmd_st_set_main_state(uint8_t main_state)
{
	_main_state.state = main_state;
}

uint8_t cmd_st_get_nav_state(void)
{
	return _nav_state.state;
}

void cmd_st_set_nav_state(uint8_t nav_state)
{
	_nav_state.state = nav_state;
}

void cmd_st_sw_ext_mode()
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_DO_SET_MODE;
	cmd.param1 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE;
	cmd.param2 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void cmd_st_pub_arm(void)
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void cmd_st_pub_disarm(void)
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void cmd_st_init(void)
{
	if (!_ext_state.homed)
	{
		return;
	}

	if (_ext_state.arming_state == ARMING_STATE_STANDBY)
	{
		_main_state.state = MAIN_STATE_STANDBY;
	}
}

void cmd_st_standby(void)
{
	if (!_ext_state.homed)
	{
		printf("[cmd] not homed.\n");
		_main_state.state = MAIN_STATE_INIT;
		return;
	}

	if (_ext_state.armed)
	{
		cmd_st_pub_disarm();
	}

	if (_ext_state.main_state != MAIN_STATE_EXTCTL)
	{
		cmd_st_sw_ext_mode();
		return;
	}
}

void cmd_st_auto_fly(void)
{
	if (!_ext_state.homed)
	{
		printf("[cmd machine] not homed.\n");
		_main_state.state = MAIN_STATE_FAILSAFE;
		return;
	}

	if (!_ext_state.armed)
	{
		cmd_st_pub_arm();
		return;
	}

	if (_wasland != _ext_state.landed)
	{
		if (_ext_state.landed)
		{
			cmd_st_pub_disarm();
		}
		_wasland = _ext_state.landed;
		_main_state.state = MAIN_STATE_STANDBY;
	}
}

void cmd_st_failsafe(void)
{
	if (_ext_state.armed)
	{
		cmd_st_pub_disarm();
	}
}
