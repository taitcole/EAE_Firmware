#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#define V_TEMP_NEGATIVE_20 4.771
#define V_TEMP_NEGATIVE_10 4.642
#define V_TEMP_0 4.438
#define V_TEMP_10 4.141
#define V_TEMP_20 3.751
#define V_TEMP_30 3.325
#define V_TEMP_40 2.838
#define V_TEMP_60 1.915
#define V_TEMP_80 1.212
#define V_TEMP_100 0.749
#define V_TEMP_120 0.465
#define V_TEMP_140 0.295

int convertVoltageToTemp(float voltage);

#endif