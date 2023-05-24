#ifndef TAKOKB_COMMON_H
#define TAKOKB_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

extern int test_step;
extern bool success;

#define PRESS(row, colum) ((matrix)[(row)] |= (1U << (colum)))
#define RELEASE(row, colum) ((matrix)[(row)] &= ~(1U << (colum)))

void test_tick(void);

void test_next_step(void);

void assert_active_layer_equals(int layer);

void assert_keycode_equals(report_keyboard_t *report, int index, uint8_t keycode);

void assert_equals(bool changed, bool b, const char *message);

#ifdef __cplusplus
}
#endif

#endif //TAKOKB_COMMON_H
