package arduinoui.view;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;

import arduinoui.model.SerialInputListener;

public class ArduinoUi extends JFrame {

	private static final long serialVersionUID = 1L;
	
	private final JComboBox<String> portList;
	private final JButton connectBtn;
	private final JPanel topPanel;
	private JFreeChart graph;
	
	public ArduinoUi(final String title, int width, int height) {
		this.setTitle(title);
		this.setSize(width, height);
		this.setLayout(new BorderLayout());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);		
		this.portList = new JComboBox<>();
		this.connectBtn = new JButton("Connect");
		this.topPanel = new JPanel();
		this.topPanel.add(this.portList);
		this.topPanel.add(this.connectBtn);
		this.add(topPanel, BorderLayout.NORTH);
	}
	
	
	public String getSelectedPort() {
		return this.portList.getSelectedItem().toString();
	}
	
	public void addPorts(List<String> portNames) {
		portNames.forEach(p -> this.portList.addItem(p));
	}
	
	public void setupConnectBtn(final boolean connected, final SerialInputListener listener) {
		this.connectBtn.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				if(connected) {
					connectBtn.setText("Disconnect");
					portList.setEnabled(false);
					listener.start();
				} else {
					
				}
			}
		});
	}
	
	public void setupGraph(final String title, final String xLabel, final String yLabel, final XYDataset dataset) {
		this.graph = ChartFactory.createXYLineChart(title, xLabel, yLabel, dataset, PlotOrientation.VERTICAL, true, false, false);
	}
	
	public void setVisible() {
		this.setVisible(true);
	}
	
}
