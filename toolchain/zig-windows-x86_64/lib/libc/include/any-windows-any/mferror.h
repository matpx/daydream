/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#ifndef _MFERROR_H
#define _MFERROR_H

#define STATUS_SEVERITY(hr) (((hr) >> 30) & 0x3)
#define _HRESULT_TYPEDEF_(_sc) ((HRESULT)_sc)

#define FACILITY_MF_WIN32  0x7
#define FACILITY_MF        0xd

#define STATUS_SEVERITY_SUCCESS        0x0
#define STATUS_SEVERITY_INFORMATIONAL  0x1
#define STATUS_SEVERITY_WARNING        0x2
#define STATUS_SEVERITY_ERROR          0x3

#define MF_E_PLATFORM_NOT_INITIALIZED  _HRESULT_TYPEDEF_(0xc00d36b0)
#define MF_E_BUFFERTOOSMALL            _HRESULT_TYPEDEF_(0xc00d36b1)
#define MF_E_INVALIDREQUEST            _HRESULT_TYPEDEF_(0xc00d36b2)
#define MF_E_INVALIDSTREAMNUMBER       _HRESULT_TYPEDEF_(0xc00d36b3)
#define MF_E_INVALIDMEDIATYPE          _HRESULT_TYPEDEF_(0xc00d36b4)
#define MF_E_NOTACCEPTING              _HRESULT_TYPEDEF_(0xc00d36b5)
#define MF_E_NOT_INITIALIZED           _HRESULT_TYPEDEF_(0xc00d36b6)
#define MF_E_UNSUPPORTED_REPRESENTATION  _HRESULT_TYPEDEF_(0xc00d36b7)
#define MF_E_NO_MORE_TYPES             _HRESULT_TYPEDEF_(0xc00d36b9)
#define MF_E_UNSUPPORTED_SERVICE       _HRESULT_TYPEDEF_(0xc00d36ba)
#define MF_E_UNEXPECTED                _HRESULT_TYPEDEF_(0xc00d36bb)
#define MF_E_INVALIDNAME               _HRESULT_TYPEDEF_(0xc00d36bc)
#define MF_E_INVALIDTYPE               _HRESULT_TYPEDEF_(0xc00d36bd)
#define MF_E_INVALID_FILE_FORMAT       _HRESULT_TYPEDEF_(0xc00d36be)
#define MF_E_INVALIDINDEX              _HRESULT_TYPEDEF_(0xc00d36bf)
#define MF_E_INVALID_TIMESTAMP         _HRESULT_TYPEDEF_(0xc00d36c0)
#define MF_E_UNSUPPORTED_SCHEME        _HRESULT_TYPEDEF_(0xc00d36c3)
#define MF_E_UNSUPPORTED_BYTESTREAM_TYPE  _HRESULT_TYPEDEF_(0xc00d36c4)
#define MF_E_UNSUPPORTED_TIME_FORMAT   _HRESULT_TYPEDEF_(0xc00d36c5)
#define MF_E_NO_SAMPLE_TIMESTAMP       _HRESULT_TYPEDEF_(0xc00d36c8)
#define MF_E_NO_SAMPLE_DURATION        _HRESULT_TYPEDEF_(0xc00d36c9)
#define MF_E_INVALID_STREAM_DATA       _HRESULT_TYPEDEF_(0xc00d36cb)
#define MF_E_RT_UNAVAILABLE            _HRESULT_TYPEDEF_(0xc00d36cf)
#define MF_E_UNSUPPORTED_RATE          _HRESULT_TYPEDEF_(0xc00d36d0)
#define MF_E_THINNING_UNSUPPORTED      _HRESULT_TYPEDEF_(0xc00d36d1)
#define MF_E_REVERSE_UNSUPPORTED       _HRESULT_TYPEDEF_(0xc00d36d2)
#define MF_E_UNSUPPORTED_RATE_TRANSITION  _HRESULT_TYPEDEF_(0xc00d36d3)
#define MF_E_RATE_CHANGE_PREEMPTED     _HRESULT_TYPEDEF_(0xc00d36d4)
#define MF_E_NOT_FOUND                 _HRESULT_TYPEDEF_(0xc00d36d5)
#define MF_E_NOT_AVAILABLE             _HRESULT_TYPEDEF_(0xc00d36d6)
#define MF_E_NO_CLOCK                  _HRESULT_TYPEDEF_(0xc00d36d7)
#define MF_S_MULTIPLE_BEGIN            _HRESULT_TYPEDEF_(0x000d36d8)
#define MF_E_MULTIPLE_BEGIN            _HRESULT_TYPEDEF_(0xc00d36d9)
#define MF_E_MULTIPLE_SUBSCRIBERS      _HRESULT_TYPEDEF_(0xc00d36da)
#define MF_E_TIMER_ORPHANED            _HRESULT_TYPEDEF_(0xc00d36db)
#define MF_E_STATE_TRANSITION_PENDING      _HRESULT_TYPEDEF_(0xc00d36dc)
#define MF_E_UNSUPPORTED_STATE_TRANSITION  _HRESULT_TYPEDEF_(0xc00d36dd)
#define MF_E_UNRECOVERABLE_ERROR_OCCURRED  _HRESULT_TYPEDEF_(0xc00d36de)
#define MF_E_SAMPLE_HAS_TOO_MANY_BUFFERS   _HRESULT_TYPEDEF_(0xc00d36df)
#define MF_E_SAMPLE_NOT_WRITABLE       _HRESULT_TYPEDEF_(0xc00d36e0)
#define MF_E_INVALID_KEY               _HRESULT_TYPEDEF_(0xc00d36e2)
#define MF_E_BAD_STARTUP_VERSION       _HRESULT_TYPEDEF_(0xc00d36e3)
#define MF_E_UNSUPPORTED_CAPTION       _HRESULT_TYPEDEF_(0xc00d36e4)
#define MF_E_INVALID_POSITION          _HRESULT_TYPEDEF_(0xc00d36e5)
#define MF_E_ATTRIBUTENOTFOUND         _HRESULT_TYPEDEF_(0xc00d36e6)
#define MF_E_PROPERTY_TYPE_NOT_ALLOWED _HRESULT_TYPEDEF_(0xc00d36e7)
#define MF_E_PROPERTY_TYPE_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d36e8)
#define MF_E_PROPERTY_EMPTY              _HRESULT_TYPEDEF_(0xc00d36e9)
#define MF_E_PROPERTY_NOT_EMPTY          _HRESULT_TYPEDEF_(0xc00d36ea)
#define MF_E_PROPERTY_VECTOR_NOT_ALLOWED _HRESULT_TYPEDEF_(0xc00d36eb)
#define MF_E_PROPERTY_VECTOR_REQUIRED    _HRESULT_TYPEDEF_(0xc00d36ec)
#define MF_E_OPERATION_CANCELLED         _HRESULT_TYPEDEF_(0xc00d36ed)
#define MF_E_BYTESTREAM_NOT_SEEKABLE     _HRESULT_TYPEDEF_(0xc00d36ee)
#define MF_E_DISABLED_IN_SAFEMODE        _HRESULT_TYPEDEF_(0xc00d36ef)
#define MF_E_CANNOT_PARSE_BYTESTREAM     _HRESULT_TYPEDEF_(0xc00d36f0)
#define MF_E_SOURCERESOLVER_MUTUALLY_EXCLUSIVE_FLAGS _HRESULT_TYPEDEF_(0xc00d36f1)
#define MF_E_MEDIAPROC_WRONGSTATE        _HRESULT_TYPEDEF_(0xc00d36f2)
#define MF_E_RT_THROUGHPUT_NOT_AVAILABLE _HRESULT_TYPEDEF_(0xc00d36f3)
#define MF_E_RT_TOO_MANY_CLASSES         _HRESULT_TYPEDEF_(0xc00d36f4)
#define MF_E_RT_WOULDBLOCK               _HRESULT_TYPEDEF_(0xc00d36f5)
#define MF_E_NO_BITPUMP                  _HRESULT_TYPEDEF_(0xc00d36f6)
#define MF_E_RT_OUTOFMEMORY              _HRESULT_TYPEDEF_(0xc00d36f7)
#define MF_E_RT_WORKQUEUE_CLASS_NOT_SPECIFIED _HRESULT_TYPEDEF_(0xc00d36f8)
#define MF_E_INSUFFICIENT_BUFFER         _HRESULT_TYPEDEF_(0xc00d7170)
#define MF_E_CANNOT_CREATE_SINK          _HRESULT_TYPEDEF_(0xc00d36fa)
#define MF_E_BYTESTREAM_UNKNOWN_LENGTH   _HRESULT_TYPEDEF_(0xc00d36fb)
#define MF_E_SESSION_PAUSEWHILESTOPPED   _HRESULT_TYPEDEF_(0xc00d36fc)
#define MF_S_ACTIVATE_REPLACED           _HRESULT_TYPEDEF_(0x000d36fd)
#define MF_E_FORMAT_CHANGE_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d36fe)
#define MF_E_INVALID_WORKQUEUE           _HRESULT_TYPEDEF_(0xc00d36ff)
#define MF_E_DRM_UNSUPPORTED             _HRESULT_TYPEDEF_(0xc00d3700)
#define MF_E_UNAUTHORIZED                _HRESULT_TYPEDEF_(0xc00d3701)
#define MF_E_OUT_OF_RANGE                _HRESULT_TYPEDEF_(0xc00d3702)
#define MF_E_INVALID_CODEC_MERIT         _HRESULT_TYPEDEF_(0xc00d3703)
#define MF_E_HW_MFT_FAILED_START_STREAMING _HRESULT_TYPEDEF_(0xc00d3704)
#define MF_E_OPERATION_IN_PROGRESS       _HRESULT_TYPEDEF_(0xc00d3705)
#define MF_E_HARDWARE_DRM_UNSUPPORTED    _HRESULT_TYPEDEF_(0xc00d3706)
#define MF_E_DURATION_TOO_LONG           _HRESULT_TYPEDEF_(0xc00d3707)
#define MF_E_OPERATION_UNSUPPORTED_AT_D3D_FEATURE_LEVEL _HRESULT_TYPEDEF_(0xc00d3708)
#define MF_E_UNSUPPORTED_MEDIATYPE_AT_D3D_FEATURE_LEVEL _HRESULT_TYPEDEF_(0xc00d3709)
#define MF_S_ASF_PARSEINPROGRESS         _HRESULT_TYPEDEF_(0x400d3a98)
#define MF_E_ASF_PARSINGINCOMPLETE       _HRESULT_TYPEDEF_(0xc00d3a98)
#define MF_E_ASF_MISSINGDATA             _HRESULT_TYPEDEF_(0xc00d3a99)
#define MF_E_ASF_INVALIDDATA             _HRESULT_TYPEDEF_(0xc00d3a9a)
#define MF_E_ASF_OPAQUEPACKET            _HRESULT_TYPEDEF_(0xc00d3a9b)
#define MF_E_ASF_NOINDEX                 _HRESULT_TYPEDEF_(0xc00d3a9c)
#define MF_E_ASF_OUTOFRANGE              _HRESULT_TYPEDEF_(0xc00d3a9d)
#define MF_E_ASF_INDEXNOTLOADED          _HRESULT_TYPEDEF_(0xc00d3a9e)
#define MF_E_ASF_TOO_MANY_PAYLOADS       _HRESULT_TYPEDEF_(0xc00d3a9f)
#define MF_E_ASF_UNSUPPORTED_STREAM_TYPE _HRESULT_TYPEDEF_(0xc00d3aa0)
#define MF_E_ASF_DROPPED_PACKET          _HRESULT_TYPEDEF_(0xc00d3aa1)
#define MF_E_NO_EVENTS_AVAILABLE         _HRESULT_TYPEDEF_(0xc00d3e80)
#define MF_E_INVALID_STATE_TRANSITION    _HRESULT_TYPEDEF_(0xc00d3e82)
#define MF_E_END_OF_STREAM               _HRESULT_TYPEDEF_(0xc00d3e84)
#define MF_E_SHUTDOWN                    _HRESULT_TYPEDEF_(0xc00d3e85)
#define MF_E_MP3_NOTFOUND                _HRESULT_TYPEDEF_(0xc00d3e86)
#define MF_E_MP3_OUTOFDATA               _HRESULT_TYPEDEF_(0xc00d3e87)
#define MF_E_MP3_NOTMP3                  _HRESULT_TYPEDEF_(0xc00d3e88)
#define MF_E_MP3_NOTSUPPORTED            _HRESULT_TYPEDEF_(0xc00d3e89)
#define MF_E_NO_DURATION                 _HRESULT_TYPEDEF_(0xc00d3e8a)
#define MF_E_INVALID_FORMAT              _HRESULT_TYPEDEF_(0xc00d3e8c)
#define MF_E_PROPERTY_NOT_FOUND          _HRESULT_TYPEDEF_(0xc00d3e8d)
#define MF_E_PROPERTY_READ_ONLY          _HRESULT_TYPEDEF_(0xc00d3e8e)
#define MF_E_PROPERTY_NOT_ALLOWED        _HRESULT_TYPEDEF_(0xc00d3e8f)
#define MF_E_MEDIA_SOURCE_NOT_STARTED    _HRESULT_TYPEDEF_(0xc00d3e91)
#define MF_E_UNSUPPORTED_FORMAT          _HRESULT_TYPEDEF_(0xc00d3e98)
#define MF_E_MP3_BAD_CRC                 _HRESULT_TYPEDEF_(0xc00d3e99)
#define MF_E_NOT_PROTECTED               _HRESULT_TYPEDEF_(0xc00d3e9a)
#define MF_E_MEDIA_SOURCE_WRONGSTATE     _HRESULT_TYPEDEF_(0xc00d3e9b)
#define MF_E_MEDIA_SOURCE_NO_STREAMS_SELECTED _HRESULT_TYPEDEF_(0xc00d3e9c)
#define MF_E_CANNOT_FIND_KEYFRAME_SAMPLE _HRESULT_TYPEDEF_(0xc00d3e9d)
#define MF_E_UNSUPPORTED_CHARACTERISTICS _HRESULT_TYPEDEF_(0xc00d3e9e)
#define MF_E_NO_AUDIO_RECORDING_DEVICE   _HRESULT_TYPEDEF_(0xc00d3e9f)
#define MF_E_AUDIO_RECORDING_DEVICE_IN_USE _HRESULT_TYPEDEF_(0xc00d3ea0)
#define MF_E_AUDIO_RECORDING_DEVICE_INVALIDATED _HRESULT_TYPEDEF_(0xc00d3ea1)
#define MF_E_VIDEO_RECORDING_DEVICE_INVALIDATED _HRESULT_TYPEDEF_(0xc00d3ea2)
#define MF_E_VIDEO_RECORDING_DEVICE_PREEMPTED _HRESULT_TYPEDEF_(0xc00d3ea3)
#define MF_E_NETWORK_RESOURCE_FAILURE    _HRESULT_TYPEDEF_(0xc00d4268)
#define MF_E_NET_WRITE                   _HRESULT_TYPEDEF_(0xc00d4269)
#define MF_E_NET_READ                    _HRESULT_TYPEDEF_(0xc00d426a)
#define MF_E_NET_REQUIRE_NETWORK         _HRESULT_TYPEDEF_(0xc00d426b)
#define MF_E_NET_REQUIRE_ASYNC           _HRESULT_TYPEDEF_(0xc00d426c)
#define MF_E_NET_BWLEVEL_NOT_SUPPORTED   _HRESULT_TYPEDEF_(0xc00d426d)
#define MF_E_NET_STREAMGROUPS_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d426e)
#define MF_E_NET_MANUALSS_NOT_SUPPORTED  _HRESULT_TYPEDEF_(0xc00d426f)
#define MF_E_NET_INVALID_PRESENTATION_DESCRIPTOR _HRESULT_TYPEDEF_(0xc00d4270)
#define MF_E_NET_CACHESTREAM_NOT_FOUND   _HRESULT_TYPEDEF_(0xc00d4271)
#define MF_I_MANUAL_PROXY                _HRESULT_TYPEDEF_(0x400d4272)
#define MF_E_NET_REQUIRE_INPUT           _HRESULT_TYPEDEF_(0xc00d4274)
#define MF_E_NET_REDIRECT                _HRESULT_TYPEDEF_(0xc00d4275)
#define MF_E_NET_REDIRECT_TO_PROXY       _HRESULT_TYPEDEF_(0xc00d4276)
#define MF_E_NET_TOO_MANY_REDIRECTS      _HRESULT_TYPEDEF_(0xc00d4277)
#define MF_E_NET_TIMEOUT                 _HRESULT_TYPEDEF_(0xc00d4278)
#define MF_E_NET_CLIENT_CLOSE            _HRESULT_TYPEDEF_(0xc00d4279)
#define MF_E_NET_BAD_CONTROL_DATA        _HRESULT_TYPEDEF_(0xc00d427a)
#define MF_E_NET_INCOMPATIBLE_SERVER     _HRESULT_TYPEDEF_(0xc00d427b)
#define MF_E_NET_UNSAFE_URL              _HRESULT_TYPEDEF_(0xc00d427c)
#define MF_E_NET_CACHE_NO_DATA           _HRESULT_TYPEDEF_(0xc00d427d)
#define MF_E_NET_EOL                     _HRESULT_TYPEDEF_(0xc00d427e)
#define MF_E_NET_BAD_REQUEST             _HRESULT_TYPEDEF_(0xc00d427f)
#define MF_E_NET_INTERNAL_SERVER_ERROR   _HRESULT_TYPEDEF_(0xc00d4280)
#define MF_E_NET_SESSION_NOT_FOUND       _HRESULT_TYPEDEF_(0xc00d4281)
#define MF_E_NET_NOCONNECTION            _HRESULT_TYPEDEF_(0xc00d4282)
#define MF_E_NET_CONNECTION_FAILURE      _HRESULT_TYPEDEF_(0xc00d4283)
#define MF_E_NET_INCOMPATIBLE_PUSHSERVER _HRESULT_TYPEDEF_(0xc00d4284)
#define MF_E_NET_SERVER_ACCESSDENIED     _HRESULT_TYPEDEF_(0xc00d4285)
#define MF_E_NET_PROXY_ACCESSDENIED      _HRESULT_TYPEDEF_(0xc00d4286)
#define MF_E_NET_CANNOTCONNECT           _HRESULT_TYPEDEF_(0xc00d4287)
#define MF_E_NET_INVALID_PUSH_TEMPLATE   _HRESULT_TYPEDEF_(0xc00d4288)
#define MF_E_NET_INVALID_PUSH_PUBLISHING_POINT _HRESULT_TYPEDEF_(0xc00d4289)
#define MF_E_NET_BUSY                    _HRESULT_TYPEDEF_(0xc00d428a)
#define MF_E_NET_RESOURCE_GONE           _HRESULT_TYPEDEF_(0xc00d428b)
#define MF_E_NET_ERROR_FROM_PROXY        _HRESULT_TYPEDEF_(0xc00d428c)
#define MF_E_NET_PROXY_TIMEOUT           _HRESULT_TYPEDEF_(0xc00d428d)
#define MF_E_NET_SERVER_UNAVAILABLE      _HRESULT_TYPEDEF_(0xc00d428e)
#define MF_E_NET_TOO_MUCH_DATA           _HRESULT_TYPEDEF_(0xc00d428f)
#define MF_E_NET_SESSION_INVALID         _HRESULT_TYPEDEF_(0xc00d4290)
#define MF_E_OFFLINE_MODE                _HRESULT_TYPEDEF_(0xc00d4291)
#define MF_E_NET_UDP_BLOCKED             _HRESULT_TYPEDEF_(0xc00d4292)
#define MF_E_NET_UNSUPPORTED_CONFIGURATION _HRESULT_TYPEDEF_(0xc00d4293)
#define MF_E_NET_PROTOCOL_DISABLED       _HRESULT_TYPEDEF_(0xc00d4294)
#define MF_E_NET_COMPANION_DRIVER_DISCONNECT _HRESULT_TYPEDEF_(0xc00d4295)
#define MF_E_ALREADY_INITIALIZED         _HRESULT_TYPEDEF_(0xc00d4650)
#define MF_E_BANDWIDTH_OVERRUN           _HRESULT_TYPEDEF_(0xc00d4651)
#define MF_E_LATE_SAMPLE                 _HRESULT_TYPEDEF_(0xc00d4652)
#define MF_E_FLUSH_NEEDED                _HRESULT_TYPEDEF_(0xc00d4653)
#define MF_E_INVALID_PROFILE             _HRESULT_TYPEDEF_(0xc00d4654)
#define MF_E_INDEX_NOT_COMMITTED         _HRESULT_TYPEDEF_(0xc00d4655)
#define MF_E_NO_INDEX                    _HRESULT_TYPEDEF_(0xc00d4656)
#define MF_E_CANNOT_INDEX_IN_PLACE       _HRESULT_TYPEDEF_(0xc00d4657)
#define MF_E_MISSING_ASF_LEAKYBUCKET     _HRESULT_TYPEDEF_(0xc00d4658)
#define MF_E_INVALID_ASF_STREAMID        _HRESULT_TYPEDEF_(0xc00d4659)
#define MF_E_STREAMSINK_REMOVED          _HRESULT_TYPEDEF_(0xc00d4a38)
#define MF_E_STREAMSINKS_OUT_OF_SYNC     _HRESULT_TYPEDEF_(0xc00d4a3a)
#define MF_E_STREAMSINKS_FIXED           _HRESULT_TYPEDEF_(0xc00d4a3b)
#define MF_E_STREAMSINK_EXISTS           _HRESULT_TYPEDEF_(0xc00d4a3c)
#define MF_E_SAMPLEALLOCATOR_CANCELED    _HRESULT_TYPEDEF_(0xc00d4a3d)
#define MF_E_SAMPLEALLOCATOR_EMPTY       _HRESULT_TYPEDEF_(0xc00d4a3e)
#define MF_E_SINK_ALREADYSTOPPED         _HRESULT_TYPEDEF_(0xc00d4a3f)
#define MF_E_ASF_FILESINK_BITRATE_UNKNOWN _HRESULT_TYPEDEF_(0xc00d4a40)
#define MF_E_SINK_NO_STREAMS             _HRESULT_TYPEDEF_(0xc00d4a41)
#define MF_S_SINK_NOT_FINALIZED          _HRESULT_TYPEDEF_(0x000d4a42)
#define MF_E_METADATA_TOO_LONG           _HRESULT_TYPEDEF_(0xc00d4a43)
#define MF_E_SINK_NO_SAMPLES_PROCESSED   _HRESULT_TYPEDEF_(0xc00d4a44)
#define MF_E_SINK_HEADERS_NOT_FOUND      _HRESULT_TYPEDEF_(0xc00d4a45)
#define MF_E_VIDEO_REN_NO_PROCAMP_HW     _HRESULT_TYPEDEF_(0xc00d4e20)
#define MF_E_VIDEO_REN_NO_DEINTERLACE_HW _HRESULT_TYPEDEF_(0xc00d4e21)
#define MF_E_VIDEO_REN_COPYPROT_FAILED   _HRESULT_TYPEDEF_(0xc00d4e22)
#define MF_E_VIDEO_REN_SURFACE_NOT_SHARED _HRESULT_TYPEDEF_(0xc00d4e23)
#define MF_E_VIDEO_DEVICE_LOCKED         _HRESULT_TYPEDEF_(0xc00d4e24)
#define MF_E_NEW_VIDEO_DEVICE            _HRESULT_TYPEDEF_(0xc00d4e25)
#define MF_E_NO_VIDEO_SAMPLE_AVAILABLE   _HRESULT_TYPEDEF_(0xc00d4e26)
#define MF_E_NO_AUDIO_PLAYBACK_DEVICE    _HRESULT_TYPEDEF_(0xc00d4e84)
#define MF_E_AUDIO_PLAYBACK_DEVICE_IN_USE _HRESULT_TYPEDEF_(0xc00d4e85)
#define MF_E_AUDIO_PLAYBACK_DEVICE_INVALIDATED _HRESULT_TYPEDEF_(0xc00d4e86)
#define MF_E_AUDIO_SERVICE_NOT_RUNNING   _HRESULT_TYPEDEF_(0xc00d4e87)
#define MF_E_AUDIO_BUFFER_SIZE_ERROR     _HRESULT_TYPEDEF_(0xc00d4e88)
#define MF_E_AUDIO_CLIENT_WRAPPER_SPOOF_ERROR _HRESULT_TYPEDEF_(0xc00d4e89)

#define MF_E_TOPO_INVALID_OPTIONAL_NODE    _HRESULT_TYPEDEF_(0xc00d520e)
#define MF_E_TOPO_CANNOT_FIND_DECRYPTOR    _HRESULT_TYPEDEF_(0xc00d5211)
#define MF_E_TOPO_CODEC_NOT_FOUND      _HRESULT_TYPEDEF_(0xc00d5212)
#define MF_E_TOPO_CANNOT_CONNECT       _HRESULT_TYPEDEF_(0xc00d5213)
#define MF_E_TOPO_UNSUPPORTED          _HRESULT_TYPEDEF_(0xc00d5214)
#define MF_E_TOPO_INVALID_TIME_ATTRIBUTES  _HRESULT_TYPEDEF_(0xc00d5215)
#define MF_E_TOPO_LOOPS_IN_TOPOLOGY    _HRESULT_TYPEDEF_(0xC00d5216)
#define MF_E_TOPO_MISSING_PRESENTATION_DESCRIPTOR  _HRESULT_TYPEDEF_(0xc00d5217)
#define MF_E_TOPO_MISSING_STREAM_DESCRIPTOR        _HRESULT_TYPEDEF_(0xc00d5218)
#define MF_E_TOPO_STREAM_DESCRIPTOR_NOT_SELECTED   _HRESULT_TYPEDEF_(0xc00d5219)
#define MF_E_TOPO_MISSING_SOURCE       _HRESULT_TYPEDEF_(0xc00d521a)
#define MF_E_TOPO_SINK_ACTIVATES_UNSUPPORTED       _HRESULT_TYPEDEF_(0xc00d521b)
#define MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID _HRESULT_TYPEDEF_(0xc00d61ac)
#define MF_E_SEQUENCER_UNKNOWN_SEGMENT_ID _HRESULT_TYPEDEF_(0xc00d61ac)
#define MF_S_SEQUENCER_CONTEXT_CANCELED   _HRESULT_TYPEDEF_(0x000d61ad)
#define MF_E_NO_SOURCE_IN_CACHE           _HRESULT_TYPEDEF_(0xc00d61ae)
#define MF_S_SEQUENCER_SEGMENT_AT_END_OF_STREAM _HRESULT_TYPEDEF_(0x000d61af)
#define MF_E_TRANSFORM_TYPE_NOT_SET      _HRESULT_TYPEDEF_(0xc00d6d60)
#define MF_E_TRANSFORM_STREAM_CHANGE     _HRESULT_TYPEDEF_(0xc00d6d61)
#define MF_E_TRANSFORM_INPUT_REMAINING   _HRESULT_TYPEDEF_(0xc00d6d62)
#define MF_E_TRANSFORM_PROFILE_MISSING   _HRESULT_TYPEDEF_(0xc00d6d63)
#define MF_E_TRANSFORM_PROFILE_INVALID_OR_CORRUPT  _HRESULT_TYPEDEF_(0xc00d6d64)
#define MF_E_TRANSFORM_PROFILE_TRUNCATED           _HRESULT_TYPEDEF_(0xc00d6d65)
#define MF_E_TRANSFORM_PROPERTY_PID_NOT_RECOGNIZED _HRESULT_TYPEDEF_(0xc00d6d66)
#define MF_E_TRANSFORM_PROPERTY_VARIANT_TYPE_WRONG _HRESULT_TYPEDEF_(0xc00d6d67)
#define MF_E_TRANSFORM_PROPERTY_NOT_WRITEABLE      _HRESULT_TYPEDEF_(0xc00d6d68)
#define MF_E_TRANSFORM_PROPERTY_ARRAY_VALUE_WRONG_NUM_DIM  _HRESULT_TYPEDEF_(0xc00d6d69)
#define MF_E_TRANSFORM_PROPERTY_VALUE_SIZE_WRONG   _HRESULT_TYPEDEF_(0xc00d6d6a)
#define MF_E_TRANSFORM_PROPERTY_VALUE_OUT_OF_RANGE _HRESULT_TYPEDEF_(0xc00d6d6b)
#define MF_E_TRANSFORM_PROPERTY_VALUE_INCOMPATIBLE _HRESULT_TYPEDEF_(0xc00d6d6c)
#define MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_OUTPUT_MEDIATYPE       _HRESULT_TYPEDEF_(0xc00d6d6d)
#define MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_INPUT_MEDIATYPE        _HRESULT_TYPEDEF_(0xc00d6d6e)
#define MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_MEDIATYPE_COMBINATION  _HRESULT_TYPEDEF_(0xc00d6d6f)
#define MF_E_TRANSFORM_CONFLICTS_WITH_OTHER_CURRENTLY_ENABLED_FEATURES _HRESULT_TYPEDEF_(0xc00d6d70)
#define MF_E_TRANSFORM_NEED_MORE_INPUT                                 _HRESULT_TYPEDEF_(0xc00d6d72)
#define MF_E_TRANSFORM_NOT_POSSIBLE_FOR_CURRENT_SPKR_CONFIG            _HRESULT_TYPEDEF_(0xc00d6d73)
#define MF_E_TRANSFORM_CANNOT_CHANGE_MEDIATYPE_WHILE_PROCESSING        _HRESULT_TYPEDEF_(0xc00d6d74)
#define MF_S_TRANSFORM_DO_NOT_PROPAGATE_EVENT       _HRESULT_TYPEDEF_(0x000d6d75)
#define MF_E_UNSUPPORTED_D3D_TYPE                   _HRESULT_TYPEDEF_(0xc00d6d76)
#define MF_E_TRANSFORM_ASYNC_LOCKED                 _HRESULT_TYPEDEF_(0xc00d6d77)
#define MF_E_TRANSFORM_CANNOT_INITIALIZE_ACM_DRIVER _HRESULT_TYPEDEF_(0xc00d6d78)
#define MF_E_TRANSFORM_STREAM_INVALID_RESOLUTION _HRESULT_TYPEDEF_(0xc00d6d79)
#define MF_E_TRANSFORM_ASYNC_MFT_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d6d7a)
#define MF_E_TRANSFORM_EXATTRIBUTE_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d6d7c)
#define MF_E_LICENSE_INCORRECT_RIGHTS    _HRESULT_TYPEDEF_(0xc00d7148)
#define MF_E_LICENSE_OUTOFDATE           _HRESULT_TYPEDEF_(0xc00d7149)
#define MF_E_LICENSE_REQUIRED            _HRESULT_TYPEDEF_(0xc00d714a)
#define MF_E_DRM_HARDWARE_INCONSISTENT   _HRESULT_TYPEDEF_(0xc00d714b)
#define MF_E_NO_CONTENT_PROTECTION_MANAGER _HRESULT_TYPEDEF_(0xc00d714c)
#define MF_E_LICENSE_RESTORE_NO_RIGHTS   _HRESULT_TYPEDEF_(0xc00d714d)
#define MF_E_BACKUP_RESTRICTED_LICENSE   _HRESULT_TYPEDEF_(0xc00d714e)
#define MF_E_LICENSE_RESTORE_NEEDS_INDIVIDUALIZATION _HRESULT_TYPEDEF_(0xc00d714f)
#define MF_S_PROTECTION_NOT_REQUIRED     _HRESULT_TYPEDEF_(0x000d7150)
#define MF_E_COMPONENT_REVOKED           _HRESULT_TYPEDEF_(0xc00d7151)
#define MF_E_TRUST_DISABLED              _HRESULT_TYPEDEF_(0xc00d7152)
#define MF_E_WMDRMOTA_NO_ACTION          _HRESULT_TYPEDEF_(0xc00d7153)
#define MF_E_WMDRMOTA_ACTION_ALREADY_SET _HRESULT_TYPEDEF_(0xc00d7154)
#define MF_E_WMDRMOTA_DRM_HEADER_NOT_AVAILABLE _HRESULT_TYPEDEF_(0xc00d7155)
#define MF_E_WMDRMOTA_DRM_ENCRYPTION_SCHEME_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d7156)
#define MF_E_WMDRMOTA_ACTION_MISMATCH    _HRESULT_TYPEDEF_(0xc00d7157)
#define MF_E_WMDRMOTA_INVALID_POLICY     _HRESULT_TYPEDEF_(0xc00d7158)
#define MF_E_POLICY_UNSUPPORTED          _HRESULT_TYPEDEF_(0xc00d7159)
#define MF_E_OPL_NOT_SUPPORTED           _HRESULT_TYPEDEF_(0xc00d715a)
#define MF_E_TOPOLOGY_VERIFICATION_FAILED _HRESULT_TYPEDEF_(0xc00d715b)
#define MF_E_SIGNATURE_VERIFICATION_FAILED _HRESULT_TYPEDEF_(0xc00d715c)
#define MF_E_DEBUGGING_NOT_ALLOWED       _HRESULT_TYPEDEF_(0xc00d715d)
#define MF_E_CODE_EXPIRED                _HRESULT_TYPEDEF_(0xc00d715e)
#define MF_E_GRL_VERSION_TOO_LOW         _HRESULT_TYPEDEF_(0xc00d715f)
#define MF_E_GRL_RENEWAL_NOT_FOUND       _HRESULT_TYPEDEF_(0xc00d7160)
#define MF_E_GRL_EXTENSIBLE_ENTRY_NOT_FOUND _HRESULT_TYPEDEF_(0xc00d7161)
#define MF_E_KERNEL_UNTRUSTED            _HRESULT_TYPEDEF_(0xc00d7162)
#define MF_E_PEAUTH_UNTRUSTED            _HRESULT_TYPEDEF_(0xc00d7163)
#define MF_E_NON_PE_PROCESS              _HRESULT_TYPEDEF_(0xc00d7165)
#define MF_E_REBOOT_REQUIRED             _HRESULT_TYPEDEF_(0xc00d7167)
#define MF_S_WAIT_FOR_POLICY_SET         _HRESULT_TYPEDEF_(0x000d7168)
#define MF_S_VIDEO_DISABLED_WITH_UNKNOWN_SOFTWARE_OUTPUT _HRESULT_TYPEDEF_(0x000d7169)
#define MF_E_GRL_INVALID_FORMAT          _HRESULT_TYPEDEF_(0xc00d716a)
#define MF_E_GRL_UNRECOGNIZED_FORMAT     _HRESULT_TYPEDEF_(0xc00d716b)
#define MF_E_ALL_PROCESS_RESTART_REQUIRED _HRESULT_TYPEDEF_(0xc00d716c)
#define MF_E_PROCESS_RESTART_REQUIRED    _HRESULT_TYPEDEF_(0xc00d716d)
#define MF_E_USERMODE_UNTRUSTED          _HRESULT_TYPEDEF_(0xc00d716e)
#define MF_E_PEAUTH_SESSION_NOT_STARTED  _HRESULT_TYPEDEF_(0xc00d716f)
#define MF_E_PEAUTH_PUBLICKEY_REVOKED    _HRESULT_TYPEDEF_(0xc00d7171)
#define MF_E_GRL_ABSENT                  _HRESULT_TYPEDEF_(0xc00d7172)
#define MF_S_PE_TRUSTED                  _HRESULT_TYPEDEF_(0x000d7173)
#define MF_E_PE_UNTRUSTED                _HRESULT_TYPEDEF_(0xc00d7174)
#define MF_E_PEAUTH_NOT_STARTED          _HRESULT_TYPEDEF_(0xc00d7175)
#define MF_E_INCOMPATIBLE_SAMPLE_PROTECTION _HRESULT_TYPEDEF_(0xc00d7176)
#define MF_E_PE_SESSIONS_MAXED           _HRESULT_TYPEDEF_(0xc00d7177)
#define MF_E_HIGH_SECURITY_LEVEL_CONTENT_NOT_ALLOWED _HRESULT_TYPEDEF_(0xc00d7178)
#define MF_E_TEST_SIGNED_COMPONENTS_NOT_ALLOWED _HRESULT_TYPEDEF_(0xc00d7179)
#define MF_E_ITA_UNSUPPORTED_ACTION      _HRESULT_TYPEDEF_(0xC00D717A)
#define MF_E_ITA_ERROR_PARSING_SAP_PARAMETERS _HRESULT_TYPEDEF_(0xc00d717b)
#define MF_E_POLICY_MGR_ACTION_OUTOFBOUNDS _HRESULT_TYPEDEF_(0xc00d717c)
#define MF_E_BAD_OPL_STRUCTURE_FORMAT    _HRESULT_TYPEDEF_(0xc00d717d)
#define MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_PROTECTION_GUID _HRESULT_TYPEDEF_(0xc00d717e)
#define MF_E_NO_PMP_HOST                 _HRESULT_TYPEDEF_(0xc00d717f)
#define MF_E_ITA_OPL_DATA_NOT_INITIALIZED _HRESULT_TYPEDEF_(0xc00d7180)
#define MF_E_ITA_UNRECOGNIZED_ANALOG_VIDEO_OUTPUT _HRESULT_TYPEDEF_(0xc00d7181)
#define MF_E_ITA_UNRECOGNIZED_DIGITAL_VIDEO_OUTPUT _HRESULT_TYPEDEF_(0xc00d7182)
#define MF_E_RESOLUTION_REQUIRES_PMP_CREATION_CALLBACK _HRESULT_TYPEDEF_(0xc00d7183)
#define MF_E_INVALID_AKE_CHANNEL_PARAMETERS _HRESULT_TYPEDEF_(0xc00d7184)
#define MF_E_CONTENT_PROTECTION_SYSTEM_NOT_ENABLED _HRESULT_TYPEDEF_(0xc00d7185)
#define MF_E_UNSUPPORTED_CONTENT_PROTECTION_SYSTEM _HRESULT_TYPEDEF_(0xc00d7186)
#define MF_E_DRM_MIGRATION_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00d7187)
#define MF_E_HDCP_AUTHENTICATION_FAILURE _HRESULT_TYPEDEF_(0xc00d7188)
#define MF_E_HDCP_LINK_FAILURE           _HRESULT_TYPEDEF_(0xc00d7189)
#define MF_E_CLOCK_INVALID_CONTINUITY_KEY _HRESULT_TYPEDEF_(0xc00d9c40)
#define MF_E_CLOCK_NO_TIME_SOURCE        _HRESULT_TYPEDEF_(0xc00d9c41)
#define MF_E_CLOCK_STATE_ALREADY_SET     _HRESULT_TYPEDEF_(0xc00d9c42)
#define MF_E_CLOCK_NOT_SIMPLE            _HRESULT_TYPEDEF_(0xc00d9c43)
#define MF_S_CLOCK_STOPPED               _HRESULT_TYPEDEF_(0x000d9c44)
#define MF_E_CLOCK_AUDIO_DEVICE_POSITION_UNEXPECTED _HRESULT_TYPEDEF_(0x000d9c45)
#define MF_E_CLOCK_AUDIO_RENDER_POSITION_UNEXPECTED _HRESULT_TYPEDEF_(0x000d9c46)
#define MF_E_CLOCK_AUDIO_RENDER_TIME_UNEXPECTED _HRESULT_TYPEDEF_(0x000d9c47)
#define MF_E_NO_MORE_DROP_MODES          _HRESULT_TYPEDEF_(0xc00da028)
#define MF_E_NO_MORE_QUALITY_LEVELS      _HRESULT_TYPEDEF_(0xc00da029)
#define MF_E_DROPTIME_NOT_SUPPORTED      _HRESULT_TYPEDEF_(0xc00da02a)
#define MF_E_QUALITYKNOB_WAIT_LONGER     _HRESULT_TYPEDEF_(0xc00da02b)
#define MF_E_QM_INVALIDSTATE             _HRESULT_TYPEDEF_(0xc00da02c)
#define MF_E_TRANSCODE_NO_CONTAINERTYPE  _HRESULT_TYPEDEF_(0xc00da410)
#define MF_E_TRANSCODE_PROFILE_NO_MATCHING_STREAMS _HRESULT_TYPEDEF_(0xc00da411)
#define MF_E_TRANSCODE_NO_MATCHING_ENCODER _HRESULT_TYPEDEF_(0xc00da412)
#define MF_E_TRANSCODE_INVALID_PROFILE   _HRESULT_TYPEDEF_(0xc00da413)
#define MF_E_ALLOCATOR_NOT_INITIALIZED   _HRESULT_TYPEDEF_(0xc00da7f8)
#define MF_E_ALLOCATOR_NOT_COMMITED      _HRESULT_TYPEDEF_(0xc00da7f9)
#define MF_E_ALLOCATOR_ALREADY_COMMITED  _HRESULT_TYPEDEF_(0xc00da7fa)
#define MF_E_STREAM_ERROR                _HRESULT_TYPEDEF_(0xc00da7fb)
#define MF_E_INVALID_STREAM_STATE        _HRESULT_TYPEDEF_(0xc00da7fc)
#define MF_E_HW_STREAM_NOT_CONNECTED     _HRESULT_TYPEDEF_(0xc00da7fd)
#define MF_E_NO_CAPTURE_DEVICES_AVAILABLE _HRESULT_TYPEDEF_(0xc00dabe0)
#define MF_E_CAPTURE_SINK_OUTPUT_NOT_SET _HRESULT_TYPEDEF_(0xc00dabe1)
#define MF_E_CAPTURE_SINK_MIRROR_ERROR   _HRESULT_TYPEDEF_(0xc00dabe2)
#define MF_E_CAPTURE_SINK_ROTATE_ERROR   _HRESULT_TYPEDEF_(0xc00dabe3)
#define MF_E_CAPTURE_ENGINE_INVALID_OP   _HRESULT_TYPEDEF_(0xc00dabe4)
#define MF_E_CAPTURE_ENGINE_ALL_EFFECTS_REMOVED _HRESULT_TYPEDEF_(0xc00dabe5)
#define MF_E_CAPTURE_SOURCE_NO_INDEPENDENT_PHOTO_STREAM_PRESENT _HRESULT_TYPEDEF_(0xc00dabe6)
#define MF_E_CAPTURE_SOURCE_NO_VIDEO_STREAM_PRESENT _HRESULT_TYPEDEF_(0xc00dabe7)
#define MF_E_CAPTURE_SOURCE_NO_AUDIO_STREAM_PRESENT _HRESULT_TYPEDEF_(0xc00dabe8)
#define MF_E_CAPTURE_SOURCE_DEVICE_EXTENDEDPROP_OP_IN_PROGRESS _HRESULT_TYPEDEF_(0xc00dabe9)
#define MF_E_CAPTURE_PROPERTY_SET_DURING_PHOTO _HRESULT_TYPEDEF_(0xc00dabea)
#define MF_E_CAPTURE_NO_SAMPLES_IN_QUEUE _HRESULT_TYPEDEF_(0xc00dabeb)
#define MF_E_HW_ACCELERATED_THUMBNAIL_NOT_SUPPORTED _HRESULT_TYPEDEF_(0xc00dabec)
#define MF_E_UNSUPPORTED_CAPTURE_DEVICE_PRESENT _HRESULT_TYPEDEF_(0xc00dabed)
#define MF_E_TIMELINECONTROLLER_UNSUPPORTED_SOURCE_TYPE _HRESULT_TYPEDEF_(0xc00dafc8)
#define MF_E_TIMELINECONTROLLER_NOT_ALLOWED _HRESULT_TYPEDEF_(0xc00dafc9)
#define MF_E_TIMELINECONTROLLER_CANNOT_ATTACH _HRESULT_TYPEDEF_(0xc00dafca)
#define MF_E_MEDIA_EXTENSION_APPSERVICE_CONNECTION_FAILED _HRESULT_TYPEDEF_(0xc00db3b0)
#define MF_E_MEDIA_EXTENSION_APPSERVICE_REQUEST_FAILED _HRESULT_TYPEDEF_(0xc00db3b1)
#define MF_E_MEDIA_EXTENSION_PACKAGE_INTEGRITY_CHECK_FAILED _HRESULT_TYPEDEF_(0xc00db3b2)
#define MF_E_MEDIA_EXTENSION_PACKAGE_LICENSE_INVALID _HRESULT_TYPEDEF_(0xc00db3b3)

#define MF_INDEX_SIZE_ERR      0x80700001
#define MF_NOT_FOUND_ERR       0x80700008
#define MF_NOT_SUPPORTED_ERR   0x80700009
#define MF_INVALID_STATE_ERR   0x8070000b
#define MF_SYNTAX_ERR          0x8070000c
#define MF_INVALID_ACCESS_ERR  0x8070000f
#define MF_QUOTA_EXCEEDED_ERR  0x80700016
#define MF_PARSE_ERR           0x80700051
#define MF_TYPE_ERR            0x80704005

#endif /* _MFERROR_H */
