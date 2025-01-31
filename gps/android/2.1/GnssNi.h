/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 * Not a Contribution
 */
/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ANDROID_HARDWARE_GNSS_V2_0_GNSSNI_H
#define ANDROID_HARDWARE_GNSS_V2_0_GNSSNI_H

#include <android/hardware/gnss/1.0/IGnssNi.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace gnss {
namespace V2_1 {
namespace implementation {

using ::android::hardware::gnss::V1_0::IGnssNi;
using ::android::hardware::gnss::V1_0::IGnssNiCallback;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::sp;

struct Gnss;
struct GnssNi : public IGnssNi {
    GnssNi(Gnss* gnss);
    ~GnssNi() = default;

    /*
     * Methods from ::android::hardware::gnss::V1_0::IGnssNi follow.
     * These declarations were generated from IGnssNi.hal.
     */
    Return<void> setCallback(const sp<IGnssNiCallback>& callback) override;
    Return<void> respond(int32_t notifId,
                         IGnssNiCallback::GnssUserResponseType userResponse) override;

 private:
    struct GnssNiDeathRecipient : hidl_death_recipient {
        GnssNiDeathRecipient(sp<GnssNi> gnssNi) : mGnssNi(gnssNi) {
        }
        ~GnssNiDeathRecipient() = default;
        virtual void serviceDied(uint64_t cookie, const wp<IBase>& who) override;
        sp<GnssNi> mGnssNi;
    };

 private:
    sp<GnssNiDeathRecipient> mGnssNiDeathRecipient = nullptr;
    sp<IGnssNiCallback> mGnssNiCbIface = nullptr;
    Gnss* mGnss = nullptr;
};

}  // namespace implementation
}  // namespace V2_1
}  // namespace gnss
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_GNSS_V2_0_GNSSNI_H
