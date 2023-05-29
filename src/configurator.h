#ifndef TAKOKB_CONFIGURATOR_H
#define TAKOKB_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

enum configurator_commands : uint8_t {
    get_protocol_version = 0x01,
};

typedef struct configurator_hid_report {

    enum configurator_commands command_id;

    union {
        uint8_t raw[7];

        struct {
            uint8_t protocol_version;
        } protocol_version;
    };

} configurator_hid_report_t;

_Static_assert(sizeof(configurator_hid_report_t) == 8, "configurator_hid_report must be 8 bytes");

void configurator_receive_hid_report(configurator_hid_report_t *report);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_CONFIGURATOR_H
