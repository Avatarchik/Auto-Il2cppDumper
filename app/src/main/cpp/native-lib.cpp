#include <jni.h>
#include <string>
#include <pthread.h>
#include <dlfcn.h>
#include "Includes/il2cpp_dump.h"

void *hack_thread(void*){
    auto il2cpp_handle = dlopen("libil2cpp.so",4);
    il2cpp_dump(il2cpp_handle, "/sdcard/Download");
    return nullptr;
}

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, nullptr, hack_thread, nullptr);
}