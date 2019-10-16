package com.example.smarthome;

import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
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

public class DoorSystem extends AppCompatActivity {
    private TextView textViewDoor;
    private ImageButton buttonOpenDoor;
    private ImageButton lightButton2;
    private ImageButton doorButtonActive;
    private ImageButton securityButton2;
    private ImageButton wifiButtonDoor;
    private WifiManager wifiManager;
    private int numclicked = 0;
    private String numClickedString; //for passing numClicked variable value when converting to landscape mode (changing orientation)
    private ServerInterface serverInterface;


    private final String TEXT_DOOR = "textState";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_door_system);

        textViewDoor = findViewById(R.id.textViewDoor);
        buttonOpenDoor = findViewById(R.id.buttonOpenDoor);

        lightButton2 = findViewById(R.id.lightButton2);
        doorButtonActive = findViewById(R.id.doorButton2Active);
        securityButton2 = findViewById(R.id.securityButton2);

        wifiButtonDoor = findViewById(R.id.wifiButtonDoor);

        wifiManager = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        wifiManager.setWifiEnabled(true);


        textViewDoor.setText("");

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

        buttonOpenDoor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textViewDoor.setText("");
                String result = "   The Door Is Opened. \n  And Will Close After Few Seconds.";
                textViewDoor.append(result);
                createStateDoor();
            }
        });

        lightButton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent lightSystem2 = new Intent(DoorSystem.this , LightSystem.class);
                startActivity(lightSystem2);
                overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
            }
        });

        securityButton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent securitySystem2 = new Intent(DoorSystem.this , SecuritySystem.class);
                startActivity(securitySystem2);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

        wifiButtonDoor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                numclicked +=1;
                if (numclicked % 2 == 1){
                    connectToWifi("popos", "123456789");
                    wifiButtonDoor.setImageResource(R.drawable.wifi_on);
                    Toast.makeText(DoorSystem.this, "Connected to Door System!!!", Toast.LENGTH_LONG).show();
                }
                else {
                    wifiManager.disconnect();
                    wifiButtonDoor.setImageResource(R.drawable.wifi_off);
                    Toast.makeText(DoorSystem.this, "DisConnected from Door System!!!", Toast.LENGTH_LONG).show();
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
        outState.putString(TEXT_DOOR,textViewDoor.getText().toString());
        outState.putInt(numClickedString ,numclicked);       //saving the value of the numclicked variable into a string variable to save it into the bundle
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        textViewDoor.setText(savedInstanceState.getString(TEXT_DOOR));
        numclicked = savedInstanceState.getInt(numClickedString);     //restoring the value of numclicked variable
        //the following if-else statement to make the current value of the wifiButtonDoor background still the same after the change in orientation
        if (numclicked % 2 == 1){
            wifiButtonDoor.setImageResource(R.drawable.wifi_on);
        }else {
            wifiButtonDoor.setImageResource(R.drawable.wifi_off);
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

    public void createStateDoor() {

        Call<Door> call = serverInterface.createDoor("opendoor");

        call.enqueue(new Callback<Door>() {
            @Override
            public void onResponse(Call<Door> call, Response<Door> response) {
                if (!response.isSuccessful()) {
                    Toast.makeText(DoorSystem.this, "not connected" + response.code(), Toast.LENGTH_LONG).show();
                    return;
                }
                Door doorResponse = response.body();
                String content = "";
                content += "Code: " + response.code() + "\n";
                content += "State: " + doorResponse.getDoorState() + "\n";


                //textView.setText(content);
            }

            @Override
            public void onFailure(Call<Door> call, Throwable t) {
                //textView.setText(t.getMessage());
            }
        });
    }
}
