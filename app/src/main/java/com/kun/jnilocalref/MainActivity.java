package com.kun.jnilocalref;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        createNativeLocalRef(1000);
//        createNativeLocalRef2(1000);
//        createNativeLocalRef3(1000);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void createNativeLocalRef(int count);

    public native void createNativeLocalRef1(int count);

    public native void createNativeLocalRef2(int count);

    public native void createNativeLocalRef3(int count);

    public void onClick(View view) {
        createNativeLocalRef(1000);
    }

    public void onClick1(View view) {
        createNativeLocalRef1(1000);
    }

    public void onClick2(View view) {
        createNativeLocalRef2(1000);
    }

    public void onClick3(View view) {
        createNativeLocalRef3(1000);
    }
}
