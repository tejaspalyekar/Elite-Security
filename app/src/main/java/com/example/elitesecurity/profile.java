package com.example.elitesecurity;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.DocumentSnapshot;
import com.google.firebase.firestore.EventListener;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.FirebaseFirestoreException;

public class profile extends AppCompatActivity {
TextView name,email,phoneno;
FirebaseAuth mAuth;
FirebaseFirestore firestore;
String Userid;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);
        phoneno=findViewById(R.id.textView3);
        name=findViewById(R.id.textView4);
        email=findViewById(R.id.textView5);
      mAuth=FirebaseAuth.getInstance();
      firestore=FirebaseFirestore.getInstance();
     Userid=mAuth.getCurrentUser().getUid();
        DocumentReference documentReference=firestore.collection("users").document(Userid);
        documentReference.addSnapshotListener(this, new EventListener<DocumentSnapshot>() {
            @Override

            public void onEvent(@Nullable DocumentSnapshot documentSnapshot, @Nullable FirebaseFirestoreException error) {
                name.setText(documentSnapshot.getString("name"));
                email.setText(documentSnapshot.getString("Email"));
                phoneno.setText(documentSnapshot.getString("Phone NO"));


            }
        });
    }
}