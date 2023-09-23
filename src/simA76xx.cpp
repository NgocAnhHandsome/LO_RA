#include "simA76xx.h"
#include <HardwareSerial.h>
// Sử dụng UART2, GPIO 17 là RX, GPIO 16 là TX
void waitForResponse(const char *expectedResponse, unsigned int timeout);
HardwareSerial SIM7600Serial(2);
void Clear_SIM7600Seria_buff();

void Sim_A76xx_config()
{
    Serial.begin(115200);
    SIM7600Serial.begin(115200, SERIAL_8N1, 17, 16); // Baud rate và GPIO cho UART2

    Serial.println("RESET");
    SIM7600Serial.println("AT+CRESET");
    waitForResponse("+CGEV", 10000);

    Serial.println("1");
    SIM7600Serial.println("AT");
    waitForResponse("OK", 1000);

    Serial.println("2");
    SIM7600Serial.println("AT+CMQTTSTART");
    waitForResponse("OK", 1000);

    Serial.println("3");
    SIM7600Serial.println("AT+CMQTTACCQ=0,\"a12mmmm\"");
    waitForResponse("OK", 1000);

    Serial.println("4");
    SIM7600Serial.println("AT+CMQTTWILLTOPIC=0," + String(strlen(TOPIC_PUB)));
    waitForResponse(">", 1000);
    SIM7600Serial.print(TOPIC_PUB);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);

    Serial.println("5");
    SIM7600Serial.println("AT+CMQTTWILLMSG=0," + String(strlen(MSG_ERROR)) + ",1");
    waitForResponse(">", 1000);
    SIM7600Serial.print(MSG_ERROR);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);

    Serial.println("6");
    SIM7600Serial.println("AT+CMQTTCONNECT=0,\"tcp://" + String(HOST) + ":" + String(PORT) + "\",20,1");
    waitForResponse("OK", 1000);
    Sim_A76xx_pub("ngocanh", "anh_chao_em");
}
void Sim_A76xx_pub(String topic, String message)
{
    SIM7600Serial.println("AT+CMQTTTOPIC=0," + String(topic.length()));
    waitForResponse(">", 1000);
    SIM7600Serial.print(topic);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);

    SIM7600Serial.println("AT+CMQTTPAYLOAD=0," + String(message.length()));
    waitForResponse(">", 1000);
    SIM7600Serial.print(message);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);    

    SIM7600Serial.println("AT+CMQTTPUB=0,1,60");
    waitForResponse("OK", 1000);    

}
void Sim_A76xx_sub(String topic)
{
    SIM7600Serial.println("AT+CMQTTSUBTOPIC=0," + String(topic.length()) + ",1");
    waitForResponse(">", 1000);
    SIM7600Serial.print(topic);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);    

    SIM7600Serial.println("AT+CMQTTSUB=0," + String(topic.length()) + ",1");
    waitForResponse(">", 1000);
    SIM7600Serial.print(topic);
    SIM7600Serial.write(26);
    waitForResponse("OK", 1000);  
}
bool Sim_A76xx_flag()
{
    return 1;
}
String Sim_A76xx_message()
{
    return "a";
}

void waitForResponse(const char *expectedResponse, unsigned int timeout)
{
    unsigned long startTime = millis();
    String response = "";
    while (millis() - startTime < timeout)
    {
        char tmp = SIM7600Serial.read();
        response += tmp;
        if (strstr(response.c_str(), expectedResponse) != NULL)
        {
            Clear_SIM7600Seria_buff();
//            Serial.println(response);
            return;
        }

        if (tmp == '\n')
        {
            response = "";
        }
    }
    // Timeout
    Serial.println("Timeout waiting for response: " + String(expectedResponse));
    Clear_SIM7600Seria_buff();
}

void Clear_SIM7600Seria_buff()
{
    while (SIM7600Serial.available() > 0)
    {
        char tmp = SIM7600Serial.read();
    }
}

void processIncomingData() {
  while (SIM7600Serial.available()) {
    char receivedChar = SIM7600Serial.read();

    // Xử lý dữ liệu nhận được ở đây
    // Ví dụ: in dữ liệu ra Serial Monitor
    Serial.print(receivedChar);
  }
}