#include <jni.h>
#include <string>
#include <thread>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include "Il2Cpp/il2cpp_dump.h"
#include "Includes/config.h"
#include "Includes/log.h"

static int GetAndroidApiLevel() {
    char prop_value[PROP_VALUE_MAX];
    __system_property_get("ro.build.version.sdk", prop_value);
    return atoi(prop_value);
}

bool isLibraryLoaded(const char *libraryName) {
    char line[512] = {0};
    FILE *fp = fopen("/proc/self/maps", "rt");
    if (fp != nullptr) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, libraryName)) {
                return true;
            }
        }
        fclose(fp);
    }
    return false;
}

#define libTarget "libil2cpp.so"

void dump_thread() {
    LOGI("Start dumping");
    do {
        sleep(1);
    } while (!isLibraryLoaded(libTarget));

    //Waiting libil2cpp.so fully loaded.
    sleep(Sleep);

    auto il2cpp_handle = dlopen(libTarget, 4);
    char buffer[64];
    int sdk = GetAndroidApiLevel();
    if (sdk >= 30) //Android 11 allows writing to Download folder without permission
        sprintf(buffer, "/storage/emulated/0/Download/");
    else
        sprintf(buffer, "/storage/emulated/0/Android/data/%s", GetPackageName());
    il2cpp_dump(il2cpp_handle, buffer);
}

//The idea from first Il2Cpp Dumper called PokemonGoDumper
//https://github.com/Jumboperson/PokemonGoDumper/blob/master/main.c#L569

void *pLibRealUnity = 0;

typedef jint(JNICALL *CallJNI_OnLoad_t)(JavaVM *vm, void *reserved);

typedef void(JNICALL *CallJNI_OnUnload_t)(JavaVM *vm, void *reserved);

CallJNI_OnLoad_t RealJNIOnLoad = 0;
CallJNI_OnUnload_t RealJNIOnUnload = 0;

#ifdef RootMode

JNIEXPORT jint JNICALL CallJNIOL(
        JavaVM *vm, void *reserved) {
    LOGI("Exec %s", RealLibToLoad);

    std::thread(dump_thread).detach();

    if (!pLibRealUnity)
        pLibRealUnity = dlopen(RealLibToLoad, RTLD_NOW);
    if (!RealJNIOnLoad)
        RealJNIOnLoad = reinterpret_cast<CallJNI_OnLoad_t>(dlsym(pLibRealUnity, "JNI_OnLoad"));
    return RealJNIOnLoad(vm, reserved);
}

JNIEXPORT void JNICALL CallJNIUL(
        JavaVM *vm, void *reserved) {
    if (!pLibRealUnity)
        pLibRealUnity = dlopen(RealLibToLoad, RTLD_NOW);
    if (!RealJNIOnUnload)
        RealJNIOnUnload = reinterpret_cast<CallJNI_OnUnload_t>(dlsym(pLibRealUnity,
                                                                     "JNI_OnUnload"));
    RealJNIOnUnload(vm, reserved);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("Initialize JNI");

    return CallJNIOL(vm, reserved);
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("Unload JNI");

    CallJNIUL(vm, reserved);
}

#else

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    std::thread(dump_thread).detach();
}
#endif
