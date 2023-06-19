package room.service.mqtt;

import java.util.ArrayList;
import java.util.List;

import io.netty.handler.codec.mqtt.MqttProperties;
import io.vertx.core.Vertx;
import io.vertx.mqtt.MqttEndpoint;
import io.vertx.mqtt.MqttServer;
import io.vertx.mqtt.MqttServerOptions;
import io.vertx.mqtt.messages.codes.MqttSubAckReasonCode;
import room.service.serial.CommChannel;

/**
 * An MQTT Server instance that handles MQTT communication with ESP32.
 * 
 * @param rs Room-Service instance, used to update peripherals values.
 * */
public class MQTTServer {

	public MQTTServer(CommChannel serial) {
		Vertx vertx = Vertx.vertx();
		final List<MqttEndpoint> endpoints = new ArrayList<>();
		MqttServerOptions options = new MqttServerOptions()
            .setHost("192.168.2.2") // Indirizzo IP o hostname del server MQTT
            .setPort(1883); // Porta su cui il server MQTT deve ascoltare
		
		MqttServer mqttServer = MqttServer.create(vertx,options);
		
		mqttServer.endpointHandler(endpoint -> {
			log("client connesso: " + endpoint.clientIdentifier());
			endpoints.add(endpoint);
			
			endpoint.subscribeHandler(subscribe -> {
				List<MqttSubAckReasonCode> reasonCodes = new ArrayList<>();
				  for (io.vertx.mqtt.MqttTopicSubscription s: subscribe.topicSubscriptions()) {
				    log("Subscription for " + s.topicName() + " with QoS " + s.qualityOfService());
				    reasonCodes.add(MqttSubAckReasonCode.qosGranted(s.qualityOfService()));
				  }
				  // ack the subscriptions request
				  endpoint.subscribeAcknowledge(subscribe.messageId(), reasonCodes, MqttProperties.NO_PROPERTIES);
				});
				
			endpoint.unsubscribeHandler(unsubscribe -> {

				  for (String t: unsubscribe.topics()) {
				    System.out.println("Unsubscription for " + t);
				  }
				  // ack the subscriptions request
				  endpoint.unsubscribeAcknowledge(unsubscribe.messageId());
				});

			endpoint.publishHandler(message -> {
				//log("messaggio arrivato: "+ message.payload());
				serial.sendMsg(message.payload().toString());
			});
			endpoint.accept(false);
		}).listen()
		.onComplete(ar -> {
			if(ar.succeeded()) {
				log("MQTT server is listening on port " + ar.result().actualPort());
			} else {
				log("Error on starting the server");
			}
		});
	}
	
	private void log(final String msg) {
		System.out.println("[MQTT SERVER] " + msg);
	}
	
}