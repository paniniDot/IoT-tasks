package room.service.serial;

import java.io.IOException;
import java.util.concurrent.*;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

public class SerialCommChannel implements CommChannel {
	
	private BlockingQueue<String> queue;
	private SerialPort port;
	
	public SerialCommChannel(String portName, int rate) {
		this.queue = new ArrayBlockingQueue<String>(100);
		this.port = SerialPort.getCommPort(portName);
		this.port.setComPortParameters(
				rate, 
				8, 
				SerialPort.ONE_STOP_BIT, 
				SerialPort.FLOW_CONTROL_DISABLED);
		this.port.openPort();
		this.port.addDataListener(new SerialPortDataListener() {	
			
			String messages = "";
			
			@Override
			public void serialEvent(SerialPortEvent event) {
				messages += new String(event.getReceivedData());
				System.out.println("Messaggio attuale: " + messages);
				while (messages.contains("\n")) {
					String[] message = messages.split("\\n", 2);
					messages = (message.length > 1) ? message[1] : "";
					System.out.println("Message: " + message[0]);
				}
			}	
			
			@Override
			public int getListeningEvents() {
				return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
			}
		});
	}
	
	
	@Override
	public void sendMsg(String msg) {
		try {
			this.port.getOutputStream().write(msg.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public String receiveMsg() throws InterruptedException {
		return this.queue.take();
	}

	@Override
	public boolean isMsgAvailable() {
		return !this.queue.isEmpty();
	}
	
	public void close() {
		this.port.closePort();
	}
}

