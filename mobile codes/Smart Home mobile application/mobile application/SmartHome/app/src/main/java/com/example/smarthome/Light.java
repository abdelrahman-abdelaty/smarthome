package com.example.smarthome;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Light {
    @SerializedName("state")
    @Expose
    private String state;



    public Light(String state) {
        this.state = state;
    }

    public String getState() {
        return state;
    }

}
