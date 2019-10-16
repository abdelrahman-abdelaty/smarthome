package com.example.smarthome;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {
    private ImageView homeIcon;
    private ImageButton lightButton;
    private ImageButton doorButton;
    private ImageButton securityButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        lightButton = findViewById(R.id.lightSystemButton);
        doorButton = findViewById(R.id.doorSystemButton);
        securityButton = findViewById(R.id.securitySystemButton);

        lightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent lightSystem = new Intent(MainActivity.this , LightSystem.class);
                startActivity(lightSystem);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

        doorButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent doorSystem = new Intent(MainActivity.this , DoorSystem.class);
                startActivity(doorSystem);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

        securityButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent securitySystem = new Intent(MainActivity.this , SecuritySystem.class);
                startActivity(securitySystem);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

    }

}
