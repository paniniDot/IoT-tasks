package com.example.roomapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.OutputStream;

public class ControllerEmulatedActivity extends AppCompatActivity {

    private Button remoteButton;
    private boolean ledState;
    private SeekBar seekBar;
    private int servoState;

    private TextView textView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);
        ledState = false;
        servoState = 0;
        initUI();
    }

    private void initUI() {
        textView= findViewById(R.id.textView3);
        remoteButton = findViewById(R.id.remotebutton);
        remoteButton.setEnabled(false);
        remoteButton.setOnClickListener((v) -> sendMessage());
        seekBar = findViewById(R.id.seekBar);
        seekBar.setEnabled(false);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                textView.setText("servo: "+String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                new Thread(() -> {
                    servoState = seekBar.getProgress();
                    runOnUiThread(() -> seekBar.setProgress(servoState));
                }).start();
            }
        });
        manageConnectedSocket();
    }

    private void sendMessage() {
        new Thread(() -> {
            String message = ledState ? "off\n" : "on\n";
            remoteButton.setText("led: "+ (ledState ? "off" : "on"));
            ledState = !ledState;
        }).start();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    private void manageConnectedSocket() {
        runOnUiThread(() -> {
            remoteButton.setEnabled(true);
            seekBar.setEnabled(true);
            seekBar.setProgress(servoState);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
    }
}