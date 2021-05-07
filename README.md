# Auto-Il2cppDumper
This is for helping you get dump.cs from Il2cpp game <br />
hope this will help you >::<

# Important
This project is modifying version of [Riru-Il2cppDumper](https://github.com/Perfare/Riru-Il2CppDumper) <br />
Credit : [Perfare](https://github.com/Perfare)

# Usage 
- build with Android Studio
- decompile the game 
- copy result libnative.so into the decompiled folder apk
- search the main activity of the game
- put this on onCreate function
```smali
 const-string v0, "native-lib"
 
 invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

- re-compile and run it
- wait 10-30 seconds 
- once the dump complete it will auto generate dump.cs in /sdcard/Download
