package room.service.mqtt;

import java.util.concurrent.BlockingQueue;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MessageListener implements IMqttMessageListener {
	private final BlockingQueue<String> messageQueue;

    public MessageListener(BlockingQueue<String> messageQueue) {
        this.messageQueue = messageQueue;
    }

    @Override
    public void messageArrived(String topic, MqttMessage message) {
        try {
            // Add the received message to the queue
            messageQueue.put(new String(message.getPayload()));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
