package com.example.elitesecurity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.renderscript.Sampler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class Dashboard extends AppCompatActivity {

    FirebaseDatabase rootNode;
    DatabaseReference reference;
    Button button,button1;
    TextView display;
    ImageButton siren;
    MediaPlayer mediaPlayer;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dashboard);
        button = findViewById(R.id.sensor);
        button1 = findViewById(R.id.rsensor);
        display = findViewById(R.id.display);
        siren   = findViewById(R.id.siren);

        //Write a message to the database
        rootNode = FirebaseDatabase.getInstance();
        reference = rootNode.getReference("SensorData_And_Status/online_Status");
        reference.setValue("1");

         DatabaseReference myRef = FirebaseDatabase.getInstance().getReference();
        // Read from the database

        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
              String onlinedb = (String) dataSnapshot.child("SensorData_And_Status/online_Status").getValue();
              String status = dataSnapshot.child("SensorData_And_Status/Status").getValue().toString();
              String sensordata = dataSnapshot.child("SensorData_And_Status/sensor value").getValue().toString();

              if (Integer.parseInt(onlinedb) == 1 ){
                  display.setText("SYSTEM OFFLINE!!");
                  display.setTextColor(Color.RED);

              }

              if (Integer.parseInt(onlinedb) == 0 ){
                  display.setText("SYSTEM ONLINE!");
                  display.setTextColor(Color.GREEN);

              }

              if ( Integer.parseInt(sensordata) == 1 && status == "on" && mediaPlayer == null ){
                          mediaPlayer=MediaPlayer.create(getApplicationContext(),R.raw.zapsplat_emergency_alarm_siren_warning_harsh_digital_medium_39928);
                          //mediaPlayer.setLooping(true);
                          mediaPlayer.start();
                }
               if (status == "on"){
                   button.setBackgroundColor(Color.GREEN);
                   button1.setBackgroundColor(Color.GRAY);
               }
                if (status == "off"){
                    button1.setBackgroundColor(Color.RED);
                    button.setBackgroundColor(Color.GRAY);
                }
             }


            @Override
            public void onCancelled(DatabaseError error) {
                // Failed to read value

            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                rootNode = FirebaseDatabase.getInstance();
                reference = rootNode.getReference("SensorData_And_Status/Status");
                reference.setValue("on");




            }
        });
       button1.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               rootNode = FirebaseDatabase.getInstance();
               reference = rootNode.getReference("SensorData_And_Status/Status");
               reference.setValue("off");

           }
       });

        siren.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mediaPlayer!=null){
                    mediaPlayer.stop();
                    mediaPlayer=null;
                }


            }
        });


    }
}