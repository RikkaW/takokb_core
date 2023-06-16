#ifndef TAKOKB_CONFIGURATOR_H
#define TAKOKB_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <takokb.h>

void configurator_receive_report(takokb_configurator_report_t *report, size_t size);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_CONFIGURATOR_H
