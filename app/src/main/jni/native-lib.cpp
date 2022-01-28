#include <jni.h>
#include <string>
#include <pthread.h>
#include <dlfcn.h>
#include <unistd.h>
#include "Includes/il2cpp_dump.h"
#include "Includes/game.h"
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

void *hack_thread(void *) {
    do {
        sleep(1);
    } while (!isLibraryLoaded(libTarget));

    //Waiting libil2cpp.so fully loaded.
    sleep(3);

    auto il2cpp_handle = dlopen(libTarget, 4);
    il2cpp_dump(il2cpp_handle, "/storage/emulated/0/Download");
    return nullptr;
}

//The idea from first Il2Cpp Dumper called PokemonGoDumper
//https://github.com/Jumboperson/PokemonGoDumper/blob/master/main.c#L569

int iBeenInjected = 0;
void* pLibRealUnity = 0;
typedef void (*UnitySendMessage_t)(const char* ob, const char* method, const char* msg);
typedef jint(JNICALL* CallJNI_OnLoad_t)(JavaVM* vm, void* reserved);
typedef void(JNICALL* CallJNI_OnUnload_t)(JavaVM* vm, void* reserved);

UnitySendMessage_t RealUSM = 0;
CallJNI_OnLoad_t RealJNIOnLoad = 0;
CallJNI_OnUnload_t RealJNIOnUnload = 0;
void* libdlopen = 0;

#ifdef RootMode
JNIEXPORT jint JNICALL CallJNIOL(
        JavaVM* vm, void* reserved)
{
    LOGI("Loading librealunity.so");
    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealunity.so", RTLD_NOW);
    if (!RealJNIOnLoad)
        RealJNIOnLoad = reinterpret_cast<CallJNI_OnLoad_t>(dlsym(pLibRealUnity, "JNI_OnLoad"));
    return RealJNIOnLoad(vm, reserved);
}

JNIEXPORT void JNICALL CallJNIUL(
        JavaVM* vm, void* reserved)
{
    if (!pLibRealUnity)
        pLibRealUnity = dlopen("librealunity.so", RTLD_NOW);
    if (!RealJNIOnUnload)
        RealJNIOnUnload = reinterpret_cast<CallJNI_OnUnload_t>(dlsym(pLibRealUnity,
                                                                          "JNI_OnUnload"));
    RealJNIOnUnload(vm, reserved);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    if (!iBeenInjected)
    {
        LOGI("Loading dumper");
        pthread_t ptid;
        pthread_create(&ptid, nullptr, hack_thread, nullptr);
    }
    return CallJNIOL(vm, reserved);
}
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved)
{
    if (!iBeenInjected)
    {
        pthread_t ptid;
        pthread_create(&ptid, nullptr, hack_thread, nullptr);
    }
    CallJNIUL(vm, reserved);
}
#else

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, nullptr, hack_thread, nullptr);
}

#endif
