package arduinoui.model;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import com.fazecast.jSerialComm.SerialPort;

public class SerialCom {
	
	public SerialCom() {
	}
	
	public List<String> getSystemPortNames() {
		return Arrays.stream(SerialPort.getCommPorts())
				.map(SerialPort::getSystemPortName)
				.collect(Collectors.toList());
	}
	
	public boolean openPort(final String portName) {
		final SerialPort port = SerialPort.getCommPort(portName);
		port.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
		return port.openPort();
	}
	
}
