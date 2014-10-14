#ifndef __NATIVEVALUE_H
#define __NATIVEVALUE_H

#include <cstdint>

union NativeValue {
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	char str[128];
};

#endif //__NATIVEVALUE_H