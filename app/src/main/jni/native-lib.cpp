#include <jni.h>
#include <string>
#include <thread>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include "Il2Cpp/il2cpp_dump.h"
#include "Includes/config.h"
#include "Includes/log.h"

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
    LOGI("Lib loaded");
    do {
        sleep(1);
    } while (!isLibraryLoaded(libTarget));

    //Waiting libil2cpp.so fully loaded.
    LOGI("Waiting in %d...", Sleep);
    sleep(Sleep);

    auto il2cpp_handle = dlopen(libTarget, 4);
    LOGI("Start dumping");

    auto androidDataPath = std::string("/storage/emulated/0/Android/data/").append(
            GetPackageName()).append("/").append(GetPackageName()).append("-dump.cs");

    il2cpp_api_init(il2cpp_handle);
    il2cpp_dump(androidDataPath.c_str());
}

//The idea from first Il2Cpp Dumper called PokemonGoDumper
//https://github.com/Jumboperson/PokemonGoDumper/blob/master/main.c#L569

void *pLibRealUnity = 0;

typedef jint(JNICALL *CallJNI_OnLoad_t)(JavaVM *vm, void *reserved);

typedef void(JNICALL *CallJNI_OnUnload_t)(JavaVM *vm, void *reserved);

CallJNI_OnLoad_t RealJNIOnLoad = 0;
CallJNI_OnUnload_t RealJNIOnUnload = 0;

#ifdef UseFakeLib

JNIEXPORT jint JNICALL CallJNIOL(JavaVM *vm, void *reserved) {
    LOGI("OnLoad called");

    std::thread(dump_thread).detach();

    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealmain.so", RTLD_NOW);
    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealunity.so", RTLD_NOW);
    if (!RealJNIOnLoad)
        RealJNIOnLoad = reinterpret_cast<CallJNI_OnLoad_t>(dlsym(pLibRealUnity, "JNI_OnLoad"));
    return RealJNIOnLoad(vm, reserved);
}

JNIEXPORT void JNICALL CallJNIUL(JavaVM *vm, void *reserved) {
    LOGI("OnUnload called");

    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealmain.so", RTLD_NOW);
    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealunity.so", RTLD_NOW);
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
