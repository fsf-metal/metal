// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: meta.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "meta.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace meta {

namespace {

const ::google::protobuf::EnumDescriptor* TimeUnit_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Epoch_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_meta_2eproto() {
  protobuf_AddDesc_meta_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "meta.proto");
  GOOGLE_CHECK(file != NULL);
  TimeUnit_descriptor_ = file->enum_type(0);
  Epoch_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_meta_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_meta_2eproto() {
}

void protobuf_AddDesc_meta_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::protobuf_AddDesc_google_2fprotobuf_2fdescriptor_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nmeta.proto\022\004meta\032 google/protobuf/desc"
    "riptor.proto*\243\001\n\010TimeUnit\022\022\n\016TIME_UNIT_D"
    "AYS\020\000\022\025\n\021TIME_UNIT_SECONDS\020\001\022\032\n\026TIME_UNI"
    "T_MILLISECONDS\020\002\022\032\n\026TIME_UNIT_MICROSECON"
    "DS\020\003\022\031\n\025TIME_UNIT_NANOSECONDS\020\004\022\031\n\025TIME_"
    "UNIT_PICOSECONDS\020\005*K\n\005Epoch\022\022\n\016EPOCH_MID"
    "NIGHT\020\000\022\016\n\nEPOCH_UNIX\020\001\022\016\n\nEPOCH_1900\020\002\022"
    "\016\n\nEPOCH_2000\020\003:B\n\ttime_unit\022\035.google.pr"
    "otobuf.FieldOptions\030\271\216\003 \001(\0162\016.meta.TimeU"
    "nit:1\n\010exponent\022\035.google.protobuf.FieldO"
    "ptions\030\273\216\003 \001(\017:3\n\nmin_length\022\035.google.pr"
    "otobuf.FieldOptions\030\274\216\003 \001(\007:3\n\nmax_lengt"
    "h\022\035.google.protobuf.FieldOptions\030\275\216\003 \001(\007"
    ":2\n\tmin_value\022\035.google.protobuf.FieldOpt"
    "ions\030\276\216\003 \001(\020:2\n\tmax_value\022\035.google.proto"
    "buf.FieldOptions\030\277\216\003 \001(\020B\"\n\032org.fixproto"
    "col.componentsB\004Meta", 660);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "meta.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51001, 14, false, false,
    &::meta::TimeUnit_IsValid);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51003, 15, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51004, 7, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51005, 7, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51006, 16, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    51007, 16, false, false);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_meta_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_meta_2eproto {
  StaticDescriptorInitializer_meta_2eproto() {
    protobuf_AddDesc_meta_2eproto();
  }
} static_descriptor_initializer_meta_2eproto_;
const ::google::protobuf::EnumDescriptor* TimeUnit_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TimeUnit_descriptor_;
}
bool TimeUnit_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* Epoch_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Epoch_descriptor_;
}
bool Epoch_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::meta::TimeUnit, ::meta::TimeUnit_IsValid>, 14, false >
  time_unit(kTimeUnitFieldNumber, static_cast< ::meta::TimeUnit >(0));
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int32 >, 15, false >
  exponent(kExponentFieldNumber, 0);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::uint32 >, 7, false >
  min_length(kMinLengthFieldNumber, 0u);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::uint32 >, 7, false >
  max_length(kMaxLengthFieldNumber, 0u);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int64 >, 16, false >
  min_value(kMinValueFieldNumber, GOOGLE_LONGLONG(0));
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int64 >, 16, false >
  max_value(kMaxValueFieldNumber, GOOGLE_LONGLONG(0));

// @@protoc_insertion_point(namespace_scope)

}  // namespace meta

// @@protoc_insertion_point(global_scope)
