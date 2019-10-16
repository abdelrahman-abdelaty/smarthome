package com.example.smarthome;

import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageButton;
import android.widget.Toast;

public class SecuritySystem extends AppCompatActivity {

    private ImageButton lightButton3;
    private ImageButton doorButton3;
    private ImageButton securityButtonActive;
    private ImageButton buttonPlayVideo;
    private ImageButton wifiButtonSecurity;
    private WifiManager wifiManager;
    private int numclicked = 0;
    private String numClickedString; //for passing numClicked variable value when converting to landscape mode (changing orientation)
    private WebView webview;
    private String webviewButtonClickString = ""; //for passing TEXT_URL variable value when converting to landscape mode (changing orientation)

    private  String TEXT_URL = "";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_security_system);

        lightButton3 = findViewById(R.id.lightButton3);
        doorButton3 = findViewById(R.id.doorButton3);
        securityButtonActive = findViewById(R.id.securityButton3Active);
        buttonPlayVideo = findViewById(R.id.buttonPlayVideo);

        webview = findViewById(R.id.webViewLivestream);

        wifiButtonSecurity = findViewById(R.id.wifiButtonSecurity);

        wifiManager = (WifiManager) getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        wifiManager.setWifiEnabled(true);


//        webview.setBackgroundColor(Color.TRANSPARENT);

        buttonPlayVideo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                TEXT_URL +="A";

                webview.setWebViewClient(new WebViewClient());
                webview.getSettings().setJavaScriptEnabled(true);
                webview.getSettings().setBuiltInZoomControls(true);
                webview.getSettings().setUseWideViewPort(true);
                webview.loadUrl("http://192.168.1.7/SecurityCamera/");
            }
        });

        lightButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent lightSystem3 = new Intent(SecuritySystem.this , LightSystem.class);
                startActivity(lightSystem3);
                overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
            }
        });

        doorButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent doorSystem3 = new Intent(SecuritySystem.this , DoorSystem.class);
                startActivity(doorSystem3);
                overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
            }
        });

        wifiButtonSecurity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                numclicked +=1;
                if (numclicked % 2 == 1){
                    connectToWifi("SecuritySystem", "SecuritySystem121212");
                    wifiButtonSecurity.setImageResource(R.drawable.wifi_on);
                    Toast.makeText(SecuritySystem.this, "Connected to Security System!!!", Toast.LENGTH_LONG).show();
                }
                else {
                    wifiManager.disconnect();
                    wifiButtonSecurity.setImageResource(R.drawable.wifi_off);
                    Toast.makeText(SecuritySystem.this, "DisConnected from Security System!!!", Toast.LENGTH_LONG).show();
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
        outState.putInt(numClickedString ,numclicked);        //saving the value of the numclicked variable into a string variable to save it into the bundle
        outState.putString(webviewButtonClickString,TEXT_URL);   //saving the value of the TEXT_URL variable into a string variable to save it into the bundle
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        numclicked = savedInstanceState.getInt(numClickedString);     //restoring the value of numclicked variable
        //the following if-else statement to make the current value of the wifiButtonDoor background still the same after the change in orientation
        if (numclicked % 2 == 1){
            wifiButtonSecurity.setImageResource(R.drawable.wifi_on);
        }else {
            wifiButtonSecurity.setImageResource(R.drawable.wifi_off);
        }

        TEXT_URL = savedInstanceState.getString(webviewButtonClickString);  //restoring the value of TEXT_URL variable
        //the following if statement to make the webView still shows the liveStream after the change in orientation
        if (TEXT_URL != "" && wifiManager.isWifiEnabled()){
            webview.setWebViewClient(new WebViewClient());
            webview.getSettings().setJavaScriptEnabled(true);
            webview.getSettings().setBuiltInZoomControls(true);
            webview.getSettings().setUseWideViewPort(true);
            webview.loadUrl("http://192.168.1.7/SecurityCamera/");
        }
    }

//http://192.168.1.7/SecurityCamera/ SecuritySystem  SecuritySystem121212
    public void connectToWifi(String networkSSID, String networkPassword) {

        WifiConfiguration conf = new WifiConfiguration();
        conf.SSID = String.format("\"%s\"", networkSSID);
        conf.preSharedKey = String.format("\"%s\"", networkPassword);

        int netId = wifiManager.addNetwork(conf);
        wifiManager.disconnect();
        wifiManager.enableNetwork(netId, true);
        wifiManager.reconnect();
    }
}
