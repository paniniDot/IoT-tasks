package com.example.roomapp;

import static android.content.ContentValues.TAG;

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

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.res.ResourcesCompat;

import com.google.android.material.color.DynamicColors;
import com.google.android.material.materialswitch.MaterialSwitch;
import com.google.android.material.slider.Slider;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
    private boolean isDragging = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        DynamicColors.applyToActivityIfAvailable(this);
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
                JSONObject configJson = new JSONObject();
                configJson.put("name", "light");
                configJson.put("measure", lightState ? 1 : 0);
                bluetoothOutputStream.write(configJson.toString().getBytes(StandardCharsets.UTF_8));
            } catch (IOException | JSONException e) {
                throw new RuntimeException(e);
            }
            runOnUiThread(() -> {
                lightSwitch.setThumbIconDrawable(lightState ? ResourcesCompat.getDrawable(getResources(), R.drawable.lightbulb_filled_48px, null) : ResourcesCompat.getDrawable(getResources(), R.drawable.lightbulb_48px, null));
                lightSwitch.setText(lightState ? "light: on" : "light: off");
            });
        });
        lightCheckBox = findViewById(R.id.checkBox2);
        lightCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (buttonView.isPressed()) {
                runOnUiThread(() -> lightSwitch.setEnabled(isChecked));
                try {
                    JSONObject configJson = new JSONObject();
                    configJson.put("name", "manual_light");
                    configJson.put("measure", isChecked ? 1 : 0);
                    bluetoothOutputStream.write(configJson.toString().getBytes(StandardCharsets.UTF_8));
                } catch (IOException | JSONException e) {
                    throw new RuntimeException(e);
                }
            }
        });
        rollSlider = findViewById(R.id.seekBar);
        rollSlider.addOnChangeListener((slider, value, fromUser) -> {
            if (fromUser) {
                rollState = (int) value;
                isDragging = true;
            }
        });
        rollSlider.addOnSliderTouchListener(new Slider.OnSliderTouchListener() {
            @Override
            public void onStartTrackingTouch(@NonNull Slider slider) {
                // Non è necessario fare nulla all'inizio del tracciamento del tocco.
            }

            @Override
            public void onStopTrackingTouch(@NonNull Slider slider) {
                // Qui puoi ottenere il valore dello slider e inviarlo solo se il click è stato rilasciato.
                if (isDragging) {
                    try {
                        JSONObject configJson = new JSONObject();
                        configJson.put("name", "roll");
                        configJson.put("measure", rollState);
                        bluetoothOutputStream.write(configJson.toString().getBytes(StandardCharsets.UTF_8));
                    } catch (IOException | JSONException e) {
                        throw new RuntimeException(e);
                    }

                    runOnUiThread(() -> {
                        // Aggiorna la visualizzazione del valore
                        rollText.setText("roll: " + rollState);
                        rollSlider.setValue(rollState);
                    });

                    isDragging = false;
                }
            }
        });
        rollCheckBox = findViewById(R.id.checkBox);
        rollCheckBox.setOnCheckedChangeListener((buttonView, isChecked) -> {
            if (buttonView.isPressed()) {
                runOnUiThread(() -> rollSlider.setEnabled(isChecked));
                try {
                    JSONObject configJson = new JSONObject();
                    configJson.put("name", "manual_roll");
                    configJson.put("measure", isChecked ? 1 : 0);
                    bluetoothOutputStream.write(configJson.toString().getBytes(StandardCharsets.UTF_8));
                } catch (IOException | JSONException e) {
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
        connectionThread = new BluetoothClientConnectionThread(bluetoothDevice, btAdapter, this::manageConnectedSocket);
        connectionThread.start();
    }


    private void manageConnectedSocket(BluetoothSocket socket) {
        try {
            bluetoothOutputStream = socket.getOutputStream();
            runOnUiThread(() -> {
                lightCheckBox.setEnabled(true);
                rollCheckBox.setEnabled(true);
            });
            new Thread(() -> {
                BufferedReader input;
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
                    Log.i(TAG, "Message received: " + message);
                    try {
                        JSONObject jsonObject = new JSONObject(message);
                        String name = jsonObject.getString("name");
                        int measure = jsonObject.getInt("measure");
                        if (name.equals("light")) {
                            lightState = measure != 0;
                            runOnUiThread(() -> {
                                lightSwitch.setThumbIconDrawable(lightState ? ResourcesCompat.getDrawable(getResources(), R.drawable.lightbulb_filled_48px, null) : ResourcesCompat.getDrawable(getResources(), R.drawable.lightbulb_48px, null));
                                lightSwitch.setChecked(lightState);
                                lightSwitch.setText("light: " + (lightState ? "on" : "off"));
                            });
                        } else if (name.equals("roll")) {
                            rollState = measure;
                            runOnUiThread(() -> {
                                rollSlider.setValue(rollState);
                                rollText.setText("roll: " + rollState);
                            });
                        } else if (jsonObject.has("lightcheckbox")) {
                            int lightCheckboxState = jsonObject.getInt("lightcheckbox");
                            boolean lightCheckboxValue = lightCheckboxState != 0;
                            runOnUiThread(() -> {
                                lightCheckBox.setChecked(lightCheckboxValue);
                                lightSwitch.setEnabled(lightCheckboxValue);
                            });
                        } else if (jsonObject.has("rollcheckbox")) {
                            int rollCheckboxState = jsonObject.getInt("rollcheckbox");
                            boolean rollCheckboxValue = rollCheckboxState != 0;
                            runOnUiThread(() -> {
                                rollCheckBox.setChecked(rollCheckboxValue);
                                rollSlider.setEnabled(rollCheckboxValue);
                            });
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
                Log.i(TAG, "Socket closed");
            }).start();
        } catch (IOException e) {
            Log.e(TAG, "Error occurred when creating output stream", e);
        }
    }

    @Override
    protected void onStop() {
        super.onStop();
        connectionThread.cancel();
    }

}