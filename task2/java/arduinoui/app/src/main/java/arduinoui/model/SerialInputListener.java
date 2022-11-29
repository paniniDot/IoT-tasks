package arduinoui.model;

import java.util.Scanner;

import com.fazecast.jSerialComm.SerialPort;

public class SerialInputListener extends Thread {

	private SerialPort port;
	
	public SerialInputListener(final SerialPort port) {
		this.port = port;
	}
	
	@Override 
	public void run() {
		final Scanner sc = new Scanner(this.port.getInputStream());
		while(sc.hasNextLine()) {
			try {
				final String line = sc.nextLine();
				final double waterLevel = Double.parseDouble(line);
				
			} catch (Exception e) {
			}
		}
	}
	
}
