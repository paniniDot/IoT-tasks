#include "SerialComunicationTask.h"
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
    this->notify();
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
    return serialComunicationTask.msgAvailable;
}
String SerialComunicationTask::receiveMsg()
{
    String str = serialComunicationTask.currentMsg;
    serialComunicationTask.msgAvailable = false;
    serialComunicationTask.currentMsg = "";
    content = "";
    return str;
}

// Update called from SonarTask and ServoTask
void SerialComunicationTask::update(Event<double> *e)
{
}

void SerialComunicationTask::notify()
{
    // if(this->isMsgAvailable()){
    //     String msg = this->receiveMsg();
    //     if(msg == "YES" || msg == "NO"){
    //         Event<double> *e = new Event<double>(EventSourceType::CHECKBOX, new double(0));
    //         for (int i = 0; i < this->getNObservers(); i++)
    //         {
    //             this->getObservers()[i]->update(e);
    //         }
    //         delete e;
    //     }
    //     Event<double> *e = new Event<double>(EventSourceType::SLIDER, new double(msg.toDouble()));
    //     for (int i = 0; i < this->getNObservers(); i++)
    //     {
    //         this->getObservers()[i]->update(e);
    //     }
    //     delete e;
    // }
}