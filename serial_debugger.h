#ifndef SERIAL_DEBUGGER_H
#define SERIAL_DEBUGGER_H

#define DO_DEBUG        (1)
#define UNUSED          __attribute__((unused))

UNUSED static void serial_init() {
    #if DO_DEBUG
    Serial.begin(9600);    
    #endif
}

UNUSED static void serial_print(UNUSED const char *c) {
    #if DO_DEBUG
    Serial.print(c);
    #endif
}

UNUSED static  void serial_println(UNUSED const char *c) {
    #if DO_DEBUG
    Serial.println(c);
    #endif
}

template <typename T>
UNUSED static void serial_print_val(UNUSED const char *c, __attribute__((unused))T val) {
    #if DO_DEBUG
    Serial.print(c);
    Serial.print(val);
    #endif
}

template <typename T>
UNUSED static void serial_println_val(UNUSED const char *c, __attribute__((unused))T val) {
    #if DO_DEBUG
    Serial.print(c);
    Serial.println(val);
    #endif
}

#endif

