#include "SerialComunicationTask.h"
#define MIN_ANGLE 750
#define MAX_ANGLE 2250
SerialComunicationTask serialComunicationTask;

String content;
SerialComunicationTask::SerialComunicationTask()
{
    content.reserve(256);
    msgAvailable = false;
    content = "";
    currentMsg = "";
}

void SerialComunicationTask::init(int period)
{
    Task::init(period);
}

void SerialComunicationTask::tick()
{
    if (isMsgAvailable())
    {
        Serial.println(receiveMsg());
        delay(50);
    }
}
void serialEvent()
{
    /* reading the content */
    while (Serial.available())
    {
        char ch = (char)Serial.read();
        if (ch == 'a')
        {
            serialComunicationTask.currentMsg = content;
            serialComunicationTask.msgAvailable = true;
        }
        else
        {
            content += ch;
        }
    }
}
bool SerialComunicationTask::isMsgAvailable()
{
    return msgAvailable;
}
String SerialComunicationTask::receiveMsg()
{
    String str = currentMsg;
    msgAvailable = false;
    currentMsg = "";
    content = "";
    return str;
}

// Update called from SonarTask and ServoTask
void SerialComunicationTask::update(Event<double> *e)
{
}
