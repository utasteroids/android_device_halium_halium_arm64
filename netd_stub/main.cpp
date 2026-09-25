// SPDX-License-Identifier: Apache-2.0
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <log/log.h>

#include "NetdStub.h"

int main(int /*argc*/, char* /*argv*/[]) {
    using ::aidl::android::system::net::netd::implementation::NetdStub;

    ABinderProcess_setThreadPoolMaxThreadCount(0);

    const auto netd = ndk::SharedRefBase::make<NetdStub>();

    const std::string instance = std::string(NetdStub::descriptor) + "/default";
    if (AServiceManager_addService(netd->asBinder().get(), instance.c_str()) != STATUS_OK) {
        ALOGE("NetdStub: could not register '%s'", instance.c_str());
        return 1;
    }

    ABinderProcess_joinThreadPool();
    return 0;
}
