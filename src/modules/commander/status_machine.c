/*
 * status_machine.c
 *
 *  Created on: Jul 9, 2018
 *      Author: lidq
 */

#include "status_machine.h"

static orb_advert_t _pub_sm_st = NULL;
static orb_advert_t _pub_cmd = NULL;
static orb_advert_t _pub_main_state = NULL;
static orb_advert_t _sub_st = NULL;
static main_state_s _main_state = { 0 };
static ext_sys_status_s _ext_state = { 0 };
static uint8_t _main_state_last = MAIN_STATE_FAILSAFE;
static uint32_t _timedes_autostart = 0xffffffff;

static void st_sw_ext_mode();

static void st_pub_arm(void);

static void st_pub_disarm(void);

static void st_init(void);

static void st_standby(void);

static void st_auto_fly(void);

static void st_failsafe(void);

void st_machine_init(void)
{
	_pub_cmd = orb_advertise(ORB_ID(ext_cmd));
	_pub_main_state = orb_advertise((ORB_ID(main_state)));
	_sub_st = orb_subscribe(ORB_ID(ext_sys_status));

	_main_state.state = MAIN_STATE_INIT;
}

void st_machine_run(void)
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
				st_init();
				break;

			case MAIN_STATE_STANDBY:
				st_standby();
				break;

			case MAIN_STATE_AUTO_FLY:
				st_auto_fly();
				break;

			default:
				st_failsafe();
				break;
		}
		//printf("cmd_st %d\n", _main_state.state);
		if (_main_state.state != _main_state_last)
		{
			orb_publish(ORB_ID(main_state), _pub_main_state, &_main_state);
			_main_state_last = _main_state.state;
		}

		usleep(10 * 1000);
	}
}

void st_sw_ext_mode()
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_DO_SET_MODE;
	cmd.param1 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_ENABLE;
	cmd.param2 = VEHICLE_CMD_DO_SET_MODE_CUSTOM_MAIN_EXTCTL;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void st_pub_arm(void)
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_ARM;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void st_pub_disarm(void)
{
	ext_cmd_s cmd = { 0 };
	cmd.command = VEHICLE_CMD_COMPONENT_ARM_DISARM;
	cmd.param1 = VEHICLE_CMD_COMPONENT_ARM_DISARM_PARAM_DISARM;
	orb_publish(ORB_ID(ext_cmd), _pub_cmd, &cmd);
}

void st_init(void)
{
	if (_ext_state.armed)
	{
		st_pub_disarm();
	}

	if (!_ext_state.homed)
	{
		return;
	}

	if (_ext_state.arming_state == ARMING_STATE_STANDBY)
	{
		_timedes_autostart = 300;
		_main_state.state = MAIN_STATE_STANDBY;
	}
}

void st_standby(void)
{
	if (_ext_state.armed)
	{
		st_pub_disarm();
	}

	if (!_ext_state.homed)
	{
		printf("[cmd machine] not homed.\n");
		return;
	}

	if (_timedes_autostart > 0)
	{
		_timedes_autostart--;

		if (_timedes_autostart % 100 == 0)
		{
			printf("[cmd] AutoStart by %ds.\n", _timedes_autostart / 100);
		}
	}

	if (_timedes_autostart == 0)
	{
		_main_state.state = MAIN_STATE_AUTO_FLY;
	}
}

void st_auto_fly(void)
{
	if (!_ext_state.homed)
	{
		printf("[cmd machine] not homed.\n");
		return;
	}

	printf("st %d\n", _ext_state.arming_state);

	if (!_ext_state.armed)
	{
		st_pub_arm();
	}

	static bool wasland = true;
	if (wasland != _ext_state.landed)
	{
		if (_ext_state.landed)
		{
			st_pub_disarm();
		}
		wasland = _ext_state.landed;
		_main_state.state = MAIN_STATE_STANDBY;
	}
}

void st_failsafe(void)
{
	if (_ext_state.armed)
	{
		st_pub_disarm();
	}
}
