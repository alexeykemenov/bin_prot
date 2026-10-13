#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>
#include <stddef.h>

#define TELEMETRY_SYNC        0xAAu
#define TELEMETRY_MSG_ID      0x01u
#define TELEMETRY_PAYLOAD_LEN 28u
#define TELEMETRY_PACKET_LEN  (1u + 1u + 1u + TELEMETRY_PAYLOAD_LEN + 1u)

size_t telemetry_pack_pose(uint8_t *out, size_t out_size,
                           float x, float y, float z,
                           float qw, float qx, float qy, float qz);

#endif /* TELEMETRY_H */
