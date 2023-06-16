/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package room.service;

import room.service.client.Client;
import room.service.html.DataService;
import room.service.mqtt.MessageListener;

import room.service.serial.*;
import room.service.utils.JsonBuilder;

import org.eclipse.paho.client.mqttv3.MqttException;

import io.vertx.core.Vertx;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class App {

    public static void main(String[] args) throws Exception {
        // Create a blocking queue to store the received messages
        BlockingQueue<String> messageQueue = new LinkedBlockingQueue<>();
        CommChannel serial = new SerialCommChannel("/dev/ttyACM0", 9600);
        Vertx vertx = Vertx.vertx();
		DataService service = new DataService(8080);
		vertx.deployVerticle(service);
		try (Client client = new Client("tcp", "broker.mqtt-dashboard.com", 1883)) {

            // Register message listeners for the topics
            client.registerToTopic("esp32/light", new MessageListener(messageQueue));
            client.registerToTopic("esp32/motion", new MessageListener(messageQueue));
            Thread.sleep(1000);
            while (true) {
                // Check if there are any messages in the queue
                if (!messageQueue.isEmpty()) {
                    String message = messageQueue.take();
                    serial.sendMsg(message);
                    if(serial.isMsgAvailable()) {
                    	System.out.println(serial.receiveMsg());
                    	service.addMeasure(JsonBuilder.getJsonWithTimestamp(serial.receiveMsg()));
                    }
                }
            }
        } catch (MqttException | InterruptedException e) {
            e.printStackTrace();
        }
    }
    
}
