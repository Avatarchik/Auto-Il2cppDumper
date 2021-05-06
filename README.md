# Auto-Il2cppDumper
This is for helping you get dump.cs from Il2cpp game

# Important
this project is modifying version of [Riru-Il2cppDumper](https://github.com/Perfare/Riru-Il2CppDumper) <br />
credit : [Perfare](https://github.com/Perfare)

# Usage 
- build with Android Studio
- decompile the game and search the main activity of the game
- put this on onCreate function
```smali
 const-string v0, "native-lib"
 
 invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```

- compile and run it
- once the dump complete it will auto generate dump.cs in /sdcard/Download
