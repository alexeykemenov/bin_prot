#include "telemetry.h"
#include <string.h>

static void put_f32_le(uint8_t *p, float f)
{
    uint32_t u;
    memcpy(&u, &f, sizeof(u));
    p[0] = (uint8_t)( u        & 0xFFu);
    p[1] = (uint8_t)((u >>  8) & 0xFFu);
    p[2] = (uint8_t)((u >> 16) & 0xFFu);
    p[3] = (uint8_t)((u >> 24) & 0xFFu);
}

size_t telemetry_pack_pose(uint8_t *out, size_t out_size,
                           float x, float y, float z,
                           float qw, float qx, float qy, float qz)
{
    if (!out || out_size < TELEMETRY_PACKET_LEN) return 0;

    out[0] = TELEMETRY_SYNC;
    out[1] = TELEMETRY_MSG_ID;
    out[2] = TELEMETRY_PAYLOAD_LEN;

    uint8_t *p = &out[3];
    put_f32_le(p +  0, x);
    put_f32_le(p +  4, y);
    put_f32_le(p +  8, z);
    put_f32_le(p + 12, qw);
    put_f32_le(p + 16, qx);
    put_f32_le(p + 20, qy);
    put_f32_le(p + 24, qz);

    uint8_t crc = (uint8_t)(TELEMETRY_MSG_ID ^ TELEMETRY_PAYLOAD_LEN);
    for (size_t i = 0; i < TELEMETRY_PAYLOAD_LEN; ++i) crc ^= p[i];
    out[3 + TELEMETRY_PAYLOAD_LEN] = crc;

    return TELEMETRY_PACKET_LEN;
}
