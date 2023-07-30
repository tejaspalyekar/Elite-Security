package com.example.elitesecurity;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.view.View;
import android.widget.GridLayout;

import com.google.firebase.auth.FirebaseAuth;

public class control extends AppCompatActivity {
GridLayout gridLayout;
    ProgressDialog mLoadingbar;
    FirebaseAuth mAuth;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control2);
        gridLayout=(GridLayout) findViewById(R.id.maingridlayout);
        setSingleEvent(gridLayout);
        mAuth=FirebaseAuth.getInstance();
        mLoadingbar =new ProgressDialog(control.this);
    }

    private void setSingleEvent(GridLayout gridLayout) {
        for (int i=0;i< this.gridLayout.getChildCount();i++){
            CardView cardView=(CardView)gridLayout.getChildAt(i);
            final int finalI=i;
           cardView.setOnClickListener(new View.OnClickListener() {
               @Override
               public void onClick(View v) {

                       if(finalI==0){
                           Intent intent=new Intent(control.this,profile.class);
                           startActivity(intent);
                       }
                       else if(finalI==1){
                           Intent intent=new Intent(control.this,Dashboard.class);
                           startActivity(intent);
                       }
                       else if(finalI==2){
                           Intent intent=new Intent(control.this,contents.class);
                           startActivity(intent);
                       }
                       else if(finalI==3){
                           mLoadingbar.setTitle("Log out");
                           mLoadingbar.setMessage("please wait");
                           mLoadingbar.setCanceledOnTouchOutside(false);
                           mLoadingbar.show();

                           FirebaseAuth.getInstance().signOut();
                           Intent intent=new Intent(control.this,Login.class);
                           startActivity(intent);
                       }
               }
           });
        }
    }
}