//
// Created by ikvarxt on 10/25/2024.
//

#include "FbJniRunner.h"
#include "TestHybridClass.h"
#include <fbjni/fbjni.h>
#include <jni.h>

using namespace facebook::jni;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *) {
  return initialize(vm, [] {
    facebook::jni::log_::loge("JNI_OnLoad", "register native methods");
    FbJniRunner::registerNatives();
    TestHybridClass::registerNatives();
  });
}
