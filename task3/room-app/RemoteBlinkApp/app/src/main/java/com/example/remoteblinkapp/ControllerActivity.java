package com.example.remoteblinkapp;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.SeekBar;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@SuppressLint("MissingPermission")
public class ControllerActivity extends AppCompatActivity {

    private OutputStream bluetoothOutputStream;
    private Button remoteButton;
    private boolean ledState;
    private SeekBar seekBar;
    private int servoState;
    private BluetoothClientConnectionThread connectionThread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);
        ledState = false;
        servoState = 0;
        initUI();
    }

    private void initUI() {
        remoteButton = findViewById(R.id.remotebutton);
        remoteButton.setEnabled(false);
        remoteButton.setOnClickListener((v) -> sendMessage());
        seekBar = findViewById(R.id.seekBar);
        seekBar.setEnabled(false);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                new Thread(() -> {
                    try {
                        servoState = seekBar.getProgress();
                        bluetoothOutputStream.write(String.valueOf(servoState).getBytes(StandardCharsets.UTF_8));
                        runOnUiThread(() -> seekBar.setProgress(servoState));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }).start();
            }
        });
    }

    private void sendMessage() {
        new Thread(() -> {
            try {
                String message = ledState ? "off\n" : "on\n";
                bluetoothOutputStream.write(message.getBytes(StandardCharsets.UTF_8));
                ledState = !ledState;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }).start();
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
        } catch (IOException e) {
            Log.e(C.TAG, "Error occurred when creating output stream", e);
        }
        runOnUiThread(() -> {
            remoteButton.setEnabled(true);
            seekBar.setEnabled(true);
            seekBar.setProgress(servoState);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
        connectionThread.cancel();
    }

}