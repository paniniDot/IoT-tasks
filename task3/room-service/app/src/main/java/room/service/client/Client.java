package room.service.client;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class Client extends MqttClient {

	private final List<String> topics = new ArrayList<>();
	
	public Client(String method, String serverUri, int port) throws MqttException {
		super("tcp://broker.mqtt-dashboard.com:1883", MqttClient.generateClientId(), new MemoryPersistence());
		//method + "://" + serverUri + ":" + port
		try (Client client = this) {
			this.connect();
			this.setCallback(new MqttCallback() {
				
				@Override
				public void messageArrived(String topic, MqttMessage message) throws Exception {
					System.out.println(topic);
					System.out.println(message);
				}
				
				@Override
				public void connectionLost(Throwable cause) {
				}
				
				@Override
				public void deliveryComplete(IMqttDeliveryToken token) {
				}
			});
		} catch (Exception e) {
            throw new MqttException(e);
        }
		
	}
	
	@Override
    public void close() throws MqttException {
        if (this.isConnected()) {
            this.disconnect();
        }
    }
	
	public void registerToTopic(final String topic) throws MqttException {
	    if (!this.topics.contains(topic)) {
	        this.topics.add(topic);
	        if (this.isConnected()) {
	            this.subscribe(topic);
	        } else {
	            throw new MqttException(new Throwable("Client is not connected"));
	        }
	    }
	}

	
	public List<String> getRegisteredTopics() {
		return List.copyOf(this.topics);
	}

}
