package com.example.roomapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import com.google.android.material.slider.Slider;
import com.google.android.material.switchmaterial.SwitchMaterial;

import java.io.OutputStream;

public class ControllerEmulatedActivity extends AppCompatActivity {

    private SwitchMaterial remoteButton;
    private boolean ledState;
    private Slider seekBar;
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
        textView = findViewById(R.id.textView3);
        remoteButton = findViewById(R.id.remotebutton);
        remoteButton.setEnabled(false);
        remoteButton.setOnClickListener((v) -> {
            runOnUiThread(() -> remoteButton.setText("led: " + (ledState ? "off" : "on")));
            ledState = !ledState;
        });
        seekBar = findViewById(R.id.seekBar);
        seekBar.setEnabled(false);
        seekBar.addOnChangeListener((slider, value, fromUser) -> {
            servoState = (int) slider.getValue();
            runOnUiThread(() -> {
                textView.setText("servo: " + String.valueOf(seekBar.getValue()));
                seekBar.setValue(servoState);
            });
        });
        manageConnectedSocket();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    private void manageConnectedSocket() {
        runOnUiThread(() -> {
            remoteButton.setEnabled(true);
            remoteButton.setChecked(ledState);
            seekBar.setEnabled(true);
            seekBar.setValue(servoState);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
    }
}