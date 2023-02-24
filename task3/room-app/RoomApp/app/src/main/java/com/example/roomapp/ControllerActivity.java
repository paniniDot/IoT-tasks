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
import android.widget.CheckBox;
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
    private MaterialSwitch lightSwitch;
    private CheckBox lightCheckBox;
    private boolean lightState;
    private Slider rollSlider;
    private CheckBox rollCheckBox;
    private int rollState;
    private TextView rollText;
    private BluetoothClientConnectionThread connectionThread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //DynamicColors.applyToActivitiesIfAvailable(this);
        setContentView(R.layout.activity_controller);
        lightState = false;
        rollState = 0;
        initUI();
    }

    private void initUI() {
        rollText = findViewById(R.id.textView3);
        lightSwitch = findViewById(R.id.remotebutton);
        lightSwitch.setOnClickListener((v) -> {
            String message = lightState ? "off\n" : "on\n";
            try {
                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            lightState = !lightState;
            runOnUiThread(() -> lightSwitch.setText("led: " + (lightState ? "on" : "off")));
        });
        lightCheckBox = findViewById(R.id.checkBox2);
        lightCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                runOnUiThread(() -> lightSwitch.setEnabled(true));
            } else {
                runOnUiThread(() -> lightSwitch.setEnabled(false));
            }
            try {
                bluetoothOutputStream.write(("led: " + isChecked + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
        rollSlider = findViewById(R.id.seekBar);
        rollSlider.addOnChangeListener((slider, value, fromUser) -> {
            rollState = (int) rollSlider.getValue();
            try {
                bluetoothOutputStream.write((rollSlider.getValue() + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> {
                rollText.setText("servo: " + rollSlider.getValue());
                rollSlider.setValue(rollState);
            });
        });
        rollCheckBox = findViewById(R.id.checkBox);
        rollCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                runOnUiThread(() -> rollSlider.setEnabled(true));
            } else {
                runOnUiThread(() -> rollSlider.setEnabled(false));
            }
            try {
                bluetoothOutputStream.write(("servo: " + isChecked  + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });
        lightSwitch.setEnabled(false);
        rollSlider.setEnabled(false);
        rollCheckBox.setEnabled(false);
        lightCheckBox.setEnabled(false);
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
            bluetoothOutputStream.write("connesso".getBytes(StandardCharsets.UTF_8));
            new Thread(() -> {
                BufferedReader input = null;
                try {
                    input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                while (socket.isConnected()) {
                    String message;
                    try {
                        message = input.readLine();
                        if (message == null) {
                            socket.close();
                            return;
                        }
                    } catch (IOException e) {
                        return;
                    }
                    Log.i(C.TAG, "Message received: " + message);
                    if (message.startsWith("ledstatus")) {
                        if (message.substring("ledstatus".length()).equals("1")) {
                            lightState = true;
                        } else if (message.substring("ledstatus".length()).equals("0")) {
                            lightState = false;
                        }
                    } else if (message.startsWith("servo")) {
                        rollState = Integer.parseInt(message.substring("servo".length()));
                    }
                    runOnUiThread(() -> {
                        lightSwitch.setChecked(lightState);
                        lightSwitch.setText("led: " + (lightState ? "on" : "off"));
                        rollSlider.setValue(rollState);
                        rollCheckBox.setEnabled(true);
                        lightCheckBox.setEnabled(true);
                    });
                }
                Log.i(C.TAG, "Socket closed");
            }).start();
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }

    }

    @Override
    protected void onStop() {
        super.onStop();
        connectionThread.cancel();
    }

}