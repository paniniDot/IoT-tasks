package room.service.serial;
import java.io.InputStream;
import java.io.OutputStream;
import com.fazecast.jSerialComm.*;
import java.io.PrintWriter;

public class SerialArduino {
	private SerialPort comPort;
	private String portDescription;
	    private InputStream in;
	    private OutputStream out;
	    private int baud_rate;
	    final byte [] b = new byte[1];

	    public SerialArduino(String portDescription, int baud_rate) {
			this.portDescription = portDescription;
			comPort = SerialPort.getCommPort(this.portDescription);
			this.baud_rate = baud_rate;
			comPort.setBaudRate(this.baud_rate);
	    }
	    public boolean openConnection(){
			if(comPort.openPort()){
				try {Thread.sleep(100);} catch(Exception e){}
				return true;
			}
			else {
				return false;
			}
		}
	    public String read() {
	        StringBuilder sb = new StringBuilder();
	        try {
	            in = comPort.getInputStream();
	            comPort.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 5000, 0); // Aumenta il timeout a 5 secondi
	            while (true) {
	                int data = in.read();
	                if (data == -1) {
	                    break; // Fine della lettura
	                }
	                if (data == '\n') {
	                    break; // Fine della riga
	                }
	                sb.append((char) data);
	            }
	        } catch (Exception e) {
	            e.printStackTrace();
	        }
	        return sb.toString().trim();
	    }


	    public void write(String data) {
	    	comPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
	        try {
	        	Thread.sleep(100);
	        } catch (Exception e) {
	            e.printStackTrace();
	        }
	        PrintWriter pout = new PrintWriter(comPort.getOutputStream());
	        try {
	        	Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	        pout.println(data); // Utilizza println() invece di print() per aggiungere automaticamente un carattere di nuova riga
	        try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	        pout.flush();
	    }

}
