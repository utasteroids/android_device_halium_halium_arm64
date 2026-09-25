// SPDX-License-Identifier: Apache-2.0
#include "NetdStub.h"

#include <log/log.h>

#include <cstdio>

namespace aidl::android::system::net::netd::implementation {

ndk::ScopedAStatus NetdStub::addInterfaceToOemNetwork(int64_t /*networkHandle*/,
                                                        const std::string& /*ifname*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::addRouteToOemNetwork(int64_t /*networkHandle*/,
                                                   const std::string& /*ifname*/,
                                                   const std::string& /*destination*/,
                                                   const std::string& /*nexthop*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::createOemNetwork(OemNetwork* _aidl_return) {
    _aidl_return->networkHandle = mNextHandle++;
    _aidl_return->packetMark = 0;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::destroyOemNetwork(int64_t /*networkHandle*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::removeInterfaceFromOemNetwork(int64_t /*networkHandle*/,
                                                             const std::string& /*ifname*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::removeRouteFromOemNetwork(int64_t /*networkHandle*/,
                                                         const std::string& /*ifname*/,
                                                         const std::string& /*destination*/,
                                                         const std::string& /*nexthop*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::setForwardingBetweenInterfaces(const std::string& /*inputIfName*/,
                                                              const std::string& /*outputIfName*/,
                                                              bool /*enable*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus NetdStub::setIpForwardEnable(bool enable) {
    // The one method here with an effect independent of the OEM-network
    // handles above: flip the actual kernel forwarding sysctl.
    FILE* f = fopen("/proc/sys/net/ipv4/ip_forward", "we");
    if (f == nullptr) {
        ALOGE("NetdStub: failed to open /proc/sys/net/ipv4/ip_forward: %m");
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    const char* value = enable ? "1" : "0";
    const bool ok = fputs(value, f) >= 0;
    fclose(f);
    if (!ok) {
        ALOGE("NetdStub: failed to write ip_forward=%s", value);
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    return ndk::ScopedAStatus::ok();
}

}  // namespace aidl::android::system::net::netd::implementation
