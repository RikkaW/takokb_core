#ifndef TAKOKB_CONFIGURATOR_H
#define TAKOKB_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <takokb.h>

void configurator_receive_hid_report(configurator_hid_report_t *report);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_CONFIGURATOR_H
