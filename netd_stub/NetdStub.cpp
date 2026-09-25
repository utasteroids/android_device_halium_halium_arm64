// SPDX-License-Identifier: Apache-2.0
#include "NetdStub.h"

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

ndk::ScopedAStatus NetdStub::setIpForwardEnable(bool /*enable*/) {
    // IP forwarding is managed on the host (NetworkManager), not here.
    return ndk::ScopedAStatus::ok();
}

}  // namespace aidl::android::system::net::netd::implementation
