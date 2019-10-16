package com.example.smarthome;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Door {

    @SerializedName("DoorState")
    @Expose
    private String DoorState;

    public Door(String state) {
        this.DoorState = state;
    }

    public String getDoorState() {
        return DoorState;
    }

}
