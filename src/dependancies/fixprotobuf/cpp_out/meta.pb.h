// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: meta.proto

#ifndef PROTOBUF_meta_2eproto__INCLUDED
#define PROTOBUF_meta_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include "google/protobuf/descriptor.pb.h"
// @@protoc_insertion_point(includes)

namespace meta {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_meta_2eproto();
void protobuf_AssignDesc_meta_2eproto();
void protobuf_ShutdownFile_meta_2eproto();


enum TimeUnit {
  TIME_UNIT_DAYS = 0,
  TIME_UNIT_SECONDS = 1,
  TIME_UNIT_MILLISECONDS = 2,
  TIME_UNIT_MICROSECONDS = 3,
  TIME_UNIT_NANOSECONDS = 4,
  TIME_UNIT_PICOSECONDS = 5
};
bool TimeUnit_IsValid(int value);
const TimeUnit TimeUnit_MIN = TIME_UNIT_DAYS;
const TimeUnit TimeUnit_MAX = TIME_UNIT_PICOSECONDS;
const int TimeUnit_ARRAYSIZE = TimeUnit_MAX + 1;

const ::google::protobuf::EnumDescriptor* TimeUnit_descriptor();
inline const ::std::string& TimeUnit_Name(TimeUnit value) {
  return ::google::protobuf::internal::NameOfEnum(
    TimeUnit_descriptor(), value);
}
inline bool TimeUnit_Parse(
    const ::std::string& name, TimeUnit* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TimeUnit>(
    TimeUnit_descriptor(), name, value);
}
enum Epoch {
  EPOCH_MIDNIGHT = 0,
  EPOCH_UNIX = 1,
  EPOCH_1900 = 2,
  EPOCH_2000 = 3
};
bool Epoch_IsValid(int value);
const Epoch Epoch_MIN = EPOCH_MIDNIGHT;
const Epoch Epoch_MAX = EPOCH_2000;
const int Epoch_ARRAYSIZE = Epoch_MAX + 1;

const ::google::protobuf::EnumDescriptor* Epoch_descriptor();
inline const ::std::string& Epoch_Name(Epoch value) {
  return ::google::protobuf::internal::NameOfEnum(
    Epoch_descriptor(), value);
}
inline bool Epoch_Parse(
    const ::std::string& name, Epoch* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Epoch>(
    Epoch_descriptor(), name, value);
}
// ===================================================================


// ===================================================================

static const int kTimeUnitFieldNumber = 51001;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::meta::TimeUnit, ::meta::TimeUnit_IsValid>, 14, false >
  time_unit;
static const int kExponentFieldNumber = 51003;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int32 >, 15, false >
  exponent;
static const int kMinLengthFieldNumber = 51004;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::uint32 >, 7, false >
  min_length;
static const int kMaxLengthFieldNumber = 51005;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::uint32 >, 7, false >
  max_length;
static const int kMinValueFieldNumber = 51006;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int64 >, 16, false >
  min_value;
static const int kMaxValueFieldNumber = 51007;
extern ::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int64 >, 16, false >
  max_value;

// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace meta

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::meta::TimeUnit>() {
  return ::meta::TimeUnit_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::meta::Epoch>() {
  return ::meta::Epoch_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_meta_2eproto__INCLUDED
