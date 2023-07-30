package com.example.elitesecurity;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.textfield.TextInputLayout;
import com.google.firebase.auth.FirebaseAuth;

public class Forgetpassword extends AppCompatActivity {
Button forget,next;
EditText email;
boolean  isEmailValid;
TextInputLayout emailError;
    FirebaseAuth mAuth;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_forgetpassword);
        forget=(Button)findViewById(R.id.loginback);
        next=(Button) findViewById(R.id.submit);
        mAuth = FirebaseAuth.getInstance();
        email=(EditText) findViewById(R.id.email_id);
        emailError = (TextInputLayout) findViewById(R.id.emailError);
        next.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            validate();
            }
        });
        forget.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent=new Intent(Forgetpassword.this,Login.class);
                startActivity(intent);
            }
        });
    }

    private void validate() {
        if (email.getText().toString().isEmpty()) {
            emailError.setError(getResources().getString(R.string.email_error));
            isEmailValid = false;
        } else if (!Patterns.EMAIL_ADDRESS.matcher(email.getText().toString()).matches()) {
            emailError.setError(getResources().getString(R.string.error_invalid_email));
            isEmailValid = false;
        } else  {
            isEmailValid = true;
            emailError.setErrorEnabled(false);
        }
        if(isEmailValid){
         mAuth.sendPasswordResetEmail(email.getText().toString()).addOnCompleteListener(new OnCompleteListener<Void>() {
             @Override
             public void onComplete(@NonNull Task<Void> task) {
               if(task.isSuccessful()){
                   Toast.makeText(Forgetpassword.this,"check your Email",Toast.LENGTH_SHORT).show();

                   startActivity(new Intent(Forgetpassword.this,Login.class));
                  finish();
               }
               else{
                   Toast.makeText(Forgetpassword.this,"Error"+task.getException(),Toast.LENGTH_SHORT).show();
               }

             }
         });

        }
    }


}