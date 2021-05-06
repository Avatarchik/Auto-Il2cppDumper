# Auto-Il2cppDumper
This is for helping you get dump.cs from Il2cpp game

# Important
Only for experienced android game modder 

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
