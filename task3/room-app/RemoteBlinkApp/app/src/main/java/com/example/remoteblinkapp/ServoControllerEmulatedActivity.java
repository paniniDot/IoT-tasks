package com.example.remoteblinkapp;

import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.SeekBar;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class ServoControllerEmulatedActivity extends AppCompatActivity {

    private SeekBar seekBar;
    private int servoState;
    private OutputStream emulatedBluetoothOutputStream;
    private EmulatedClientConnectionThread connectionThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_servo_controller);
        servoState = 0;
        initUI();
    }

    private void initUI() {
        seekBar = findViewById(R.id.seekBar);
        seekBar.setOnClickListener((v) -> sendMessage());
    }

    private void sendMessage() {
        new Thread(() -> {
            runOnUiThread(() -> seekBar.setProgress(servoState));
        }).start();
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
