package arduinoui;

import arduinoui.model.SerialCom;
import arduinoui.view.ArduinoUi;

public class Main {
	public static void main(String[] args) {
		
		ArduinoUi ui = new ArduinoUi("Arduino UI", 600, 400);
		SerialCom sCom = new SerialCom();
		ui.addPorts(sCom.getSystemPortNames());
		
	}
}
