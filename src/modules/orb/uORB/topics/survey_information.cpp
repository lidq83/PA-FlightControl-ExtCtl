#include <uORB/topics/survey_information.h>


constexpr char __orb_survey_information_fields[] = "uint64_t timestamp;double dLong_D;double dLat_D;int32_t iSerial_Num;int32_t iPhoto_Num;float fHight_M;float fPitch_D;float fRoll_D;float fYaw_D;float fDelta_H;float fDelta_Y;float fDelta_Pitch;float fDelta_Roll;float fDelta_Yaw;int32_t iFlightNum;uint8_t uFlight_Stage;uint8_t uPrevious_Stage;uint8_t[6] _padding0;";

ORB_DEFINE(survey_information, struct survey_information_s, 74,
    __orb_survey_information_fields);

