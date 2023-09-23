#ifndef SIM_A76XX_H
#define SIM_A76XX_H
#include <Arduino.h>

/*Khai bao thong tin MQTT*/
#define HOST "Mqtt.mysignage.vn"
#define PORT "1883"
#define TOPIC_PUB "ngocanh"
#define MSG_ERROR "ngocanh"
#define TOPIC_SUB "ngocanh"

void Sim_A76xx_config();
void Sim_A76xx_pub(String topic, String message);
void Sim_A76xx_sub(String topic);
bool Sim_A76xx_flag();
String Sim_A76xx_message();

#endif