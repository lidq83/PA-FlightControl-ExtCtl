#pragma once

#include <stdint.h>
#ifdef __cplusplus
#include <cstring>
#else
#include <string.h>
#endif

#include <uORB/uORB.h>


#ifndef __cplusplus

#endif


#ifdef __cplusplus
struct survey_information_s {
#else
struct survey_information_s {
#endif
	long long timestamp; // required for logger
	double dLong_D;
	double dLat_D;
	int iSerial_Num;
	int iPhoto_Num;
	float fHight_M;
	float fPitch_D;
	float fRoll_D;
	float fYaw_D;
	float fDelta_H;
	float fDelta_Y;
	float fDelta_Pitch;
	float fDelta_Roll;
	float fDelta_Yaw;
	int iFlightNum;
	char uFlight_Stage;
	char uPrevious_Stage;
	char _padding0[6]; // required for logger

#ifdef __cplusplus

#endif
};

/* register this as object request broker structure */
ORB_DECLARE(survey_information);

