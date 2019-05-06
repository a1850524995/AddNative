package com.chinaso.addnative;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    public static final String TAG = "MainActivity";
    Button staticRegister ;
    Button dynamicRegister ;

    TextView tv ;
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        staticRegister = findViewById(R.id.static_register);
        dynamicRegister = findViewById(R.id.dynamic_register);
        staticRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(Register.staticRegister());
            }
        });
        dynamicRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tv.setText(Register.dynamicRegister());
            }
        });

    }

    public static void methodCalledByJni(String msgFromJNI) {
        Log.e(TAG, msgFromJNI);
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
