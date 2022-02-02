// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageType.proto

#include "MessageType.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace ipc {
constexpr Header::Header(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : size_(0u){}
struct HeaderDefaultTypeInternal {
  constexpr HeaderDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HeaderDefaultTypeInternal() {}
  union {
    Header _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HeaderDefaultTypeInternal _Header_default_instance_;
constexpr Payload::Payload(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : value_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , length_(0u){}
struct PayloadDefaultTypeInternal {
  constexpr PayloadDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PayloadDefaultTypeInternal() {}
  union {
    Payload _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PayloadDefaultTypeInternal _Payload_default_instance_;
constexpr Package::Package(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : header_(nullptr)
  , payload_(nullptr){}
struct PackageDefaultTypeInternal {
  constexpr PackageDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PackageDefaultTypeInternal() {}
  union {
    Package _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PackageDefaultTypeInternal _Package_default_instance_;
}  // namespace ipc
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_MessageType_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_MessageType_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_MessageType_2eproto = nullptr;

const uint32_t TableStruct_MessageType_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ipc::Header, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ipc::Header, size_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ipc::Payload, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ipc::Payload, length_),
  PROTOBUF_FIELD_OFFSET(::ipc::Payload, value_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ipc::Package, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ipc::Package, header_),
  PROTOBUF_FIELD_OFFSET(::ipc::Package, payload_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::ipc::Header)},
  { 7, -1, -1, sizeof(::ipc::Payload)},
  { 15, -1, -1, sizeof(::ipc::Package)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ipc::_Header_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ipc::_Payload_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ipc::_Package_default_instance_),
};

const char descriptor_table_protodef_MessageType_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021MessageType.proto\022\003ipc\"\026\n\006Header\022\014\n\004si"
  "ze\030\001 \001(\007\"(\n\007Payload\022\016\n\006length\030\001 \001(\007\022\r\n\005v"
  "alue\030\002 \001(\014\"E\n\007Package\022\033\n\006header\030\001 \001(\0132\013."
  "ipc.Header\022\035\n\007payload\030\002 \001(\0132\014.ipc.Payloa"
  "db\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_MessageType_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_MessageType_2eproto = {
  false, false, 169, descriptor_table_protodef_MessageType_2eproto, "MessageType.proto", 
  &descriptor_table_MessageType_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_MessageType_2eproto::offsets,
  file_level_metadata_MessageType_2eproto, file_level_enum_descriptors_MessageType_2eproto, file_level_service_descriptors_MessageType_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_MessageType_2eproto_getter() {
  return &descriptor_table_MessageType_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_MessageType_2eproto(&descriptor_table_MessageType_2eproto);
namespace ipc {

// ===================================================================

class Header::_Internal {
 public:
};

Header::Header(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ipc.Header)
}
Header::Header(const Header& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  size_ = from.size_;
  // @@protoc_insertion_point(copy_constructor:ipc.Header)
}

inline void Header::SharedCtor() {
size_ = 0u;
}

Header::~Header() {
  // @@protoc_insertion_point(destructor:ipc.Header)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Header::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Header::ArenaDtor(void* object) {
  Header* _this = reinterpret_cast< Header* >(object);
  (void)_this;
}
void Header::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Header::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Header::Clear() {
// @@protoc_insertion_point(message_clear_start:ipc.Header)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  size_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Header::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // fixed32 size = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 13)) {
          size_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<uint32_t>(ptr);
          ptr += sizeof(uint32_t);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Header::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ipc.Header)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // fixed32 size = 1;
  if (this->_internal_size() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFixed32ToArray(1, this->_internal_size(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ipc.Header)
  return target;
}

size_t Header::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ipc.Header)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // fixed32 size = 1;
  if (this->_internal_size() != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Header::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Header::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Header::GetClassData() const { return &_class_data_; }

void Header::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Header *>(to)->MergeFrom(
      static_cast<const Header &>(from));
}


void Header::MergeFrom(const Header& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ipc.Header)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_size() != 0) {
    _internal_set_size(from._internal_size());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Header::CopyFrom(const Header& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ipc.Header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Header::IsInitialized() const {
  return true;
}

void Header::InternalSwap(Header* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(size_, other->size_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Header::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_MessageType_2eproto_getter, &descriptor_table_MessageType_2eproto_once,
      file_level_metadata_MessageType_2eproto[0]);
}

// ===================================================================

class Payload::_Internal {
 public:
};

Payload::Payload(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ipc.Payload)
}
Payload::Payload(const Payload& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    value_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_value().empty()) {
    value_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_value(), 
      GetArenaForAllocation());
  }
  length_ = from.length_;
  // @@protoc_insertion_point(copy_constructor:ipc.Payload)
}

inline void Payload::SharedCtor() {
value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  value_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
length_ = 0u;
}

Payload::~Payload() {
  // @@protoc_insertion_point(destructor:ipc.Payload)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Payload::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  value_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Payload::ArenaDtor(void* object) {
  Payload* _this = reinterpret_cast< Payload* >(object);
  (void)_this;
}
void Payload::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Payload::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Payload::Clear() {
// @@protoc_insertion_point(message_clear_start:ipc.Payload)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  value_.ClearToEmpty();
  length_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Payload::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // fixed32 length = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 13)) {
          length_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<uint32_t>(ptr);
          ptr += sizeof(uint32_t);
        } else
          goto handle_unusual;
        continue;
      // bytes value = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Payload::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ipc.Payload)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // fixed32 length = 1;
  if (this->_internal_length() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFixed32ToArray(1, this->_internal_length(), target);
  }

  // bytes value = 2;
  if (!this->_internal_value().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ipc.Payload)
  return target;
}

size_t Payload::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ipc.Payload)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes value = 2;
  if (!this->_internal_value().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_value());
  }

  // fixed32 length = 1;
  if (this->_internal_length() != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Payload::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Payload::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Payload::GetClassData() const { return &_class_data_; }

void Payload::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Payload *>(to)->MergeFrom(
      static_cast<const Payload &>(from));
}


void Payload::MergeFrom(const Payload& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ipc.Payload)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_value().empty()) {
    _internal_set_value(from._internal_value());
  }
  if (from._internal_length() != 0) {
    _internal_set_length(from._internal_length());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Payload::CopyFrom(const Payload& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ipc.Payload)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Payload::IsInitialized() const {
  return true;
}

void Payload::InternalSwap(Payload* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &value_, lhs_arena,
      &other->value_, rhs_arena
  );
  swap(length_, other->length_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Payload::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_MessageType_2eproto_getter, &descriptor_table_MessageType_2eproto_once,
      file_level_metadata_MessageType_2eproto[1]);
}

// ===================================================================

class Package::_Internal {
 public:
  static const ::ipc::Header& header(const Package* msg);
  static const ::ipc::Payload& payload(const Package* msg);
};

const ::ipc::Header&
Package::_Internal::header(const Package* msg) {
  return *msg->header_;
}
const ::ipc::Payload&
Package::_Internal::payload(const Package* msg) {
  return *msg->payload_;
}
Package::Package(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ipc.Package)
}
Package::Package(const Package& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_header()) {
    header_ = new ::ipc::Header(*from.header_);
  } else {
    header_ = nullptr;
  }
  if (from._internal_has_payload()) {
    payload_ = new ::ipc::Payload(*from.payload_);
  } else {
    payload_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:ipc.Package)
}

inline void Package::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&header_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&payload_) -
    reinterpret_cast<char*>(&header_)) + sizeof(payload_));
}

Package::~Package() {
  // @@protoc_insertion_point(destructor:ipc.Package)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Package::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete header_;
  if (this != internal_default_instance()) delete payload_;
}

void Package::ArenaDtor(void* object) {
  Package* _this = reinterpret_cast< Package* >(object);
  (void)_this;
}
void Package::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Package::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Package::Clear() {
// @@protoc_insertion_point(message_clear_start:ipc.Package)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaForAllocation() == nullptr && header_ != nullptr) {
    delete header_;
  }
  header_ = nullptr;
  if (GetArenaForAllocation() == nullptr && payload_ != nullptr) {
    delete payload_;
  }
  payload_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Package::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .ipc.Header header = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_header(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .ipc.Payload payload = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_payload(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Package::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ipc.Package)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .ipc.Header header = 1;
  if (this->_internal_has_header()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::header(this), target, stream);
  }

  // .ipc.Payload payload = 2;
  if (this->_internal_has_payload()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::payload(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ipc.Package)
  return target;
}

size_t Package::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ipc.Package)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .ipc.Header header = 1;
  if (this->_internal_has_header()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *header_);
  }

  // .ipc.Payload payload = 2;
  if (this->_internal_has_payload()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *payload_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Package::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Package::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Package::GetClassData() const { return &_class_data_; }

void Package::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Package *>(to)->MergeFrom(
      static_cast<const Package &>(from));
}


void Package::MergeFrom(const Package& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ipc.Package)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_header()) {
    _internal_mutable_header()->::ipc::Header::MergeFrom(from._internal_header());
  }
  if (from._internal_has_payload()) {
    _internal_mutable_payload()->::ipc::Payload::MergeFrom(from._internal_payload());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Package::CopyFrom(const Package& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ipc.Package)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Package::IsInitialized() const {
  return true;
}

void Package::InternalSwap(Package* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Package, payload_)
      + sizeof(Package::payload_)
      - PROTOBUF_FIELD_OFFSET(Package, header_)>(
          reinterpret_cast<char*>(&header_),
          reinterpret_cast<char*>(&other->header_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Package::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_MessageType_2eproto_getter, &descriptor_table_MessageType_2eproto_once,
      file_level_metadata_MessageType_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ipc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ipc::Header* Arena::CreateMaybeMessage< ::ipc::Header >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ipc::Header >(arena);
}
template<> PROTOBUF_NOINLINE ::ipc::Payload* Arena::CreateMaybeMessage< ::ipc::Payload >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ipc::Payload >(arena);
}
template<> PROTOBUF_NOINLINE ::ipc::Package* Arena::CreateMaybeMessage< ::ipc::Package >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ipc::Package >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
