// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fix.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "fix.pb.h"

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

namespace fix {

namespace {

const ::google::protobuf::Descriptor* Tenor_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Tenor_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Datatype_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* Version_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_fix_2eproto() {
  protobuf_AddDesc_fix_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "fix.proto");
  GOOGLE_CHECK(file != NULL);
  Tenor_descriptor_ = file->message_type(0);
  static const int Tenor_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, days_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, weeks_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, months_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, years_),
  };
  Tenor_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Tenor_descriptor_,
      Tenor::default_instance_,
      Tenor_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Tenor, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Tenor));
  Datatype_descriptor_ = file->enum_type(0);
  Version_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_fix_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Tenor_descriptor_, &Tenor::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_fix_2eproto() {
  delete Tenor::default_instance_;
  delete Tenor_reflection_;
}

void protobuf_AddDesc_fix_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::protobuf_AddDesc_google_2fprotobuf_2fdescriptor_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tfix.proto\022\003fix\032 google/protobuf/descri"
    "ptor.proto\"C\n\005Tenor\022\014\n\004days\030\001 \001(\r\022\r\n\005wee"
    "ks\030\002 \001(\r\022\016\n\006months\030\003 \001(\r\022\r\n\005years\030\004 \001(\r*"
    "\200\006\n\010Datatype\022\016\n\004CHAR\020\000\032\004\250\224#\000\022\016\n\004DATA\020\001\032\004"
    "\250\224#\000\022\017\n\005FLOAT\020\002\032\004\250\224#\000\022\r\n\003INT\020\003\032\004\250\224#\000\022\026\n\014"
    "DAY_OF_MONTH\020\004\032\004\250\224#\003\022\024\n\nMONTH_YEAR\020\005\032\004\250\224"
    "#\003\022\r\n\003AMT\020\006\032\004\250\224#\004\022\021\n\007BOOLEAN\020\007\032\004\250\224#\004\022\022\n\010"
    "CURRENCY\020\010\032\004\250\224#\004\022\022\n\010EXCHANGE\020\t\032\004\250\224#\004\022\030\n\016"
    "LOCAL_MKT_DATE\020\n\032\004\250\224#\004\022\037\n\025MULTIPLE_STRIN"
    "G_VALUE\020\013\032\004\250\224#\004\022\017\n\005PRICE\020\014\032\004\250\224#\004\022\026\n\014PRIC"
    "E_OFFSET\020\r\032\004\250\224#\004\022\r\n\003QTY\020\016\032\004\250\224#\004\022\020\n\006STRIN"
    "G\020\017\032\004\250\224#\004\022\027\n\rUTC_TIME_ONLY\020\020\032\004\250\224#\004\022\027\n\rUT"
    "C_TIMESTAMP\020\021\032\004\250\224#\004\022\020\n\006LENGTH\020\022\032\004\250\224#\005\022\026\n"
    "\014NUM_IN_GROUP\020\023\032\004\250\224#\005\022\024\n\nPERCENTAGE\020\024\032\004\250"
    "\224#\005\022\021\n\007SEQ_NUM\020\025\032\004\250\224#\005\022\021\n\007TAG_NUM\020\026\032\004\250\224#"
    "\005\022\021\n\007COUNTRY\020\027\032\004\250\224#\006\022\035\n\023MULTIPLE_CHAR_VA"
    "LUE\020\030\032\004\250\224#\006\022\021\n\007PATTERN\020\031\032\004\250\224#\006\022\032\n\020RESERV"
    "ED1000PLUS\020\032\032\004\250\224#\006\022\031\n\017RESERVED100PLUS\020\033\032"
    "\004\250\224#\006\022\032\n\020RESERVED4000PLUS\020\034\032\004\250\224#\006\022\026\n\014TZ_"
    "TIME_ONLY\020\035\032\004\250\224#\006\022\026\n\014TZ_TIMESTAMP\020\036\032\004\250\224#"
    "\006\022\017\n\005TENOR\020\037\032\004\250\224#\006\022\027\n\rUTC_DATE_ONLY\020 \032\004\250"
    "\224#\006\022\022\n\010XML_DATA\020!\032\004\250\224#\007\022\031\n\010LANGUAGE\020\"\032\013\250"
    "\224#\t\265\224#Z\000\000\000*\243\001\n\007Version\022\013\n\007FIX_2_7\020\000\022\013\n\007F"
    "IX_3_0\020\001\022\013\n\007FIX_4_0\020\002\022\013\n\007FIX_4_1\020\003\022\013\n\007FI"
    "X_4_2\020\004\022\013\n\007FIX_4_3\020\005\022\013\n\007FIX_4_4\020\006\022\013\n\007FIX"
    "_5_0\020\007\022\014\n\010FIXT_1_1\020\010\022\020\n\014FIX_5_0_SP_1\020\t\022\020"
    "\n\014FIX_5_0_SP_2\020\n:0\n\010category\022\034.google.pr"
    "otobuf.FileOptions\030\212\236\003 \001(\t:3\n\010msg_type\022\037"
    ".google.protobuf.MessageOptions\030\331\255\003 \001(\t:"
    ",\n\003tag\022\035.google.protobuf.FieldOptions\030\303\265"
    "\003 \001(\007:<\n\004type\022\035.google.protobuf.FieldOpt"
    "ions\030\304\265\003 \001(\0162\r.fix.Datatype:B\n\013field_add"
    "ed\022\035.google.protobuf.FieldOptions\030\305\265\003 \001("
    "\0162\014.fix.Version:7\n\016field_added_ep\022\035.goog"
    "le.protobuf.FieldOptions\030\306\265\003 \001(\017:G\n\020fiel"
    "d_deprecated\022\035.google.protobuf.FieldOpti"
    "ons\030\307\265\003 \001(\0162\014.fix.Version:7\n\nenum_value\022"
    "!.google.protobuf.EnumValueOptions\030\304\262\004 \001"
    "(\t:E\n\nenum_added\022!.google.protobuf.EnumV"
    "alueOptions\030\305\262\004 \001(\0162\014.fix.Version::\n\renu"
    "m_added_ep\022!.google.protobuf.EnumValueOp"
    "tions\030\306\262\004 \001(\017:J\n\017enum_deprecated\022!.googl"
    "e.protobuf.EnumValueOptions\030\307\262\004 \001(\0162\014.fi"
    "x.VersionB!\n\032org.fixprotocol.componentsB"
    "\003Fix", 1764);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "fix.proto", &protobuf_RegisterTypes);
  Tenor::default_instance_ = new Tenor();
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FileOptions::default_instance(),
    53002, 9, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::MessageOptions::default_instance(),
    55001, 9, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    56003, 7, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    56004, 14, false, false,
    &::fix::Datatype_IsValid);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    56005, 14, false, false,
    &::fix::Version_IsValid);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    56006, 15, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::FieldOptions::default_instance(),
    56007, 14, false, false,
    &::fix::Version_IsValid);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::EnumValueOptions::default_instance(),
    72004, 9, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::EnumValueOptions::default_instance(),
    72005, 14, false, false,
    &::fix::Version_IsValid);
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::EnumValueOptions::default_instance(),
    72006, 15, false, false);
  ::google::protobuf::internal::ExtensionSet::RegisterEnumExtension(
    &::google::protobuf::EnumValueOptions::default_instance(),
    72007, 14, false, false,
    &::fix::Version_IsValid);
  Tenor::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_fix_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_fix_2eproto {
  StaticDescriptorInitializer_fix_2eproto() {
    protobuf_AddDesc_fix_2eproto();
  }
} static_descriptor_initializer_fix_2eproto_;
const ::google::protobuf::EnumDescriptor* Datatype_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Datatype_descriptor_;
}
bool Datatype_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* Version_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Version_descriptor_;
}
bool Version_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Tenor::kDaysFieldNumber;
const int Tenor::kWeeksFieldNumber;
const int Tenor::kMonthsFieldNumber;
const int Tenor::kYearsFieldNumber;
#endif  // !_MSC_VER

Tenor::Tenor()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:fix.Tenor)
}

void Tenor::InitAsDefaultInstance() {
}

Tenor::Tenor(const Tenor& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:fix.Tenor)
}

void Tenor::SharedCtor() {
  _cached_size_ = 0;
  days_ = 0u;
  weeks_ = 0u;
  months_ = 0u;
  years_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Tenor::~Tenor() {
  // @@protoc_insertion_point(destructor:fix.Tenor)
  SharedDtor();
}

void Tenor::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Tenor::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Tenor::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Tenor_descriptor_;
}

const Tenor& Tenor::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_fix_2eproto();
  return *default_instance_;
}

Tenor* Tenor::default_instance_ = NULL;

Tenor* Tenor::New() const {
  return new Tenor;
}

void Tenor::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Tenor*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(days_, years_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Tenor::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:fix.Tenor)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 days = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &days_)));
          set_has_days();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_weeks;
        break;
      }

      // optional uint32 weeks = 2;
      case 2: {
        if (tag == 16) {
         parse_weeks:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &weeks_)));
          set_has_weeks();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_months;
        break;
      }

      // optional uint32 months = 3;
      case 3: {
        if (tag == 24) {
         parse_months:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &months_)));
          set_has_months();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_years;
        break;
      }

      // optional uint32 years = 4;
      case 4: {
        if (tag == 32) {
         parse_years:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &years_)));
          set_has_years();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:fix.Tenor)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:fix.Tenor)
  return false;
#undef DO_
}

void Tenor::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:fix.Tenor)
  // optional uint32 days = 1;
  if (has_days()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->days(), output);
  }

  // optional uint32 weeks = 2;
  if (has_weeks()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->weeks(), output);
  }

  // optional uint32 months = 3;
  if (has_months()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->months(), output);
  }

  // optional uint32 years = 4;
  if (has_years()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->years(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:fix.Tenor)
}

::google::protobuf::uint8* Tenor::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:fix.Tenor)
  // optional uint32 days = 1;
  if (has_days()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->days(), target);
  }

  // optional uint32 weeks = 2;
  if (has_weeks()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->weeks(), target);
  }

  // optional uint32 months = 3;
  if (has_months()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->months(), target);
  }

  // optional uint32 years = 4;
  if (has_years()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->years(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fix.Tenor)
  return target;
}

int Tenor::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 days = 1;
    if (has_days()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->days());
    }

    // optional uint32 weeks = 2;
    if (has_weeks()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->weeks());
    }

    // optional uint32 months = 3;
    if (has_months()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->months());
    }

    // optional uint32 years = 4;
    if (has_years()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->years());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Tenor::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Tenor* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Tenor*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Tenor::MergeFrom(const Tenor& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_days()) {
      set_days(from.days());
    }
    if (from.has_weeks()) {
      set_weeks(from.weeks());
    }
    if (from.has_months()) {
      set_months(from.months());
    }
    if (from.has_years()) {
      set_years(from.years());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Tenor::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Tenor::CopyFrom(const Tenor& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Tenor::IsInitialized() const {

  return true;
}

void Tenor::Swap(Tenor* other) {
  if (other != this) {
    std::swap(days_, other->days_);
    std::swap(weeks_, other->weeks_);
    std::swap(months_, other->months_);
    std::swap(years_, other->years_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Tenor::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Tenor_descriptor_;
  metadata.reflection = Tenor_reflection_;
  return metadata;
}

const ::std::string category_default("");
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FileOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  category(kCategoryFieldNumber, category_default);
const ::std::string msg_type_default("");
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::MessageOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  msg_type(kMsgTypeFieldNumber, msg_type_default);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::uint32 >, 7, false >
  tag(kTagFieldNumber, 0u);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::fix::Datatype, ::fix::Datatype_IsValid>, 14, false >
  type(kTypeFieldNumber, static_cast< ::fix::Datatype >(0));
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::fix::Version, ::fix::Version_IsValid>, 14, false >
  field_added(kFieldAddedFieldNumber, static_cast< ::fix::Version >(0));
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int32 >, 15, false >
  field_added_ep(kFieldAddedEpFieldNumber, 0);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::fix::Version, ::fix::Version_IsValid>, 14, false >
  field_deprecated(kFieldDeprecatedFieldNumber, static_cast< ::fix::Version >(0));
const ::std::string enum_value_default("");
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::StringTypeTraits, 9, false >
  enum_value(kEnumValueFieldNumber, enum_value_default);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::fix::Version, ::fix::Version_IsValid>, 14, false >
  enum_added(kEnumAddedFieldNumber, static_cast< ::fix::Version >(0));
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int32 >, 15, false >
  enum_added_ep(kEnumAddedEpFieldNumber, 0);
::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::EnumValueOptions,
    ::google::protobuf::internal::EnumTypeTraits< ::fix::Version, ::fix::Version_IsValid>, 14, false >
  enum_deprecated(kEnumDeprecatedFieldNumber, static_cast< ::fix::Version >(0));

// @@protoc_insertion_point(namespace_scope)

}  // namespace fix

// @@protoc_insertion_point(global_scope)
