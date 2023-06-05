package com.il2cpp.dumper;

import android.app.Activity;
import android.os.Bundle;


public class MainActivity extends Activity {
    static {
        System.loadLibrary("il2cppdumper");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
