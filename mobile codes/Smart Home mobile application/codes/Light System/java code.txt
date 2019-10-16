package com.example.smarthome;

import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import okhttp3.OkHttpClient;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class LightSystem extends AppCompatActivity {
    private ImageView imageLightIcon;
    private TextView textViewState;
    private ImageButton buttonOn;
    private ImageButton buttonOff;
    private ImageButton lightButtonActive;
    private ImageButton doorButton1;
    private ImageButton securityButton1;
    private ImageButton wifiButtonLight;
    private WifiManager wifiManager;
    private int numclicked = 0;
    private String numClickedString; //for passing numClicked variable value when converting to landscape mode (changing orientation)
    private ServerInterface serverInterface;



    private final String TEXT_STATE = "textState";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_light_system);


        buttonOn = findViewById(R.id.buttonOn);
        buttonOff = findViewById(R.id.buttonOff);
        imageLightIcon = findViewById(R.id.lightImageLogo);
        textViewState = findViewById(R.id.textViewLight);

        lightButtonActive = findViewById(R.id.lightButton1Active);
        doorButton1 = findViewById(R.id.doorButton1);
        securityButton1 = findViewById(R.id.securityButton1);

        wifiButtonLight = findViewById(R.id.wifiButtonLight);

        wifiManager = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        wifiManager.setWifiEnabled(true);



        textViewState.setText("");

        Gson gson = new GsonBuilder()
                .setLenient()
                .create();

        OkHttpClient client = new OkHttpClient();

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl("http://192.168.4.1")
                .client(client)
                .addConverterFactory(GsonConverterFactory.create(gson))
                .build();

        serverInterface = retrofit.create(ServerInterface.class);


        buttonOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textViewState.setText("");
                String result = "The Light Is ON. \n";
                textViewState.append(result);
                createState();
            }
        });

        buttonOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textViewState.setText("");
                String result = "The Light Is OFF. \n";
                textViewState.append(result);
                createState2();
            }
        });


        doorButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent doorSystem1 = new Intent(LightSystem.this , DoorSystem.class);
                startActivity(doorSystem1);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

        securityButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent securitySystem1 = new Intent(LightSystem.this , SecuritySystem.class);
                startActivity(securitySystem1);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

        wifiButtonLight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                numclicked +=1;
                if (numclicked % 2 == 1){
                    connectToWifi("popos", "123456789");
                    wifiButtonLight.setImageResource(R.drawable.wifi_on);
                    Toast.makeText(LightSystem.this, "Connected to Light System!!!", Toast.LENGTH_LONG).show();
                }
                else {
                    wifiManager.disconnect();
                    wifiButtonLight.setImageResource(R.drawable.wifi_off);
                    Toast.makeText(LightSystem.this, "DisConnected from Light System!!!", Toast.LENGTH_LONG).show();
                }
            }
        });

    }

    @Override
    public void finish() {
        super.finish();
        overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        outState.putString(TEXT_STATE,textViewState.getText().toString());
        outState.putInt(numClickedString ,numclicked);       //saving the value of the numclicked variable into a string variable to save it into the bundle
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        textViewState.setText(savedInstanceState.getString(TEXT_STATE));
        numclicked = savedInstanceState.getInt(numClickedString);     //restoring the value of numclicked variable
        //the following if-else statement to make the current value of the wifiButtonLight background still the same after the change in orientation
        if (numclicked % 2 == 1){
            wifiButtonLight.setImageResource(R.drawable.wifi_on);
        }else {
            wifiButtonLight.setImageResource(R.drawable.wifi_off);
        }
    }


    public void connectToWifi(String networkSSID, String networkPassword) {

        WifiConfiguration conf = new WifiConfiguration();
        conf.SSID = String.format("\"%s\"", networkSSID);
        conf.preSharedKey = String.format("\"%s\"", networkPassword);

        int netId = wifiManager.addNetwork(conf);
        wifiManager.disconnect();
        wifiManager.enableNetwork(netId, true);
        wifiManager.reconnect();
    }

    public void createState() {
        Call<Light> call = serverInterface.createLightOn("LEDOn");

        call.enqueue(new Callback<Light>() {
            @Override
            public void onResponse(Call<Light> call, Response<Light> response) {
                if (!response.isSuccessful()) {
                    Toast.makeText(LightSystem.this, "not connected" + response.code(), Toast.LENGTH_LONG).show();
                    return;
                }
                Light lightResponse = response.body();
                String content = "";
                content += "Code: " + response.code() + "\n";
                content += "State: " + lightResponse.getState() + "\n";


                //textView.setText(content);
            }

            @Override
            public void onFailure(Call<Light> call, Throwable t) {
                //textView.setText(t.getMessage());
            }
        });
    }

    public void createState2() {
        Call<Light> call = serverInterface.createLightOff("LEDOff");

        call.enqueue(new Callback<Light>() {
            @Override
            public void onResponse(Call<Light> call, Response<Light> response) {
                if (!response.isSuccessful()) {
                    Toast.makeText(LightSystem.this, "not connected" + response.code(), Toast.LENGTH_LONG).show();
                    return;
                }
                Light lightResponse = response.body();
                String content = "";
                content += "Code: " + response.code() + "\n";
                content += "State: " + lightResponse.getState() + "\n";


                //textView.setText(content);
            }

            @Override
            public void onFailure(Call<Light> call, Throwable t) {
                //textView.setText(t.getMessage());
            }
        });
    }
}
