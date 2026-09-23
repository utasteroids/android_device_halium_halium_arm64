// Minimal AIDL android.system.net.netd.INetd implementation for Halium.
//
// Halium ships no real netd server. Vendor RIL/data daemons (e.g. Qualcomm's
// nicmd) block waiting for this interface to register before they will
// proceed with modem data-call setup, so its mere presence matters even
// before any method here is called for real. setIpForwardEnable is wired to
// the actual sysctl since that costs nothing; the OEM-network methods are
// no-ops that report success, matching this tree's existing halium stub
// conventions (see vendor/halium/selinux_stubs).

#pragma once

#include <aidl/android/system/net/netd/BnNetd.h>

namespace aidl::android::system::net::netd::implementation {

class NetdStub : public BnNetd {
  public:
    ndk::ScopedAStatus addInterfaceToOemNetwork(int64_t networkHandle,
                                                 const std::string& ifname) override;
    ndk::ScopedAStatus addRouteToOemNetwork(int64_t networkHandle, const std::string& ifname,
                                             const std::string& destination,
                                             const std::string& nexthop) override;
    ndk::ScopedAStatus createOemNetwork(OemNetwork* _aidl_return) override;
    ndk::ScopedAStatus destroyOemNetwork(int64_t networkHandle) override;
    ndk::ScopedAStatus removeInterfaceFromOemNetwork(int64_t networkHandle,
                                                      const std::string& ifname) override;
    ndk::ScopedAStatus removeRouteFromOemNetwork(int64_t networkHandle, const std::string& ifname,
                                                  const std::string& destination,
                                                  const std::string& nexthop) override;
    ndk::ScopedAStatus setForwardingBetweenInterfaces(const std::string& inputIfName,
                                                       const std::string& outputIfName,
                                                       bool enable) override;
    ndk::ScopedAStatus setIpForwardEnable(bool enable) override;

  private:
    // Handles handed out by createOemNetwork(); starts above 0 since the
    // interface reserves handle 0 to mean "no networks available".
    int64_t mNextHandle = 1;
};

}  // namespace aidl::android::system::net::netd::implementation
