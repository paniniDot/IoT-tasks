package room.service.client;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class Client extends MqttClient {

	private final List<String> topics = new ArrayList<>();
	
	public Client(String method, String serverUri, int port) throws MqttException {
		super(method + "://" + serverUri + ":" + port, MqttClient.generateClientId(), new MemoryPersistence());
		this.setConnection();
	}
	
	private void setConnection() throws MqttException {
		if (!this.isConnected()) {
			this.connect();
		}
	}

	public void registerToTopic(final String topic, IMqttMessageListener listener) throws MqttException {
	    if (!this.topics.contains(topic)) {
	        this.topics.add(topic);
	        this.subscribe(topic, listener);
	    }
	}

	public List<String> getRegisteredTopics() {
		return List.copyOf(this.topics);
	}

}