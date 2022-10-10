# Auto-Il2cppDumper
Il2CppDumper without Magisk/Zygisk, dump il2cpp data at runtime, can bypass protection, encryption and obfuscation.

This project is based on BrianGIG [Auto-Il2cppDumper](https://github.com/BryanGIG/Auto-Il2cppDumper) which I continue to maintain it

# Usage
This is full auto, no need to put unity version anymore since it's based on Zygisk-Il2cppDumper.

You can download pre-compiled libs [HERE](https://github.com/AndnixSH/Auto-Il2cppDumper/releases) and follow steps below

In config file `jni/Includes/config.h`:

Uncomment `#define UseFakeLib` to use it as root mode

`#define Sleep X`: Default is 2 seconds. Increase if getting issue with dumper, like if not fully dumped

# How to use

### Method 1: Adding Il2CppDumper to APK file
Some games may have APK integrity and signature check. You may need to bypass it before adding Il2CppDumper

- Decompile the game 
- Copy result libil2cppdumper.so into the decompiled folder apk. Make sure only copy same ABIs as the Target App, for example if Target App has only armeabi-v7a, then you should only copy armeabi-v7a
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

### Method 2: Fake libs
This is useful to get around security. Does not need to modify game APK at all but it needs ROOTED device! This is a trick to load our fake libunity.so or libmain.so and load game's renamed lib librealunity.so or librealmain.so. Can't decide which lib? Try libmain.so first as it sometimes work better than libunity.so

Note: Some games does not extract the libs to /data/data. If this is the case, try to use older Android version (9 and below) or modify APK file (See above).

- Make sure you know the architecture of the game and your device before proceed
- Use any file manager app that can access root. Go to /data/data/(package name)/lib
- Rename game's libunity.so to librealunity.so or libmain.so to librealmain.so 
- Put our lib file libunity.so or libmain.so to the lib folder

This will work in APK too for non-rooted devices. You can just open APK as ZIP straight forward, rename libunity.so to librealunity.so, and add fake libunity.so. After that, zipalign and sign the APK. There is no need to re-compile APK at all

### Dumping
- Run the game
- Wait a few seconds. Let the game load into main screen
- Once the dump complete it will auto generate dump.cs in /storage/emulated/0/Android/data/(Package name)/ (Android 10 and below) or /storage/emulated/0/Download (Android 11 and above) without storage permission

### Obfuscated names
Names can't be deobfuscated. Once they are obfuscated/renamed, it can't be reverted back to original, the APK doesn't even have a brain to memorize all original names. Instead, try find older version without obfuscation, or debug the game using GG, frida, gdb, lldb or others. If you can't do any of these, maybe guess the functions and try one by one :P

### Bypass more games?
I'm too noob in Il2Cpp API related, so I can't improve it or bypassing security, and it is not really my thing to bypass. But if you know, feel free to pull request. Issues are still disabled since I forked the project.

# Credits
- Perfare [Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper)
- BrianGIG [Auto-Il2cppDumper](https://github.com/BryanGIG/Auto-Il2cppDumper)