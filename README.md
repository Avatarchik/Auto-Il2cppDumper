# Auto-Il2cppDumper
Il2CppDumper without Magisk/Zygisk, dump il2cpp data at runtime, can bypass protection, encryption and obfuscation.

This project is based on BrianGIG [Auto-Il2cppDumper](https://github.com/BryanGIG/Auto-Il2cppDumper) which I continue to maintain it

# Usage
This is full auto, no need to put unity version anymore since it's based on Zygisk-Il2cppDumper.

You can download pre-compiled libs [HERE](https://github.com/AndnixSH/Auto-Il2cppDumper/releases) and follow steps below

###`jni/Includes/config.h`

Uncomment `#define RootMode` to use it as root mode

`#define Sleep X`: Default is 2 seconds. Increase if getting issue with dumper, like if not fully dumped

# How to use

### Non root method
This method requires to modify APK. You may need to bypass APK integrity and signature check if you want to use this method

- Build APK with Android Studio
- Decompile app-debug.apk using apktool.jar, APK Tool GUI or any other tools of your choice
- Decompile the game 
- Copy result il2cppdumper.so into the decompiled folder apk. Make sure only copy same ABIs as the Target App, for example if Target App has only armeabi-v7a, then you should only copy armeabi-v7a
- Search the main activity in AndroidManifest.xml. Example: com.gameloft.android.XamarinMainActivity

```xml
<activity android:configChanges="density|fontScale|keyboard|keyboardHidden|layoutDirection|locale|mcc|mnc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|touchscreen|uiMode" android:label="@string/icon_label" android:launchMode="singleTop" android:multiprocess="false" android:name="com.gameloft.android.XamarinMainActivity" android:resizeableActivity="false" android:screenOrientation="sensorLandscape" android:theme="@style/Theme.acp.notitlebar.fullscreen">
    <intent-filter>
        <action android:name="android.intent.action.MAIN"/>
        <category android:name="android.intent.category.LAUNCHER"/>
    </intent-filter>
</activity>
```

- Locate the smali file of main activity
- Copy and paste this smali code into onCreate function

```smali
 const-string v0, "il2cppdumper"
 
 invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

Like

```smali
.method protected onCreate(Landroid/os/Bundle;)V
    .locals 2

    const-string v0, "il2cppdumper"
 
    invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

    whatever code below
```

- Re-compile, zipalign and sign the APK
- Install APK

### Root method
This is useful to get around security. Does not need to modify game APK at all! This is a trick to load our fake libunity.so and load game's renamed lib librealunity.so

Note: Some games does not extract the libs in /data/data. In this case, try to use older Android version or modify APK file (See above).

- Build APK with Android Studio
- Extract libil2cppdumper.so from app-debug.apk. Make sure you know the architecture of the game and your device before proceed
- Rename our lib to libunity.so
- On rooted device/VM, use any file manager app that can access root. Go to /data/data/(package name)/lib
- IMPORTANT! Rename game's libunity.so to librealunity.so
- Put our lib file libunity.so

### Dumping
- Run the game
- Wait a few seconds. Let the game load into main screen
- Once the dump complete it will auto generate dump.cs in /storage/emulated/0/Android/data/(Package name)/ (Android 10 and below) or /storage/emulated/0/Download (Android 11 and above) without storage permission

# Credits
- Perfare [Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper)
- BrianGIG [Auto-Il2cppDumper](https://github.com/BryanGIG/Auto-Il2cppDumper)