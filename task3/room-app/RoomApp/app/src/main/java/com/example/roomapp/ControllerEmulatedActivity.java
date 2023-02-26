package com.example.roomapp;

import androidx.appcompat.app.AppCompatActivity;


import android.os.Bundle;
import android.util.Log;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import android.widget.CheckBox;
import android.widget.TextView;

import com.google.android.material.materialswitch.MaterialSwitch;
import com.google.android.material.slider.Slider;

public class ControllerEmulatedActivity extends AppCompatActivity {
    private MaterialSwitch lightSwitch;
    private CheckBox lightCheckBox;
    private boolean lightState;
    private Slider rollSlider;
    private CheckBox rollCheckBox;
    private int rollState;
    private TextView rollText;

    private OutputStream emulatedBluetoothOutputStream;

    private EmulatedClientConnectionThread connectionThread;

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
                emulatedBluetoothOutputStream.write(("light: " + (lightState ? "on" : "off") + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> lightSwitch.setText("light: " + (lightState ? "on" : "off")));
        });
        lightCheckBox = findViewById(R.id.checkBox2);
        lightCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (isChecked) {
                runOnUiThread(() -> lightSwitch.setEnabled(true));
            } else {
                runOnUiThread(() -> lightSwitch.setEnabled(false));
            }
        });
        rollSlider = findViewById(R.id.seekBar);
        rollSlider.addOnChangeListener((slider, value, fromUser) -> {
            rollState = (int) rollSlider.getValue();
            Log.i(C.TAG, "roll: " + rollSlider.getValue());
            new Thread(() -> {
            try {
                emulatedBluetoothOutputStream.write(("roll: " + rollSlider.getValue() + "\n").getBytes(StandardCharsets.UTF_8));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            }).start();
            runOnUiThread(() -> {
                rollText.setText("roll: " + rollSlider.getValue());
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
        });
        lightSwitch.setEnabled(false);
        rollSlider.setEnabled(false);
        rollCheckBox.setEnabled(false);
        lightCheckBox.setEnabled(false);
    }

    @Override
    protected void onStart() {
        super.onStart();
        connectionThread = new EmulatedClientConnectionThread(this::manageConnectedSocket);
        connectionThread.start();
    }

    private void manageConnectedSocket(Socket socket) {
        try {
            emulatedBluetoothOutputStream = socket.getOutputStream();
            Log.i(C.TAG, "Connection successful!");
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }
        runOnUiThread(() -> {
            lightSwitch.setChecked(lightState);
            lightSwitch.setText("light: " + (lightState ? "on" : "off"));
            rollSlider.setValue(rollState);
            rollCheckBox.setEnabled(true);
            lightCheckBox.setEnabled(true);
        });
        /*new Thread(() -> {
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
            }
            Log.i(C.TAG, "Socket closed");
        }).start();*/
    }

    @Override
    protected void onStop() {
        super.onStop();
        connectionThread.cancel();
    }
}