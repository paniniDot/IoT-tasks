package com.example.roomapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import com.google.android.material.materialswitch.MaterialSwitch;
import com.google.android.material.slider.Slider;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@SuppressLint("MissingPermission")
public class ControllerActivity extends AppCompatActivity {

    private OutputStream bluetoothOutputStream;
    private MaterialSwitch remoteButton;

    private RadioGroup ledRadioButton;
    private boolean ledState;
    private Slider seekBar;

    private RadioGroup servoRadioButton;
    private int servoState;
    private Thread rcv;
    private TextView textView;
    private BluetoothClientConnectionThread connectionThread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //DynamicColors.applyToActivitiesIfAvailable(this);
        setContentView(R.layout.activity_controller);
        ledState = false;
        servoState = 0;
        initUI();
    }

    private void initUI() {
        textView = findViewById(R.id.textView3);
        remoteButton = findViewById(R.id.remotebutton);
        remoteButton.setEnabled(false);
        remoteButton.setOnClickListener((v) -> {
            String message = ledState ? "off\n" : "on\n";
            try {
                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            ledState = !ledState;
            runOnUiThread(() -> remoteButton.setText("led: " + (ledState ? "on" : "off")));
        });
        ledRadioButton =findViewById(R.id.radioGroup);
        ledRadioButton.setOnCheckedChangeListener((group, checkId)->{
            String text = ((RadioButton) group.findViewById(group.getCheckedRadioButtonId())).getText().toString();
            Log.d(C.TAG, "click: "+text);
        });
        seekBar = findViewById(R.id.seekBar);
        seekBar.setEnabled(false);
        seekBar.addOnChangeListener((slider, value, fromUser) -> {
            servoState = (int) seekBar.getValue();
            try {
                bluetoothOutputStream.write(String.valueOf(seekBar.getValue()).getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> {
                textView.setText("servo: " + String.valueOf(seekBar.getValue()));
                seekBar.setValue(servoState);
            });
        });
        servoRadioButton =findViewById(R.id.radioGroup2);
        servoRadioButton.setOnCheckedChangeListener((group, checkId)->{
            String text = ((RadioButton) group.findViewById(group.getCheckedRadioButtonId())).getText().toString();
            Log.d(C.TAG, "click: "+text);
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        Intent intent = getIntent();
        BluetoothDevice bluetoothDevice = intent.getParcelableExtra(ScanActivity.X_BLUETOOTH_DEVICE_EXTRA);
        BluetoothAdapter btAdapter = getSystemService(BluetoothManager.class).getAdapter();
        Log.i(C.TAG, "Connecting to " + bluetoothDevice.getName());
        connectionThread = new BluetoothClientConnectionThread(bluetoothDevice, btAdapter, this::manageConnectedSocket);
        connectionThread.start();
    }

    private void manageConnectedSocket(BluetoothSocket socket) {
        try {
            bluetoothOutputStream = socket.getOutputStream();
            Log.i(C.TAG, "Connection successful!");
            // Thread per la lettura dei messaggi in entrata
            bluetoothOutputStream.write("connesso".getBytes(StandardCharsets.UTF_8));
            rcv = new Thread(() -> {
                try {
                    while (bluetoothOutputStream != null) {
                        BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                        String message = input.readLine();
                        Log.i(C.TAG, "Message received: " + message);
                        if (message.startsWith("ledstatus")) {
                            if (message.substring("ledstatus".length()).equals("1")) {
                                ledState = true;
                            } else if (message.substring("ledstatus".length()).equals("0")) {
                                ledState = false;
                            }
                        } else if (message.startsWith("servo")) {
                            servoState = Integer.parseInt(message.substring("servo".length()));
                        }
                        runOnUiThread(() -> {
                            remoteButton.setEnabled(true);
                            remoteButton.setChecked(ledState);
                            remoteButton.setText("led: " + (ledState ? "on" : "off"));
                            seekBar.setEnabled(true);
                            seekBar.setValue(servoState);
                        });
                    }
                } catch (IOException e) {
                    Log.e(C.TAG, "Error occurred when reading input stream", e);
                }
            });
            rcv.start();
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }

    }

    @Override
    protected void onStop() {
        super.onStop();
        rcv.interrupt();
        connectionThread.cancel();
    }

}