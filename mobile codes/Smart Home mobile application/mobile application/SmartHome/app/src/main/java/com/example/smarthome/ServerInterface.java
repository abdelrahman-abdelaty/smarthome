package com.example.smarthome;

import retrofit2.Call;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.POST;

public interface ServerInterface {

    @FormUrlEncoded
    @POST("/LEDOn")
    Call<Light> createLightOn(
            @Field("state") String state
            // @Field("stateNumber") int stateNumber
    );

    @FormUrlEncoded
    @POST("/LEDOff")
    Call<Light> createLightOff(
            @Field("state") String state
            // @Field("stateNumber") int stateNumber
    );

    @FormUrlEncoded
    @POST("/opendoor")
    Call<Door> createDoor(
            @Field("DoorState") String DoorState
    );
}
