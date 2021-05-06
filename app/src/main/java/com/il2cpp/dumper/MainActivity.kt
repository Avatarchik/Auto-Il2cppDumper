package com.il2cpp.dumper

import android.app.Activity
import android.os.Bundle
import android.os.PersistableBundle

class MainActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?, persistentState: PersistableBundle?) {
        super.onCreate(savedInstanceState, persistentState)
        setContentView(R.layout.activity_main)
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}