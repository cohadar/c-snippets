#define MAX(a,b) ((a)<(b)?(b):(a))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define GT(a,b) (((a)>(b))-((a)<(b)))

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define FIELD_SIZEOF(t, f) (sizeof(((t*)0)->f))

#define KILO 0x400UL
#define MEGA 0x100000UL
#define GIGA 0x40000000UL
#define TERA 0x10000000000UL
