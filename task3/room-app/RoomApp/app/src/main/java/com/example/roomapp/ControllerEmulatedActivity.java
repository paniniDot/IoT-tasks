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
        runOnUiThread(() -> {
            lightSwitch.setChecked(lightState);
            lightSwitch.setText("light: " + (lightState ? "on" : "off"));
            rollSlider.setValue(rollState);
            rollCheckBox.setEnabled(true);
            lightCheckBox.setEnabled(true);
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
    }
}