package com.example.roomapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.drawable.Drawable;
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
        setContentView(R.layout.activity_controller);
        lightState = false;
        rollState = 0;
        initUI();
    }

    private void initUI() {
        rollText = findViewById(R.id.textView3);
        lightSwitch = findViewById(R.id.remotebutton);
        lightSwitch.setOnClickListener((v) -> {
            lightState = !lightState;
            try {
                bluetoothOutputStream.write(("light: " + lightState + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> {
                lightSwitch.setThumbIconDrawable(lightState ? getResources().getDrawable(R.drawable.lightbulb_filled_48px):getResources().getDrawable(R.drawable.lightbulb_48px));
                lightSwitch.setText(lightState ? "light: on" : "light: off");
            });
        });
        lightCheckBox = findViewById(R.id.checkBox2);
        lightCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (buttonView.isPressed())
            {
                runOnUiThread(() -> lightSwitch.setEnabled(isChecked));
                try {
                    bluetoothOutputStream.write(("lightcheckbox: " + isChecked + "\n").getBytes(StandardCharsets.UTF_8));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        rollSlider = findViewById(R.id.seekBar);
        rollSlider.addOnChangeListener((slider, value, fromUser) -> {
            rollState = (int) rollSlider.getValue();
            try {
                bluetoothOutputStream.write(("roll: " + rollState + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> {
                rollText.setText("roll: " + rollState);
                rollSlider.setValue(rollState);
            });
        });
        rollCheckBox = findViewById(R.id.checkBox);
        rollCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (buttonView.isPressed())
            {
                runOnUiThread(() -> rollSlider.setEnabled(isChecked));
                try {
                    bluetoothOutputStream.write(("rollcheckbox: " + isChecked + "\n").getBytes(StandardCharsets.UTF_8));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
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
                    if (message.startsWith("lightstate: ")) {
                        lightState = message.substring("lightstate: ".length()).equals("1");
                        runOnUiThread(() -> {
                            lightSwitch.setChecked(lightState);
                            lightSwitch.setText("light: " + (lightState ? "on" : "off"));
                        });
                    } else if (message.startsWith("lightcheckbox: ")) {
                        boolean b = message.substring("lightcheckbox: ".length()).equals("1");
                        runOnUiThread(() -> {
                            lightCheckBox.setChecked(b);
                            lightSwitch.setEnabled(b);
                            lightCheckBox.setEnabled(true);
                        });
                    } else if (message.startsWith("rollcheckbox: ")) {
                        boolean b = message.substring("rollcheckbox: ".length()).equals("1");
                        runOnUiThread(() -> {
                            rollCheckBox.setChecked(b);
                            rollSlider.setEnabled(b);
                            rollCheckBox.setEnabled(true);
                        });
                    } else if (message.startsWith("roll: ")) {
                        rollState = Integer.parseInt(message.substring("roll: ".length()));
                        runOnUiThread(() -> rollSlider.setValue(rollState));
                    }
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