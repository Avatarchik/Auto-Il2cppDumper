# Auto-Il2cppDumper
This is for helping you get dump.cs from Il2cpp game <br />
hope this will help you >::<

# Important
This project is modifying version of [Riru-Il2cppDumper](https://github.com/Perfare/Riru-Il2CppDumper) <br />
Credit : [Perfare](https://github.com/Perfare)<br />

And BrianGIG [Auto-Il2cppDumper](https://github.com/BryanGIG/Auto-Il2cppDumper)

# Usage
Get unity version by opening any asset file into Notepad++ and any text editor

Edit unity version that match with UnityVersion Compatible list

```
// UnityVersion Compatible list
// 5.3.0f4     | 5.3.0f4 - 5.3.1f1         | v16
// 5.3.2f1     | 5.3.2f1                   | v19
// 5.3.3f1     | 5.3.3f1 - 5.3.4f1         | v20
// 5.3.5f1     | 5.3.5f1                   | v21
// 5.3.6f1     | 5.3.6f1                   | v21
// 5.3.7f1     | 5.3.7f1 - 5.3.8f2         | v21
// 5.4.0f3     | 5.4.0f3                   | v21
// 5.4.1f1     | 5.4.1f1 - 5.4.3f1         | v21
// 5.4.4f1     | 5.4.4f1 - 5.4.6f3         | v21
// 5.5.0f3     | 5.5.0f3                   | v22
// 5.5.1f1     | 5.5.1f1 - 5.5.6f1         | v22
// 5.6.0f3     | 5.6.0f3 - 5.6.7f1         | v23
// 2017.1.0f3  | 2017.1.0f3 - 2017.1.2f1   | v24
// 2017.1.3f1  | 2017.1.3f1 - 2017.1.5f1   | v24
// 2017.2.0f3  | 2017.2.0f3                | v24
// 2017.2.1f1  | 2017.2.1f1 - 2017.4.40f1  | v24
// 2018.1.0f2  | 2018.1.0f2 - 2018.1.9f2   | v24
// 2018.2.0f2  | 2018.2.0f2 - 2018.2.21f1  | v24
// 2018.3.0f2  | 2018.3.0f2 - 2018.3.7f1   | v24.1
// 2018.3.8f1  | 2018.3.8f1 - 2018.4.36f1  | v24.1
// 2019.1.0f2  | 2019.1.0f2 - 2019.2.21f1  | v24.2
// 2019.3.0f6  | 2019.3.0f6 - 2019.3.6f1   | v24.2
// 2019.3.7f1  | 2019.3.7f1 - 2019.4.14f1  | v24.3
// 2019.4.15f1 | 2019.4.15f1 - 2019.4.20f1 | v24.4
// 2019.4.21f1 | 2019.4.21f1 - 2019.4.29f1 | v24.5
// 2020.1.0f1  | 2020.1.0f1 - 2020.1.10f1  | v24.3
// 2020.1.11f1 | 2020.1.11f1 - 2020.1.17f1 | v24.4
// 2020.2.0f1  | 2020.2.0f1 - 2020.2.3f1   | v27
// 2020.2.4f1  | 2020.2.4f1 - 2020.3.15f2  | v27.1
// 2021.1.0f1  | 2021.1.0f1 - 2021.1.16f1  | v27.2
```

# Non root method
This method requires to modify game APK. You may need to bypass APK integrity and sig check if you want to use this method

- Build APK with Android Studio
- Decompile app-debug.apk
- Decompile the game 
- Copy result libnative.so into the decompiled folder apk
- Search the main activity of the game
- Put this on onCreate function
```smali
 const-string v0, "native-lib"
 
 invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

- Re-compile and run it
- Wait 10-30 seconds 
- Once the dump complete it will auto generate dump.cs in /sdcard/Download

# Root method
This is useful to get around security. Does not need to modify game APK at all! This is a trick to load our fake libunity.so and load game's renamed lib librealunity.so

Note: Some games does not store the libs in /data/data, you would be unable to do this trick!

- Build APK with Android Studio
- Extract libnative-lib.so from app-debug.apk. Make sure you know what architecture the game is using before proceed
- Rename our lib to libunity.so
- On rooted device/VM, use any file manager app that can access root. Go to /data/data/(package name)/lib
- IMPORTANT! Rename game's libunity.so to librealunity.so
- Put our lib file libunity.so
- Run the game
- Wait 10-30 seconds
- Once the dump complete it will auto generate dump.cs in /sdcard/Download