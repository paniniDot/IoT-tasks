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
		this.port.addDataListener(new SerialPortDataListener() {	
			
			@Override
			public void serialEvent(SerialPortEvent event) {
				if (event.getEventType() == SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
                    String message = new String(new byte[port.bytesAvailable()]);
                    queue.add(message);
                    System.out.println("Messaggio ricevuto: " + message);
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

