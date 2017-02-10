// Copyright [2013] Zurich Instruments AG

/** 
@file  ziAPI.h
@brief Header File for the Zurich Instruments AG C/C++ API v4 doing Communication with ziDataServer

ziAPI provides all functionality to establish a connection with the ziDataServer and to communicate with it. It has
functions for setting and getting parameters in a single call as well as an event-framework with which the user may
subscribe the parameter tree and receive the events which occur when values change.
- All functions do not check passed pointers if they're NULL pointers. In that case a segmentation fault will occur.
- The ZIConnection is not thread-safe. One connection can only be used in one thread. If you want to use the ziAPI
  in a multi-threaded program you will have to use one ZIConnection for each thread that is communicating or implement
  a mutual exclusion.
- The ziDataServer is able to handle connections from threads simultaneously. The ziDataServer takes over
  the synchronization.
*/

#ifndef __ZIAPI_H__
#define __ZIAPI_H__

// Portable fixed-width integer types.
// In case <stdint.h> is not available on your system, define ZI_CUSTOM_STDINT_H and set it to the
// name of the custom (or specific to your system) implementation.
#ifdef ZI_CUSTOM_STDINT_H
#include ZI_CUSTOM_STDINT_H
#elif defined(_MSC_VER) && _MSC_VER < 1600
// <stdint.h> is not available on MSVC++ below 2010 (10.0)
typedef   signed __int8    int8_t;
typedef   signed __int16   int16_t;
typedef   signed __int32   int32_t;
typedef   signed __int64   int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;
#else
#include <stdint.h>
#endif

#ifdef _WIN32
  #define ZI_EXPORT __declspec(dllexport)
  #ifndef __cplusplus
    #define inline __inline
  #endif
#else
  #define ZI_EXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// The maximum length that has to be used for passing paths to functions (including terminating zero)
#define MAX_PATH_LEN      256
/// The maximum size of an event's data block
#define MAX_EVENT_SIZE    0x400000


/// Defines return value for all ziAPI functions. Divided into 3 regions: info, warning and error.
enum ZIResult_enum {
  // *********** Infos
  ZI_INFO_BASE = 0x0000,
  /// Success (no error)
  ZI_INFO_SUCCESS = 0x0000,

  ZI_INFO_MAX,

  // *********** Warnings
  ZI_WARNING_BASE = 0x4000,
  /// Warning (general);
  ZI_WARNING_GENERAL = 0x4000,

  /// FIFO Underrun
  ZI_WARNING_UNDERRUN = 0x4001,
  /// FIFO Overflow
  ZI_WARNING_OVERFLOW = 0x4002,

  /// Value or Node not found
  ZI_WARNING_NOTFOUND = 0x4003,

  ZI_WARNING_MAX,

  // *********** Errors
  ZI_ERROR_BASE = 0x8000,
  /// Error (general)
  ZI_ERROR_GENERAL = 0x8000,

  /// USB Communication failed
  ZI_ERROR_USB = 0x8001,

  /// Memory allocation failed
  ZI_ERROR_MALLOC = 0x8002,

  /// Unable to initisalize mutex
  ZI_ERROR_MUTEX_INIT = 0x8003,
  /// Unable to destroy mutex
  ZI_ERROR_MUTEX_DESTROY = 0x8004,
  /// Unable to lock mutex
  ZI_ERROR_MUTEX_LOCK = 0x8005,
  /// Unable to unlock mutex
  ZI_ERROR_MUTEX_UNLOCK = 0x8006,

  /// Unable to start thread
  ZI_ERROR_THREAD_START = 0x8007,
  /// Unable to join thread
  ZI_ERROR_THREAD_JOIN = 0x8008,

  /// Can't initialize socket
  ZI_ERROR_SOCKET_INIT = 0x8009,
  /// Unable to connect socket
  ZI_ERROR_SOCKET_CONNECT = 0x800a,
  /// Hostname not found
  ZI_ERROR_HOSTNAME = 0x800b,

  /// Connection invalid
  ZI_ERROR_CONNECTION = 0x800c,
  /// Command timed out
  ZI_ERROR_TIMEOUT = 0x800d,
  /// Command internally failed
  ZI_ERROR_COMMAND = 0x800e,
  /// Command failed in server
  ZI_ERROR_SERVER_INTERNAL = 0x800f,

  /// Provided Buffer length is too small
  ZI_ERROR_LENGTH = 0x8010,

  /// Can't open file or read from it
  ZI_ERROR_FILE = 0x8011,

  /// There is already a similar entry
  ZI_ERROR_DUPLICATE = 0x8012,

  /// Attempt to set a read-only node
  ZI_ERROR_READONLY = 0x8013,

  /// Device is not visible to the server
  ZI_ERROR_DEVICE_NOT_VISIBLE = 0x8014,
  /// Device is already connected by a different server
  ZI_ERROR_DEVICE_IN_USE = 0x8015,
  /// Device does currently not support the specified interface
  ZI_ERROR_DEVICE_INTERFACE = 0x8016,
  /// Device connection timeout
  ZI_ERROR_DEVICE_CONNECTION_TIMEOUT = 0x8017,
  /// Device already connected over a different Interface
  ZI_ERROR_DEVICE_DIFFERENT_INTERFACE = 0x8018,
  /// Device needs FW upgrade
  ZI_ERROR_DEVICE_NEEDS_FW_UPGRADE = 0x8019,

  ZI_ERROR_MAX,

  // deprecated
  // **********
#ifdef _MSC_VER
  /// Success (no error)
  ZI_SUCCESS = 0x0000,

  ZI_MAX_INFO,

  /// Warning (general);
  ZI_WARNING = 0x4000,

  /// FIFO Underrun
  ZI_UNDERRUN,
  /// FIFO Overflow
  ZI_OVERFLOW,

  /// Value or Node not found
  ZI_NOTFOUND,

  ZI_MAX_WARNING,

  /// Error (general)
  ZI_ERROR = 0x8000,

  /// USB Communication failed
  ZI_USB,

  /// Memory allocation failed
  ZI_MALLOC,

  /// Unable to initialize mutex
  ZI_MUTEX_INIT,
  /// Unable to destroy mutex
  ZI_MUTEX_DESTROY,
  /// Unable to lock mutex
  ZI_MUTEX_LOCK,
  /// Unable to unlock mutex
  ZI_MUTEX_UNLOCK,

  /// Unable to start thread
  ZI_THREAD_START,
  /// Unable to join thread
  ZI_THREAD_JOIN,

  /// Can't initialize socket
  ZI_SOCKET_INIT,
  /// Unable to connect socket
  ZI_SOCKET_CONNECT,
  /// Hostname not found
  ZI_HOSTNAME,

  /// Connection invalid
  ZI_CONNECTION,
  /// Command timed out
  ZI_TIMEOUT,
  /// Command internally failed
  ZI_COMMAND,
  /// Command failed in server
  ZI_SERVER_INTERNAL,

  /// Provided Buffer length doesn't reach
  ZI_LENGTH,

  /// Can't open file or read from it
  ZI_FILE,

  /// There is already a similar entry
  ZI_DUPLICATE,

  /// Attempt to set a read-only node
  ZI_READONLY,

  ZI_MAX_ERROR,
#endif
};

#ifdef _MSC_VER
#pragma deprecated(ZI_SUCCESS)
#pragma deprecated(ZI_MAX_INFO)
#pragma deprecated(ZI_WARNING)
#pragma deprecated(ZI_UNDERRUN)
#pragma deprecated(ZI_OVERFLOW)
#pragma deprecated(ZI_NOTFOUND)
#pragma deprecated(ZI_MAX_WARNING)
#pragma deprecated(ZI_ERROR)
#pragma deprecated(ZI_USB)
#pragma deprecated(ZI_MALLOC)
#pragma deprecated(ZI_MUTEX_INIT)
#pragma deprecated(ZI_MUTEX_DESTROY)
#pragma deprecated(ZI_MUTEX_LOCK)
#pragma deprecated(ZI_MUTEX_UNLOCK)
#pragma deprecated(ZI_THREAD_START)
#pragma deprecated(ZI_THREAD_JOIN)
#pragma deprecated(ZI_SOCKET_INIT)
#pragma deprecated(ZI_SOCKET_CONNECT)
#pragma deprecated(ZI_HOSTNAME)
#pragma deprecated(ZI_CONNECTION)
#pragma deprecated(ZI_TIMEOUT)
#pragma deprecated(ZI_COMMAND)
#pragma deprecated(ZI_SERVER_INTERNAL)
#pragma deprecated(ZI_LENGTH)
#pragma deprecated(ZI_FILE)
#pragma deprecated(ZI_DUPLICATE)
#pragma deprecated(ZI_READONLY)
#pragma deprecated(ZI_MAX_ERROR)
#else
__attribute__((deprecated)) const ZIResult_enum ZI_SUCCESS         = ZIResult_enum(0x0000);
__attribute__((deprecated)) const ZIResult_enum ZI_MAX_INFO        = ZIResult_enum(0x0001);
__attribute__((deprecated)) const ZIResult_enum ZI_WARNING         = ZIResult_enum(0x4000);
__attribute__((deprecated)) const ZIResult_enum ZI_UNDERRUN        = ZIResult_enum(0x4001);
__attribute__((deprecated)) const ZIResult_enum ZI_OVERFLOW        = ZIResult_enum(0x4002);
__attribute__((deprecated)) const ZIResult_enum ZI_NOTFOUND        = ZIResult_enum(0x4003);
__attribute__((deprecated)) const ZIResult_enum ZI_MAX_WARNING     = ZIResult_enum(0x4004);
__attribute__((deprecated)) const ZIResult_enum ZI_ERROR           = ZIResult_enum(0x8000);
__attribute__((deprecated)) const ZIResult_enum ZI_USB             = ZIResult_enum(0x8001);
__attribute__((deprecated)) const ZIResult_enum ZI_MALLOC          = ZIResult_enum(0x8002);
__attribute__((deprecated)) const ZIResult_enum ZI_MUTEX_INIT      = ZIResult_enum(0x8003);
__attribute__((deprecated)) const ZIResult_enum ZI_MUTEX_DESTROY   = ZIResult_enum(0x8004);
__attribute__((deprecated)) const ZIResult_enum ZI_MUTEX_LOCK      = ZIResult_enum(0x8005);
__attribute__((deprecated)) const ZIResult_enum ZI_MUTEX_UNLOCK    = ZIResult_enum(0x8006);
__attribute__((deprecated)) const ZIResult_enum ZI_THREAD_START    = ZIResult_enum(0x8007);
__attribute__((deprecated)) const ZIResult_enum ZI_THREAD_JOIN     = ZIResult_enum(0x8008);
__attribute__((deprecated)) const ZIResult_enum ZI_SOCKET_INIT     = ZIResult_enum(0x8009);
__attribute__((deprecated)) const ZIResult_enum ZI_SOCKET_CONNECT  = ZIResult_enum(0x800a);
__attribute__((deprecated)) const ZIResult_enum ZI_HOSTNAME        = ZIResult_enum(0x800b);
__attribute__((deprecated)) const ZIResult_enum ZI_CONNECTION      = ZIResult_enum(0x800c);
__attribute__((deprecated)) const ZIResult_enum ZI_TIMEOUT         = ZIResult_enum(0x800d);
__attribute__((deprecated)) const ZIResult_enum ZI_COMMAND         = ZIResult_enum(0x800e);
__attribute__((deprecated)) const ZIResult_enum ZI_SERVER_INTERNAL = ZIResult_enum(0x800f);
__attribute__((deprecated)) const ZIResult_enum ZI_LENGTH          = ZIResult_enum(0x8010);
__attribute__((deprecated)) const ZIResult_enum ZI_FILE            = ZIResult_enum(0x8011);
__attribute__((deprecated)) const ZIResult_enum ZI_DUPLICATE       = ZIResult_enum(0x8012);
__attribute__((deprecated)) const ZIResult_enum ZI_READONLY        = ZIResult_enum(0x8013);
__attribute__((deprecated)) const ZIResult_enum ZI_MAX_ERROR       = ZIResult_enum(0x8014);
#endif

#ifndef __cplusplus
typedef enum ZIResult_enum ZIResult_enum;
#endif

/// Enumerates all types that data in a ZIEvent may have
enum ZIValueType_enum {
  /// No data type, event is invalid.
  ZI_VALUE_TYPE_NONE = 0,

  /// ZIDoubleData type. Use the ZIEvent.value.doubleData pointer to read the data of the event.
  ZI_VALUE_TYPE_DOUBLE_DATA = 1,
  /// ZIDoubleDataTS type. Use the ZIEvent.value.doubleDataTS pointer to read the data of the event.
  ZI_VALUE_TYPE_DOUBLE_DATA_TS = 32,
  /// ZIIntegerData type. Use the ZIEvent.value.integerData pointer to read the data of the event.
  ZI_VALUE_TYPE_INTEGER_DATA = 2,
  /// ZIIntegerDataTS type. Use the ZIEvent.value.integerDataTS pointer to read the data of the event.
  ZI_VALUE_TYPE_INTEGER_DATA_TS = 33,
  /// ZIDemodSample type. Use the ZIEvent.value.demodSample pointer to read the data of the event.
  ZI_VALUE_TYPE_DEMOD_SAMPLE = 3,
  /// ZIAuxInSample type. Use the ZIEvent.value.auxInSample pointer to read the data of the event.
  ZI_VALUE_TYPE_AUXIN_SAMPLE = 5,
  /// ZIDIOSample type. Use the ZIEvent.value.dioSample pointer to read the data of the event.
  ZI_VALUE_TYPE_DIO_SAMPLE = 6,
  /// ZIByteArray type. Use the ZIEvent.value.byteArray pointer to read the data of the event.
  ZI_VALUE_TYPE_BYTE_ARRAY = 7,
  /// ZIByteArrayTS type. Use the ZIEvent.value.byteArrayTS pointer to read the data of the event.
  ZI_VALUE_TYPE_BYTE_ARRAY_TS = 38,

  /// ZITreeChangeData type - a list of added or removed nodes. Use the ZIEvent.value.treeChangeData
  /// pointer to read the data of the event.
  ZI_VALUE_TYPE_TREE_CHANGE_DATA = 48,
  /// TreeChange type - a list of added or removed nodes, used in v1 compatibility mode. Use the
  /// ZIEvent.value.treeChangeDataOld pointer to read the data of the event.
  ZI_VALUE_TYPE_TREE_CHANGE_DATA_OLD = 16,

  /// ZIScopeWave type. Use the ZIEvent.value.scopeWave pointer to read the data of the event.
  ZI_VALUE_TYPE_SCOPE_WAVE = 35,
  /// ScopeWave type, used in v1 compatibility mode. use the ZIEvent.value.scopeWaveOld pointer
  /// to read the data of the event.
  ZI_VALUE_TYPE_SCOPE_WAVE_OLD = 4,

  /// ZIPWAWave type. Use the ZIEvent.value.pwaWave pointer to read the data of the event.
  ZI_VALUE_TYPE_PWA_WAVE = 8,

  // deprecated
  // **********
#ifdef _MSC_VER
  /// no data type. the ziEvent is invalid.
  ZI_DATA_NONE = 0,

  /// double data type. use the ziEvent::Val.Double Pointer to read the data of the event.
  ZI_DATA_DOUBLE = 1,
  /// integer data type. use the ziEvent::Val.Integer Pointer to read the data of the event.
  ZI_DATA_INTEGER = 2,
  /// DemodSample data type. use the ziEvent::Val.Sample Pointer to read the data of the event.
  ZI_DATA_DEMODSAMPLE = 3,
  /// ScopeWave data type. use the ziEvent::Val.Wave Pointer to read the data of the event.
  ZI_DATA_SCOPEWAVE = 4,
  /// MiscADValue data type. use the ziEvent::Val.ADValue Pointer to read the data of the event.
  ZI_DATA_AUXINSAMPLE = 5,
  /// DIOValue data type. use the ziEvent::Val.DIOValue Pointer to read the data of the event.
  ZI_DATA_DIOSAMPLE = 6,
  /// ByteArray data type. use the ziEvent::Val.ByteArray Pointer to read the data of the event.
  ZI_DATA_BYTEARRAY = 7,

  /// a list of added or removed trees. use the ziEvent::Val.Tree Pointer to read the data of the event.
  ZI_DATA_TREE_CHANGED = 16,
#endif
};

#ifdef _MSC_VER
#pragma deprecated(ZI_DATA_NONE)
#pragma deprecated(ZI_DATA_DOUBLE)
#pragma deprecated(ZI_DATA_INTEGER)
#pragma deprecated(ZI_DATA_DEMODSAMPLE)
#pragma deprecated(ZI_DATA_SCOPEWAVE)
#pragma deprecated(ZI_DATA_AUXINSAMPLE)
#pragma deprecated(ZI_DATA_DIOSAMPLE)
#pragma deprecated(ZI_DATA_BYTEARRAY)
#pragma deprecated(ZI_DATA_TREE_CHANGED)
#else
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_NONE         = ZIValueType_enum(0);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_DOUBLE       = ZIValueType_enum(1);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_INTEGER      = ZIValueType_enum(2);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_DEMODSAMPLE  = ZIValueType_enum(3);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_SCOPEWAVE    = ZIValueType_enum(4);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_AUXINSAMPLE  = ZIValueType_enum(5);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_DIOSAMPLE    = ZIValueType_enum(6);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_BYTEARRAY    = ZIValueType_enum(7);
__attribute__((deprecated)) const ZIValueType_enum ZI_DATA_TREE_CHANGED = ZIValueType_enum(16);
#endif

#ifndef __cplusplus
typedef enum ZIValueType_enum ZIValueType_enum;
#endif

typedef uint64_t ZITimeStamp;
typedef double ZIDoubleData;
typedef int64_t ZIIntegerData;

/// The structure is holding single IEEE double value. Same as ZIDoubleData, but with timestamp.
struct ZIDoubleDataTS {
  /// Time stamp at which the value has changed
  ZITimeStamp timeStamp;
  ZIDoubleData value;
};

#ifndef __cplusplus
typedef struct ZIDoubleDataTS ZIDoubleDataTS;
#endif

/// The structure is holding single 64bit signed integer value. Same as ZIIntegerData, but with timestamp.
struct ZIIntegerDataTS {
  /// Time stamp at which the value has changed
  ZITimeStamp timeStamp;
  ZIIntegerData value;
};

#ifndef __cplusplus
typedef struct ZIIntegerDataTS ZIIntegerDataTS;
#endif

/// Defines the actions that are performed on a tree, as returned in
/// the ZITreeChangeData::action or ZITreeChangeDataOld::action.
enum ZITreeAction_enum {
  /// a node has been removed
  ZI_TREE_ACTION_REMOVE = 0,

  /// a node has been added
  ZI_TREE_ACTION_ADD = 1,

  /// a node has been changed
  ZI_TREE_ACTION_CHANGE = 2,
};

/// The struct is holding info about added or removed nodes.
struct ZITreeChangeData {
  /// Time stamp at which the data was updated
  ZITimeStamp timeStamp;
  /// field indicating which action occured on the tree. A value of the ZITreeAction_enum.
  uint32_t action;
  /// Name of the Path that has been added, removed or changed
  char name[32];  // should be PNODE_NAME_LEN
};

#ifndef __cplusplus
typedef struct ZITreeChangeData ZITreeChangeData;
#endif

/// The structure is holding info about added or removed nodes. This is the version without timestamp
/// used in API v1 compatibility mode.
struct TreeChange {
  /// field indicating which action occured on the tree. A value of the ZITreeAction_enum (TREE_ACTION) enum.
  uint32_t Action;
  /// Name of the Path that has been added, removed or changed
  char Name[32];  // should be PNODE_NAME_LEN
};

#ifndef __cplusplus
typedef struct TreeChange TreeChange;
#endif


/// The structure is holding data for a single demodulator sample
struct ZIDemodSample {
  /// Time stamp at which the sample has been measured
  ZITimeStamp timeStamp;

  /// X part of the sample
  double x;
  /// Y part of the sample
  double y;

  /// Frequency at that sample
  double frequency;
  /// Phase at that sample
  double phase;

  /// the current bits of the DIO
  uint32_t dioBits;

  /// trigger bits
  uint32_t trigger;

  /// value of Aux input 0
  double auxIn0;
  /// value of Aux input 1
  double auxIn1;
};

#ifndef __cplusplus
typedef struct ZIDemodSample ZIDemodSample;
#endif

/// The structure is holding data for a single auxiliary inputs sample
struct ZIAuxInSample {
  /// Time stamp at which the values have been measured
  ZITimeStamp timeStamp;

  /// Channel 0 voltage
  double ch0;
  /// Channel 1 voltage
  double ch1;
};

#ifndef __cplusplus
typedef struct ZIAuxInSample ZIAuxInSample;
#endif

/// The structure is holding data for a single digital I/O sample
struct ZIDIOSample {
  /// Time stamp at which the values have been measured
  ZITimeStamp timeStamp;

  /// The digital I/O values
  uint32_t bits;

  /// Filler to keep 8 bytes alignment in the array of ZIDIOSample structures
  uint32_t reserved;
};

#ifndef __cplusplus
typedef struct ZIDIOSample ZIDIOSample;
#endif

#ifdef _MSC_VER
// Visual C++ specific
#pragma warning(push)
#pragma warning(disable:4200)
#endif

/// The structure is holding arbitrary array of bytes. This is the version without timestamp
/// used in API v1 compatibility mode.
struct ZIByteArray {
  /// Length of the data readable from the Bytes field
  uint32_t length;
  /// The data itself. The array has the size given in length
  uint8_t bytes[0];
};

#ifndef __cplusplus
typedef struct ZIByteArray ZIByteArray;
#endif

/// The structure is holding arbitrary array of bytes. This is the same as ZIByteArray, but with timestamp.
struct ZIByteArrayTS {
  /// Time stamp at which the data was updated
  ZITimeStamp timeStamp;
  /// length of the data readable from the bytes field
  uint32_t length;
  /// the data itself. The array has the size given in length
  uint8_t bytes[0];
};

#ifndef __cplusplus
typedef struct ZIByteArrayTS ZIByteArrayTS;
#endif

/// The structure is holding a single scope shot.
struct ScopeWave {
  /// Time difference between samples
  double dt;

  /// Scope channel of the represented data
  unsigned int ScopeChannel;
  /// Trigger channel of the represented data
  unsigned int TriggerChannel;

  /// Bandwidth-limit flag
  unsigned int BWLimit;

  /// Count of samples
  unsigned int Count;
  /// First wave data
  short Data[0];
};

#ifndef __cplusplus
typedef struct ScopeWave ScopeWave;
#endif

/// The structure is holding scope data. The data may be formatted differently, depending on settings.
/// See the description of the structure members for details.
struct ZIScopeWave {

//--- 8 bytes border
    /// Time stamp of the first sample in this data block
    ZITimeStamp timeStamp;

//--- 8 bytes border
    /// Time stamp of the trigger (may also fall between samples)
    ZITimeStamp triggerTimeStamp;

//--- 8 bytes border
    /// Time difference between samples in seconds
    double dt;

//--- 8 bytes border
    /// Up to four channels: if channel is enabled, corresponding element is non-zero.
    uint8_t channelEnable[4];

    /// For each of the four channels, input source:
    ///   0 - Signal Input 1
    ///   1 - Signal Input 2
    ///   2 - Trigger Input 1
    ///   3 - Trigger Input 2
    ///   4 - Aux Output 1
    ///   5 - Aux Output 2
    ///   6 - Aux Output 3
    ///   7 - Aux Output 4
    ///   8 - Aux Input 1
    ///   9 - Aux Input 2
    uint8_t channelInput[4];

//--- 8 bytes border
    /// Non-zero if trigger is enabled
    ///   Bit(0): rising edge trigger off = 0, on = 1
    ///   Bit(1): falling edge trigger off = 0, on = 1
    uint8_t triggerEnable;

    /// Trigger source (same values as for channel input)
    uint8_t triggerInput;

    uint8_t reserved0[2];

    /// Bandwidth-limit flag, per channel
    ///   Bit(0): off = 0, on = 1
    ///   Bit(7...1): Reserved
    uint8_t channelBWLimit[4];

//--- 8 bytes border
    /// Math Operation (e.g averaging)
    ///   Bit (7..0): Reserved
    uint8_t channelMath[4];

    /// Data scaling factors for up to 4 channels
    float channelScaling[4];

    /// Current scope shot sequence number. Identifies a scope shot.
    uint32_t sequenceNumber;

//--- 8 bytes border
    /// Current segment number.
    uint32_t segmentNumber;

    /// Current block number from the beginning of a scope shot.
    /// Large scope shots are split into blocks, which need to be concatenated to obtain the complete scope shot.
    uint32_t blockNumber;

//--- 8 bytes border
    /// Total number of samples in one channel in the current scope shot, same for all channels
    uint64_t totalSamples;

//--- 8 bytes border
    /// Data transfer mode
    ///   SingleTransfer = 0, BlockTransfer = 1, ContinuousTransfer = 3, FFTSingleTransfer = 4
    ///   Other values are reserved
    uint8_t dataTransferMode;

    /// Block marker
    ///   Bit (0): 1 = End marker for continuous or multi-block transfer
    ///   Bit (7..0): Reserved
    uint8_t blockMarker;

    /// Indicator Flags
    ///   Bit (0): 1 = Data loss detected (samples are 0)
    ///   Bit (1): 1 = Missed trigger
    ///   Bit (2): 1 = Transfer failure (corrupted data)
    uint8_t flags;

    /// Data format of samples
    ///   Int16 = 0, Int32 = 1, Float = 2, Int16Interleaved = 4, Int32Interleaved = 5, FloatInterleaved = 6
    uint8_t sampleFormat;

    /// Number of samples in one channel in the current block, same for all channels
    uint32_t sampleCount;

//--- 8 bytes border
    /// First wave data
    union {
      int16_t dataInt16[0];
      int32_t dataInt32[0];
      float dataFloat[0];
    } data;

};

#ifndef __cplusplus
typedef struct ZIScopeWave ZIScopeWave;
#endif

/// Single PWA sample value
struct ZIPWASample {
  /// Phase position of each bin
  double binPhase;
  /// Real PWA result or X component of a demod PWA
  double x;
  /// Y component of the demod PWA
  double y;
  /// Number of events per bin
  uint32_t countBin;
  /// Reserved
  uint32_t reserved;
};

#ifndef __cplusplus
typedef struct ZIPWASample ZIPWASample;
#endif

/// PWA Wave
struct ZIPWAWave {
  /// Time stamp at which the data was updated
  ZITimeStamp timeStamp;

  /// Total sample count considered for PWA
  uint64_t sampleCount;

  /// Input selection used for the PWA
  uint32_t inputSelect;
  /// Oscillator used for the PWA
  uint32_t oscSelect;
  /// Harmonic setting
  uint32_t harmonic;
  /// Bin count of the PWA
  uint32_t binCount;

  /// Frequency during PWA accumulation
  double frequency;

  /// Type of the PWA
  uint8_t pwaType;
  /// PWA Mode [0: zoom PWA, 1: harmonic PWA]
  uint8_t mode;
  /// Overflow indicators
  /// overflow[0]: Data accumulator overflow
  /// overflow[1]: Counter at limit
  /// overflow[6..2]: Reserved
  /// overflow[7]: Invalid (missing frames)
  uint8_t overflow;
  /// Commensurability of the data
  uint8_t commensurable;
  /// Reserved unsigned int
  uint32_t reservedUInt;

  /// PWA data vector
  ZIPWASample data[0];
};

#ifndef __cplusplus
typedef struct ZIPWAWave ZIPWAWave;
#endif

#ifdef _MSC_VER
// Visual C++ specific
#pragma warning(pop)
#endif


/** @defgroup Connection Connecting to ziDataServer
 *  @brief This section describes how to initialize the ZIConnection and establish a connection to ziDataServer as well
 *         as how to disconnect after all data handling is done and cleanup the ZIConnection.
 *  @include ExampleConnection.c
 *  @{
 */

enum ZIAPIVersion_enum {
  ZI_API_VERSION_1 = 1,
  ZI_API_VERSION_4 = 4
};

#ifndef __cplusplus
typedef enum ZIAPIVersion_enum ZIAPIVersion_enum;
#endif


#ifdef __cplusplus
struct ZIConnectionProxy {};
#else
typedef void ZIConnectionProxy;
#endif

/// The ZIConnection is a connection reference; it holds information and helper variables about a connection to the ziServer. There is nothing in this reference which the user user may use, so it is hidden and instead a dummy pointer is used.  See ::ziAPIInit for how to create a ZIConnection.
/** This struct is intentionally left blank so that the ZIConnection does not
   have to be defined as void pointer. If it would be defined as void* the
   compiler won't give a warning, when a void** is given to a funtction since
   a void** is also a void*. Blank struct however is not supported by C89
   standard, therefore in this case for compatibility ZIConnection is defined
   as plain void*.
 */
typedef ZIConnectionProxy* ZIConnection;

/// Initializes a ::ZIConnection structure.
/** This function initializes the structure so that it is ready to connect to ziDataServer. It allocates memory and sets
    up the infrastructure needed.

    @param[out]  conn  Pointer to ::ZIConnection that is to be initialized
    @return 
    - ZI_INFO_SUCCESS  on success
    - ZI_ERROR_MALLOC  on memory allocation failure

    See @link Connection Connection @endlink for an example
    @sa ziAPIDestroy, ziAPIConnect, ziAPIDisconnect
 */
ZI_EXPORT ZIResult_enum ziAPIInit(ZIConnection* conn);

/// Destroys a ::ZIConnection structure.
/** This function frees all memory that has been allocated by ::ziAPIInit. If it is called with an uninitialized
    ::ZIConnection struct it may result in segmentation faults as well when it is called with a struct for which
    ZIAPIDestroy already has been called.

    @param[in] conn Pointer to ::ZIConnection struct that has to be destroyed
    @return 
    - ZI_INFO_SUCCESS

    See @link Connection Connection @endlink for an example
    @sa ziAPIInit, ziAPIConnect, ziAPIDisconnect
 */  
ZI_EXPORT ZIResult_enum ziAPIDestroy(ZIConnection conn);

/// Connects the ZIConnection to ziDataServer.
/** Connects to ziDataServer using a ::ZIConnection and prepares for data exchange. For most cases it is enough to just
    give a reference to the connection and give NULL for hostname and 0 for the port, so it connects to localhost
    on the default port.

    @param[in]   conn      Pointer to ::ZIConnection with which the connection should be established
    @param[in]   hostname  Name of the Host to which it should be connected, if NULL "localhost" will be used as
                           default
    @param[in]   port      The Number of the port to connect to. If 0, default port of the local ziDataServer will be
                           used (8005)
    @return 
    - ZI_INFO_SUCCESS          on success
    - ZI_ERROR_HOSTNAME        if the given host name could not be found
    - ZI_ERROR_SOCKET_CONNECT  if no connection could be established
    - ZI_ERROR_OVERFLOW        when a FIFO overflow occurred
    - ZI_ERROR_SOCKET_INIT     if initialization of the socket failed
    - ZI_ERROR_CONNECTION      when the ziDataServer didn't return the correct answer
    - ZI_ERROR_TIMEOUT         when initial communication timed out

    See @link Connection Connection @endlink for an example
    @sa ziAPIDisconnect, ziAPIInit, ziAPIDestroy
 */
ZI_EXPORT ZIResult_enum ziAPIConnect(ZIConnection conn, const char* hostname, uint16_t port);

/// Disconnects an established connection.
/** Disconnects from ziDataServer. If the connection has not been established and the function is called it returns
    without doing anything.

    @param[in]   conn  Pointer to ZIConnection to be disconnected
    @return
    - ZI_INFO_SUCCESS

    See @link Connection Connection @endlink for an example
    @sa ziAPIConnect, ziAPIInit, ziAPIDestroy
 */  
ZI_EXPORT ZIResult_enum ziAPIDisconnect(ZIConnection conn);

/// Returns the list of supported implementations
/**
    Returned names are defined by implementations in the linked library and may change depending on software version.

     @param[out] implementations  Pointer to a buffer receiving a newline-delimited list of the names of all
                                  the supported ziAPI implementations. The string is zero-terminated.
     @param[in]  bufferSize       The size of the buffer assigned to the implementations parameter
     @return 
     - ZI_INFO_SUCCESS            on success
     - ZI_ERROR_LENGTH            if the length of the char-buffer given by MaxLen is too small for all elements

     @sa ziAPIConnectEx
 */
ZI_EXPORT ZIResult_enum ziAPIListImplementations(char* implementations, uint32_t bufferSize);

/// Connects to ziDataServer and enables extended ziAPI.
/**
    With apiLevel=ZI_API_VERSION_1 and implementation=NULL, this call is equivalent to plain ::ziAPIConnect.
    With other version and implementation values enables corresponding ziAPI extension and connection using
    different implementation.

     @param[in]  conn            Pointer to the ZIConnection with which the connection should be established
     @param[in]  hostname        Name of the host to which it should be connected, if NULL "localhost" will be used
                                 as default
     @param[in]  port            The number of the port to connect to. If 0 the port of the local ziDataServer will be used
     @param[in]  apiLevel        Specifies the ziAPI compatibility level to use for this connection (1 or 4).
     @param[in]  implementation  Specifies implementation to use for a connection, must be one of the returned by
                                 ziAPIListImplementations or NULL to select default implementation
     @return 
     - ZI_INFO_SUCCESS           on success
     - ZI_ERROR_HOSTNAME         if the given host name could not be found
     - ZI_ERROR_SOCKET_CONNECT   if no connection could be established
     - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
     - ZI_ERROR_SOCKET_INIT      if initialization of the socket failed
     - ZI_ERROR_CONNECTION       when the ziDataServer didn't return the correct answer or requested implementation is not found
                                 or doesn't support requested ziAPI level
     - ZI_ERROR_TIMEOUT          when initial communication timed out

     See @link Connection Connection @endlink for an example
     @sa ziAPIListImplementations, ziAPIConnect, ziAPIDisconnect, ziAPIInit, ziAPIDestroy, ziAPIGetConnectionVersion
 */
ZI_EXPORT ZIResult_enum ziAPIConnectEx(ZIConnection conn, const char* hostname, uint16_t port,
                                       ZIAPIVersion_enum apiLevel, const char* implementation);

/// Returns ziAPI level used for the connection conn.
/**
     @param[in]  conn       Pointer to ZIConnection
     @param[out] apiLevel   Pointer to preallocated ZIAPIVersion_enum, receiving the ziAPI level
     @return 
     - ZI_INFO_SUCCESS      on success
     - ZI_ERROR_CONNECTION  if level can not be determined due to conn is not connected

     @sa ziAPIConnectEx, ziAPIGetVersion
 */
ZI_EXPORT ZIResult_enum ziAPIGetConnectionAPILevel(ZIConnection conn, ZIAPIVersion_enum* apiLevel);

/// Retrieves the revision of ziAPI
/** Sets an unsigned int with the revision (build number) of the ziAPI you are using.

    @param[in]   revision  Pointer to an unsigned int to fill up with the revision.
    @return
    - ZI_INFO_SUCCESS
 */
ZI_EXPORT ZIResult_enum ziAPIGetRevision(unsigned int* revision);

/** @} */  // end of group Connection


/** @defgroup TreeListing Tree
 *  @brief All parameters and streams are organized in a tree. You can list the whole tree, parts of it or single items
 *         using ::ziAPIListNodes or you may update the tree with nodes of newly connected devices by using
 *         ::ziAPIUpdateDevices.
 *  @include ExampleListNodes.c
 *  @{
 */

/// Defines the values of the flags used in ::ziAPIListNodes
enum ZIListNodes_enum {
  /// Default, return a simple listing of the given node immediate descendants.
  ZI_LIST_NODES_NONE = 0x00,
  /// List the nodes recursively
  ZI_LIST_NODES_RECURSIVE = 0x01,
  /// Return absolute paths
  ZI_LIST_NODES_ABSOLUTE = 0x02,
  /// Return only leaf nodes, which means the nodes at the outermost level of the tree
  ZI_LIST_NODES_LEAFSONLY = 0x04,
  /// Return only nodes which are marked as setting
  ZI_LIST_NODES_SETTINGSONLY = 0x08,

  // deprecated
  // **********
#ifdef _MSC_VER
  /// Default, return a simple listing of the given node immediate descendants.
  ZI_LIST_NONE           = 0x00,
  /// List the nodes recursively
  ZI_LIST_RECURSIVE      = 0x01,
  /// Return absolute paths
  ZI_LIST_ABSOLUTE       = 0x02,
  /// Return only leaf nodes, which means the nodes at the outermost level of the tree
  ZI_LIST_LEAFSONLY      = 0x04,
  /// Return only nodes which are marked as setting
  ZI_LIST_SETTINGSONLY   = 0x08
#endif
};

#ifdef _MSC_VER
#pragma deprecated(ZI_LIST_NONE)
#pragma deprecated(ZI_LIST_RECURSIVE)
#pragma deprecated(ZI_LIST_ABSOLUTE)
#pragma deprecated(ZI_LIST_LEAFSONLY)
#pragma deprecated(ZI_LIST_SETTINGSONLY)
#else
__attribute__((deprecated)) const ZIListNodes_enum ZI_LIST_NONE           = ZIListNodes_enum(0x00);
__attribute__((deprecated)) const ZIListNodes_enum ZI_LIST_RECURSIVE      = ZIListNodes_enum(0x01);
__attribute__((deprecated)) const ZIListNodes_enum ZI_LIST_ABSOLUTE       = ZIListNodes_enum(0x02);
__attribute__((deprecated)) const ZIListNodes_enum ZI_LIST_LEAFSONLY      = ZIListNodes_enum(0x04);
__attribute__((deprecated)) const ZIListNodes_enum ZI_LIST_SETTINGSONLY   = ZIListNodes_enum(0x08);
#endif

/// Returns all child nodes found at the specified path
/** This function returns a list of node names found at the specified path. The path may contain wildcards so that
    the returned nodes do not necessarily have to have the same parents. The list is returned in a null-terminated
    char-buffer, each element delimited by a newline. If the maximum length of the buffer (bufferSize) is not 
    sufficient for all elements, nothing will be returned and the return value will be ::ZI_LENGTH.

    @param[in]   conn        Pointer to the ZIConnection for which the node names should be retrieved.
    @param[in]   path        Path for which all children will be returned. The path may contain wildcard characters.
    @param[out]  nodes       Upon call filled with newline-delimited list of the names of all the children found.
                             The string is zero-terminated.
    @param[in]   bufferSize  The length of the buffer used for the nodes output parameter.
    @param[in]   flags       A combination of flags (applied bitwise )as defined in ::ZIListNodes_enum.
    @return
    - ZI_INFO_SUCCESS           on success
    - ZI_ERROR_CONNECTION       when the connection is invalid (not connected) or when a communication error occurred
    - ZI_ERROR_LENGTH           if the path's length exceeds ::MAX_PATH_LEN or the length of the char-buffer for the
                                nodes given by bufferSize is too small for all elements
    - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
    - ZI_ERROR_COMMAND          on an incorrect answer of the server
    - ZI_ERROR_SERVER_INTERNAL  if an internal error occurred in ziDataServer
    - ZI_ERROR_NOTFOUND         if the given path could not be resolved
    - ZI_ERROR_TIMEOUT          when communication timed out

    See @link TreeListing Tree Listing @endlink for an example

    @sa ziAPIUpdate
 */
ZI_EXPORT ZIResult_enum ziAPIListNodes(ZIConnection conn, const char* path, char* nodes, int bufferSize, int flags);

/// Search for the newly connected devices and update the tree
/** This function forces the ziDataServer to search for newly connected devices and to connect to run them

    @param[in]   conn  Pointer to ZIConnection
    @return
    - ZI_INFO_SUCCESS

    @sa ziAPIListNodes
 */
ZI_EXPORT ZIResult_enum ziAPIUpdateDevices(ZIConnection conn);

/// Connect a device to the server.
/** This function connects a device with deviceSerial via the specified deviceInterface for use with the server.

     @param[in]  conn            Pointer to the ZIConnection with which the connection should be established
     @param[in]  deviceSerial    The serial of the device to connect to, e.g., dev2100
     @param[in]  deviceInterface The interface to use for the connection, e.g., USB|1GbE
     @param[in]  interfaceParams Parameters for interface configuration

     @return 
     - ZI_INFO_SUCCESS           on success
     - ZI_ERROR_TIMEOUT          when communication timed out

     @sa ziAPIDisconnectDevice, ziAPIConnect, ziAPIDisconnect, ziAPIInit
 */
ZI_EXPORT ZIResult_enum ziAPIConnectDevice(ZIConnection conn, const char* deviceSerial,
                                           const char* deviceInterface, const char* interfaceParams);

/// Disconnect a device from the server.
/** This function disconnects a device specified by deviceSerial from the server.

     @param[in]  conn            Pointer to the ZIConnection with which the connection should be established
     @param[in]  deviceSerial    The serial of the device to connect to, e.g., dev2100

     @return 
     - ZI_INFO_SUCCESS           on success
     - ZI_ERROR_TIMEOUT          when communication timed out

     @sa ziAPIConnectDevice, ziAPIConnect, ziAPIDisconnect, ziAPIInit
 */
ZI_EXPORT ZIResult_enum ziAPIDisconnectDevice(ZIConnection conn, const char* deviceSerial);

/** @} */  // end of group TreeListing


/** @defgroup Parameters Set and Get Parameters
 *  @brief This section describes several functions for getting and setting parameters of different datatypes.
 *  @{
 */

/// gets the double-type value of the specified node
/** This function retrieves the numerical value of the specified node as an double-type value. The value first found
    is returned if more than one value is available (a wildcard is used in the path).

    @param[in]   conn   Pointer to ZIConnection with which the value should be retrieved
    @param[in]   path   Path to the node holding the value
    @param[out]  value  Pointer to a double in which the value should be written
    @return
    - ZI_INFO_SUCCESS           on success
    - ZI_ERROR_CONNECTION       when the connection is invalid (not connected) or when a communication error occurred
    - ZI_ERROR_LENGTH           if the path's length exceeds MAX_PATH_LEN
    - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
    - ZI_ERROR_COMMAND          on an incorrect answer of the server
    - ZI_ERROR_SERVER_INTERNAL  if an internal error occurred in ziDataServer
    - ZI_ERROR_NOTFOUND         if the given path could not be resolved or no value is attached to the node
    - ZI_ERROR_TIMEOUT          when communication timed out

    @include ExampleSetGetID.c

    @sa ziAPISetValueD, ziAPIGetValueAsPollData
 */

ZI_EXPORT ZIResult_enum ziAPIGetValueD(ZIConnection conn, const char* path, ZIDoubleData* value);

/// gets the integer-type value of the specified node
/** This function retrieves the numerical value of the specified node as an integer-type value. The value first
    found is returned if more than one value is available (a wildcard is used in the path).

    @param[in]   conn   Pointer to ZIConnection with which the value should be retrieved
    @param[in]   path   Path to the node holding the value
    @param[out]  value  Pointer to an 64bit integer in which the value should be written
    @return
    - ZI_INFO_SUCCESS           on success
    - ZI_ERROR_CONNECTION       when the connection is invalid (not connected) or when a communication error occurred
    - ZI_ERROR_LENGTH           if the path's length exceeds MAX_PATH_LEN
    - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
    - ZI_ERROR_COMMAND          on an incorrect answer of the server
    - ZI_ERROR_SERVER_INTERNAL  if an internal error occurred in ziDataServer
    - ZI_ERROR_NOTFOUND         if the given path could not be resolved or no value is attached to the node
    - ZI_ERROR_TIMEOUT          when communication timed out

    @include ExampleSetGetDI.c

    @sa ziAPISetValueI, ziAPIGetValueAsPollData
 */
ZI_EXPORT ZIResult_enum ziAPIGetValueI(ZIConnection conn, const char* path, ZIIntegerData* value);

/// Gets the demodulator sample value of the specified node
/** This function retrieves the value of the specified node as an DemodSample struct. The value first found is
    returned if more than one value is available (a wildcard is used in the path). This function is only applicable
    to paths matching DEMODS/[0-9]+/SAMPLE.

    @param[in]   conn   Pointer to ZIConnection with which the value should be retrieved
    @param[in]   path   Path to the node holding the value
    @param[out]  value  Pointer to a ZIDemodSample struct in which the value should be written
    @return
    - ZI_INFO_SUCCESS           on success
    - ZI_ERROR_CONNECTION       when the connection is invalid (not connected) or when a communication error occurred
    - ZI_ERROR_LENGTH           if the path's length exceeds MAX_PATH_LEN
    - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
    - ZI_ERROR_COMMAND          on an incorrect answer of the server
    - ZI_ERROR_SERVER_INTERNAL  if an internal error occurred in ziDataServer     
    - ZI_ERROR_NOTFOUND         if the given path could not be resolved or no value is attached to the node
    - ZI_ERROR_TIMEOUT          when communication timed out

    @include ExampleGetS.c

    @sa ziAPIGetValueAsPollData
 */
ZI_EXPORT ZIResult_enum ziAPIGetDemodSample(ZIConnection conn, const char* path, ZIDemodSample* value);

/// Gets the Digital I/O sample of the specified node
/** This function retrieves the newest available DIO sample from the specified node. The value first found
    is returned if more than one value is available (a wildcard is used in the path). This function is only
    applicable to nodes ending in "/DIOS/[0-9]+/INPUT".

    @param[in]   conn   Pointer to the ZIConnection with which the value should be retrieved
    @param[in]   path   Path to the node holding the value
    @param[out]  value  Pointer to a ZIDIOSample struct in which the value should be written
    @return
     - ZI_INFO_SUCCESS           on success
     - ZI_ERROR_CONNECTION       when the connection is invalid (not connected) or when a communication error occurred
     - ZI_ERROR_LENGTH           if the Path's Length exceeds MAX_PATH_LEN or the length of the char-buffer for the nodes
                                 given by MaxLen is too small for all elements
     - ZI_ERROR_OVERFLOW         when a FIFO overflow occurred
     - ZI_ERROR_COMMAND          on an incorrect answer of the server
     - ZI_ERROR_SERVER_INTERNAL  if an internal error occurred in the ziServer     
     - ZI_ERROR_NOTFOUND         if the given path could not be resolved or no value is attached to the node
     - ZI_ERROR_TIMEOUT          when communication timed out

    @include ExampleGetDIO.c

    @sa ziAPIGetValueAsPollData
 */
ZI_EXPORT ZIResult_enum ziAPIGetDIOSample(ZIConnection conn, const char* path, ZIDIOSample* value);

/// gets the AuxIn sample of the specified node
/** This function retrieves the newest available AuxIn sample from the specified node. The value first found
    is returned if more than one value is available (a wildcard is used in the path). This function is only
    applicable to nodes ending in "/AUXINS/[0-9]+/SAMPLE".

    @param[in] conn Pointer to the ziConnection with which the Value should be retrieved
    @param[in] path Path to the Node holding the value
    @param[out] value Pointer to an ZIAuxInSample struct in which the value should be written
    @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN or the length of the char-buffer for the nodes
                 given by MaxLen is too small for all elements
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no value is attached to the node
     - ZI_TIMEOUT when communication timed out

    @include ExampleGetAuxIn.c

    @sa ziAPIGetValueAsPollData
 */
ZI_EXPORT ZIResult_enum ziAPIGetAuxInSample(ZIConnection conn, const char* path, ZIAuxInSample* value);

  /// gets the Bytearray value of the specified node
  /**
     This function retrieves the newest available DIO sample from the specified node. The value first found
     is returned if more than one value is available (a wildcard is used in the path).

     @param[in]  conn        Pointer to the ziConnection with which the value should be retrieved
     @param[in]  path        Path to the Node holding the value
     @param[out] buffer      Pointer to a buffer to store the retrieved data in
     @param[out] length      Pointer to an unsigned int to store the length of data in. if an error ocurred or the length
                             of the passed buffer dosn't reach a zero will be returned
     @param[in]  bufferSize  The length of the passed buffer
     
     @return
     - ZI_SUCCESS            on success
     - ZI_CONNECTION         when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH             if the Path's Length exceeds MAX_PATH_LEN or the length of the char-buffer for the nodes
                             given by MaxLen is too small for all elements
     - ZI_OVERFLOW           when a FIFO overflow occurred
     - ZI_COMMAND            on an incorrect answer of the server
     - ZI_SERVER_INTERNAL    if an internal error occurred in the ziServer     
     - ZI_NOTFOUND           if the given path could not be resolved or no value is attached to the node
     - ZI_TIMEOUT            when communication timed out

     @include ExampleGetB.c

     @sa ziAPISetValueB, ziAPIGetValueAsPollData

  */
ZI_EXPORT ZIResult_enum ziAPIGetValueB(ZIConnection conn, const char* path, unsigned char* buffer, unsigned int* length,
                                       unsigned int bufferSize);

  /// asynchronously sets a double-type value to one or more nodes specified in the path
  /**
     This function sets the values of the nodes specified in path to Value. More than one value can be set if
     a wildcard is used. The function sets the value asynchronously which means that after the function returns
     you have no security to which value it is finally set nor at what point in time it is set.

     @param[in] conn Pointer to the ziConnection for which the value(s) will be set
     @param[in] path Path to the Node(s) for which the value(s) will be set to Value
     @param[in] value the double-type value that will be written to the node(s)
     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @include ExampleSetGetDI.c

     @sa ziAPIGetValueD. ziAPISyncSetValueD
  */
ZI_EXPORT ZIResult_enum ziAPISetValueD(ZIConnection conn, const char* path, ZIDoubleData value);

  /// asynchronously sets an integer-type value to one or more nodes specified in a path
  /**
     This function sets the values of the nodes specified in path to Value. More than one value can be set if
     a wildcard is used. The function sets the value asynchronously which means that after the function returns
     you have no security to which value it is finally set nor at what point in time it is set.

     @param[in] conn Pointer to the ziConnection for which the value(s) will be set
     @param[in] path Path to the Node(s) for which the value(s) will be set
     @param[in] value the int-type value that will be written to the node(s)
     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @include ExampleSetGetID.c

     @sa ziAPIGetValueI. ziAPISyncSetValueI

  */
ZI_EXPORT ZIResult_enum ziAPISetValueI(ZIConnection conn, const char* path, ZIIntegerData value);

  /// asynchronously sets the binary-type value of one ore more nodes specified in the path
  /**
     This function sets the values at the nodes specified in a path. More than one value can be set if
     a wildcard is used. The function sets the value asynchronously which means that after the function
     returns you have no security to which value it is finally set nor at what point in time it is set.

     @param[in] conn   Pointer to the ziConnection for which the value(s) will be set
     @param[in] path   Path to the Node(s) for which the value(s) will be set
     @param[in] buffer Pointer to the byte array with the data
     @param[in] length Length of the data in the buffer
     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @include ExampleSetB.c

     @sa ziAPIGetValueB. ziAPISyncSetValueB

  */
ZI_EXPORT ZIResult_enum ziAPISetValueB(ZIConnection conn, const char* path, unsigned char* buffer, unsigned int length);

  /// synchronously sets a double-type value to one or more nodes specified in the path
  /**
     This function sets the values of the nodes specified in path to Value. More than one value can be set if
     a wildcard is used. The function sets the value synchronously. After returning you know that it is set and
     to which value it is set.

     @param[in]    conn   Pointer to the ziConnection for which the value(s) will be set
     @param[in]    path   Path to the Node(s) for which the value(s) will be set to value
     @param[in]    value  Pointer to a double-type containing the value to be written. When the function returns value holds the effectively written value.
     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @sa ziAPIGetValueD, ziAPISetValueD
  */
ZI_EXPORT ZIResult_enum ziAPISyncSetValueD(ZIConnection conn, const char* path, ZIDoubleData* value);

  /// synchronously sets an integer-type value to one or more nodes specified in a path
  /**
     This function sets the values of the nodes specified in path to value. More than one value can be set if
     a wildcard is used. The function sets the value synchronously. After returning you know that it is set and
     to which value it is set.

     @param[in]    conn   Pointer to the ziConnection for which the value(s) will be set
     @param[in]    path   Path to the node(s) for which the value(s) will be set
     @param[in]    value  Pointer to a int-type containing then value to be written. when the function returns 
                          value holds the effectively written value.

     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @sa ziAPIGetValueI, ziAPISetValueI

  */
ZI_EXPORT ZIResult_enum ziAPISyncSetValueI(ZIConnection conn, const char* path, ZIIntegerData* value);

  /// synchronously sets the binary-type value of one ore more nodes specified in the path
  /**
     This function sets the values at the nodes specified in a path. More than one value can be set if a wildcard
     is used. This function sets the value synchronously. After returning you know that it is set and to which
     value it is set.

     @param[in] conn Pointer to the ziConnection for which the value(s) will be set
     @param[in] path Path to the Node(s) for which the value(s) will be set
     @param[in] buffer Pointer to the byte array with the data
     @param[in] length Length of the data in the buffer
     @param[in] bufferSize Length of the data in the buffer
     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_READONLY on attempt to set a read-only node
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     @sa ziAPIGetValueB, ziAPISetValueB

  */
ZI_EXPORT ZIResult_enum ziAPISyncSetValueB(ZIConnection conn, const char* path, uint8_t* buffer, uint32_t* length,
                                           uint32_t bufferSize);

ZI_EXPORT ZIResult_enum ziAPIAsyncSetDoubleData(ZIConnection conn, const char* path, ZIDoubleData value);
ZI_EXPORT ZIResult_enum ziAPIAsyncSetIntegerData(ZIConnection conn, const char* path, ZIIntegerData value);
ZI_EXPORT ZIResult_enum ziAPIAsyncSetByteArray(ZIConnection conn, const char* path, uint8_t* buffer, uint32_t length);

/** @} */  // end of group Parameters


/** @defgroup DataHandling Data Streaming
 *  @brief This section describes how to perform data streaming. It allows for recording at high data rates without sample loss.
 *  @include ExampleSubscription.c
 *  @{
 */

/// This struct holds event data forwarded by the ziDataServer
/**
    ZIEvent is used to give out events like value changes or errors to the user. Event handling functionality is
    provided by ziAPISubscribe and ziAPIUnSubscribe as well as ziAPIPollDataEx.

    @include ExampleProcessEvent.c

    @sa ziAPISubscribe, ziAPIUnSubscribe, ziAPIPollDataEx
 */
struct ZIEvent {
  /// Specifies the type of the data held by the ZIEvent
  ZIValueType_enum valueType;
  /// Number of values available in this event
  uint32_t count;

  /// The path to the node from which the event originates
  uint8_t path[MAX_PATH_LEN];

  /// Convenience pointer to allow for access to the first entry in Data using the correct type
  /// according to ZIEvent.valueType field.
  union {
    /// For convenience. The void field doesn't have a corresponding data type.
    void* untyped;

    /// when valueType == ZI_VALUE_TYPE_DOUBLE_DATA
    ZIDoubleData* doubleData;

    /// when valueType == ZI_VALUE_TYPE_DOUBLE_DATA_TS
    ZIDoubleDataTS* doubleDataTS;

    /// when valueType == ZI_VALUE_TYPE_INTEGER_DATA
    ZIIntegerData* integerData;

    /// when valueType == ZI_VALUE_TYPE_INTEGER_DATA_TS
    ZIIntegerDataTS* integerDataTS;

    /// when valueType == ZI_VALUE_TYPE_BYTE_ARRAY
    ZIByteArray* byteArray;

    /// when valueType == ZI_VALUE_TYPE_BYTE_ARRAY_TS
    ZIByteArrayTS* byteArrayTS;

    /// when valueType == ZI_VALUE_TYPE_TREE_CHANGE_DATA
    ZITreeChangeData* treeChangeData;

    /// when valueType == ZI_VALUE_TYPE_TREE_CHANGE_DATA_OLD
    TreeChange* treeChangeDataOld;

    /// when valueType == ZI_VALUE_TYPE_DEMOD_SAMPLE
    ZIDemodSample* demodSample;

    /// when valueType == ZI_VALUE_TYPE_AUXIN_SAMPLE
    ZIAuxInSample* auxInSample;

    /// when valueType == ZI_VALUE_TYPE_DIO_SAMPLE
    ZIDIOSample* dioSample;

    /// when valueType == ZI_VALUE_TYPE_SCOPE_WAVE
    ZIScopeWave* scopeWave;

    /// when valueType == ZI_VALUE_TYPE_SCOPE_WAVE_OLD
    ScopeWave* scopeWaveOld;

    /// when valueType == ZI_VALUE_TYPE_PWA_WAVE
    ZIPWAWave* pwaWave;
  } value;

  /// The raw value data
  uint8_t data[MAX_EVENT_SIZE];
};

#ifndef __cplusplus
typedef struct ZIEvent ZIEvent;
#endif

/// Allocates ZIEvent structure and returns the pointer to it. Attention!!! It is the client code responsibility
/// to deallocate the structure!
ZI_EXPORT ZIEvent* ziAPIAllocateEventEx();

/// subscribes the nodes given by path for ::ziAPIPollDataEx
/** This function subscribes to nodes so that whenever the value of the node changes the new value can be polled
    using ::ziAPIPollDataEx. By using wildcards or by using a path that is not a leaf node but contains sub nodes,
    more than one leaf can be subscribed to with one function call.

    @param[in] conn Pointer to the ziConnection for which to subscribe for
    @param[in] path Path to the nodes to subscribe
    @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

   See @link DataHandling Data Handling @endlink for an example

   @sa ziAPIUnSubscribe, ziAPIPollDataEx, ziAPIGetValueAsPollData
 */
ZI_EXPORT ZIResult_enum ziAPISubscribe(ZIConnection conn, const char* path);

  /// unsubscribes to the nodes given by path
  /**
      This function is the complement to ::ziAPISubscribe. By using wildcards or by using a path that is not a leaf
      node but contains sub nodes, more than one node can be unsubscribed with one function call.

      @param[in] conn Pointer to the ziConnection for which to unsubscribe for
      @param[in] path Path to the Nodes to unsubscribe
      @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no node given by path is able to hold values
     - ZI_TIMEOUT when communication timed out

     See @link DataHandling Data Handling @endlink for an example

     @sa ziAPISubscribe, ziAPIPollDataEx, ziAPIGetValueAsPollData

  */
ZI_EXPORT ZIResult_enum ziAPIUnSubscribe(ZIConnection conn, const char* path);
  /// checks if an event is available to read
  /**     
     This function returns immediately if an event is pending. Otherwise it waits for an event for up to 
     milliseconds. All value changes that occur in nodes that have been subscribed to or in children of nodes that
     have been subscribed to are sent from the ziServer to the ziAPI session. For a description of how the data
     are available in the struct, refer the documentation of struct ziEvent. When no event was available within
     TimeOut milliseconds, the ziEvent::Type field will be ZI_DATA_NONE and the ziEvent::Count field will be zero.
     Otherwise these fields hold the values corresponding to the event occurred.

     @param[in]  conn     Pointer to the ::ZIConnection for which events should be received
     @param[out] ev       Pointer to a ::ZIEvent struct in which the received event will be written
     @param[in]  timeOutMilliseconds Time to wait for an event in milliseconds. If -1 it will wait forever, if 0 the function
                          returns immediately.
     @return
     - ZI_SUCCESS     on success
     - ZI_CONNECTION  when the connection is invalid (not connected) or when a communication error occurred
     - ZI_OVERFLOW    when a FIFO overflow occurred

     See @link DataHandling Data Handling @endlink for an example

     @sa ziAPISubscribe, ziAPIUnSubscribe, ziAPIGetValueAsPollData, ziEvent

  */
ZI_EXPORT ZIResult_enum ziAPIPollDataEx(ZIConnection conn, ZIEvent* ev, uint32_t timeOutMilliseconds);

  /// triggers a value request, which will be given back on the poll event queue
  /**
     Use this function to receive the value of one or more nodes as one or more events using ::ziAPIPollDataEx, even
     when the node is not subscribed or no value change has occured.
     
     @param[in] conn Pointer to the ::ZIConnection with which the value should be retrieved
     @param[in] path Path to the Node holding the value

     @return
     - ZI_SUCCESS on success
     - ZI_CONNECTION when the connection is invalid (not connected) or when a communication error occurred
     - ZI_LENGTH if the Path's Length exceeds MAX_PATH_LEN or the length of the char-buffer for the nodes
                 given by MaxLen is too small for all elements
     - ZI_OVERFLOW when a FIFO overflow occurred
     - ZI_COMMAND on an incorrect answer of the server
     - ZI_SERVER_INTERNAL if an internal error occurred in the ziServer     
     - ZI_NOTFOUND if the given path could not be resolved or no value is attached to the node
     - ZI_TIMEOUT when communication timed out

     See @link DataHandling Data Handling @endlink for an example

     @sa ziAPISubscribe, ziAPIUnSubscribe, ziAPIPollDataEx

   */
ZI_EXPORT ZIResult_enum ziAPIGetValueAsPollData(ZIConnection conn, const char* path);

/** @} */  // end of group DataHandling



/** @defgroup ErrorHandling Error Handling
 *  @brief all functions return ::ZIResult_enum. To retrieve a full-text description of such a status one function
 *         is provided: ::ziAPIGetError.
 *  @{
 */

/// returns a description and the severity for a ::ZIResult_enum
/** This function returns a static char pointer to a description string for the given ::ZIResult_enum error code.
    It also provides a parameter returning the severity (info, warning, error). If the given error code does
    not exist a description for an unknown error and the base for an error will be returned. If a description
    or the base is not needed NULL may be passed.

    @param[in]  result  A ::ZIResult_enum for which the description or base will be returned
    @param[out] buffer  A pointer to a char array to return the description. May be NULL if no description is needed.
    @param[out] base    The severity for the provided Status parameter:
    - ZI_INFO_BASE for infos
    - ZI_WARNING_BASE for warnings
    - ZI_ERROR_BASE for errors

    @return
    - ZI_SUCCESS
 */
ZI_EXPORT ZIResult_enum ziAPIGetError(ZIResult_enum result, char** buffer, int* base);

/** @} */  // end of group ErrorHandling


ZI_EXPORT ZIResult_enum ReadMEMFile(const char* filename, char* buffer, int32_t bufferSize, int32_t* bytesUsed);


// deprecated symbols
// ******************
#ifdef __GNUC__
  #define DEPRECATED(decl) decl __attribute__ ((deprecated))
#elif defined(_MSC_VER)
  #define DEPRECATED(decl) __declspec(deprecated) decl
#else
  #pragma message("WARNING: You need to implement DEPRECATED for this compiler")
  #define DEPRECATED(decl) decl
#endif

// We don't want to get the deprecated warnings for the ziAPI.h itself
#ifdef __GNUC__
#if __GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 6
// Only supported by GCC >= 4.6
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
// Visual C++ specific
#pragma warning(push)
// 4996 - declared deprecated
#pragma warning(disable:4996)
#endif

typedef ZIValueType_enum DEPRECATED(ziAPIDataType);
typedef ZITimeStamp DEPRECATED(ziTimeStampType);
typedef ZIResult_enum DEPRECATED(ZI_STATUS);
typedef ZIConnection DEPRECATED(ziConnection);
typedef ZIDoubleData DEPRECATED(ziDoubleType);
typedef ZIIntegerData DEPRECATED(ziIntegerType);

/// the DemodSample struct is holding data for the ZI_DATA_DEMODSAMPLE data type
struct DEPRECATED(DemodSample {
  /// Time stamp at which the sample has been measured
  ziTimeStampType TimeStamp;

  /// X part of the sample
  double X;
  /// Y part of the sample
  double Y;

  /// Frequency at that sample
  double Frequency;
  /// Phase at that sample
  double Phase;

  /// the current bits of the DIO
  unsigned int DIOBits;

  /// reserved uint to maintain 8bytes alignment
  unsigned int Reserved;

  /// values of Aux inputs
  double AuxIn0;
  double AuxIn1;
});

#ifndef __cplusplus
typedef struct DemodSample DEPRECATED(DemodSample);
#endif

/// the AuxInSample struct is holding data for the ZI_DATA_AUXINSAMPLE data type
struct DEPRECATED(AuxInSample {
  /// Time stamp at which the values have been measured
  ziTimeStampType TimeStamp;

  /// Channel 0 voltage
  double Ch0;
  /// Channel 1 voltage
  double Ch1;
});

#ifndef __cplusplus
typedef struct AuxInSample DEPRECATED(AuxInSample);
#endif

/// the DIOSample struct is holding data for the ZI_DATA_DIOSAMPLE data type
struct DEPRECATED(DIOSample {
  /// Time stamp at which the values have been measured
  ziTimeStampType TimeStamp;

  /// the digital values
  unsigned int Bits;

  /// alignment to 8 bytes
  unsigned int Reserved;
});

#ifndef __cplusplus
typedef struct DIOSample DEPRECATED(DIOSample);
#endif

/// TREE_ACTION defines the values for the TreeChange::Action Variable
enum TREE_ACTION {
#ifdef _MSC_VER
  /// a tree has been removed
  TREE_ACTION_REMOVE = 0,

  /// a tree has been added
  TREE_ACTION_ADD = 1,

  /// a tree has changed
  TREE_ACTION_CHANGE = 2
#endif
};

#ifdef _MSC_VER
#pragma deprecated(TREE_ACTION_REMOVE)
#pragma deprecated(TREE_ACTION_ADD)
#pragma deprecated(TREE_ACTION_CHANGE)
#else
__attribute__((deprecated)) const TREE_ACTION TREE_ACTION_REMOVE   = TREE_ACTION(0);
__attribute__((deprecated)) const TREE_ACTION TREE_ACTION_ADD      = TREE_ACTION(1);
__attribute__((deprecated)) const TREE_ACTION TREE_ACTION_CHANGE   = TREE_ACTION(2);
#endif

#ifdef _MSC_VER
// Visual C++ specific
#pragma warning(push)
#pragma warning(disable:4200)
#endif

/// the ByteArrayData struct is holding data for the ZI_DATA_BYTEARRAY data type
struct DEPRECATED(ByteArrayData {
  /// length of the data readable from the Bytes field
  unsigned int Len;
  /// the data itself. The array has the size given in Len
  unsigned char Bytes[0];
});

#ifndef __cplusplus
typedef struct ByteArrayData DEPRECATED(ByteArrayData);
#endif

#ifdef _MSC_VER
// Visual C++ specific
#pragma warning(pop)
#endif

/// This struct holds event data forwarded by the ziDataServer
/**
 *  @ingroup DataHandling
    ziEvent is used to give out events like value changes or errors to the user. Event handling functionality is
    provided by ziAPISubscribe and ziAPIUnSubscribe as well as ziAPIPollDataEx.
     
    @include ExampleProcessEvent.c
    @sa ziAPISubscribe, ziAPIUnSubscribe, ziAPIPollDataEx
 */
struct DEPRECATED(ziEvent {
    /// Specifies the type of the data held by the ziEvent
    ziAPIDataType Type;
    /// Number of values available in this event
    unsigned int Count;

    /// The path to the node from which the event originates
    unsigned char Path[MAX_PATH_LEN];

    /// Convenience pointer to allow for access to the first entry in Data using the correct type
    /// according to ziEvent::Type field.
    union Val {
      /// For convenience. The void field doesn't have a corresponding data type.
      void* Void;

      /// Data of type ZI_DATA_DEMODSAMPLE
      DemodSample* SampleDemod;

      /// Data of type ZI_DATA_AUXINSAMPLE
      AuxInSample* SampleAuxIn;

      /// Data of type ZI_DATA_DIOSAMPLE
      DIOSample* SampleDIO;

      /// Data of type ZI_DATA_DOUBLE
      ziDoubleType* Double;

      /// Data of type ZI_DATA_INTEGER
      ziIntegerType* Integer;

      /// Data of type ZI_DATA_TREE_CHANGED
      TreeChange* Tree;

      /// Data of type ZI_DATA_BYTEARRAY
      ByteArrayData* ByteArray;

      /// Data of type ZI_DATA_SCOPEWAVE
      ScopeWave* Wave;

    } Val;

    /// The raw value data
    unsigned char Data[ MAX_EVENT_SIZE ];
  });

#ifndef __cplusplus
typedef struct ziEvent DEPRECATED(ziEvent);
#endif

DEPRECATED(inline ziEvent* ziAPIAllocateEvent());
inline ziEvent* ziAPIAllocateEvent() {
  return (ziEvent*)ziAPIAllocateEventEx();
}


/// checks if an event is available to read
/**
 *  @deprecated
    @ingroup DataHandling
    This function returns immediately if an event is pending. Otherwise it waits for an event for up to TimeOut
    milliseconds. All value changes that occur in nodes that have been subscribed to or in children of nodes that
    have been subscribed to are sent from the ziServer to the ziAPI session. For a description of how the data
    are available in the struct, refer the documentation of struct ziEvent. When no event was available within
    TimeOut milliseconds, the ziEvent::Type field will be ZI_DATA_NONE and the ziEvent::Count field will be zero.
    Otherwise these fields hold the values corresponding to the event occurred.

    @param[in]  conn     Pointer to the ::ZIConnection for which events should be received
    @param[out] ev       Pointer to a ::ziEvent struct in which the received event will be written
    @param[in]  timeOut  Time to wait for an event in milliseconds. If -1 it will wait forever, if 0 the function
                          returns immediately.
    @return
     - ZI_SUCCESS     on success
     - ZI_CONNECTION  when the connection is invalid (not connected) or when a communication error occurred
     - ZI_OVERFLOW    when a FIFO overflow occurred

    See @link DataHandling Data Handling @endlink for an example

    @sa ziAPISubscribe, ziAPIUnSubscribe, ziAPIGetValueAsPollData, ziEvent
 */
DEPRECATED(inline ZIResult_enum ziAPIPollData(ZIConnection conn, ziEvent* ev, int timeOut));
inline ZIResult_enum ziAPIPollData(ZIConnection conn, ziEvent* ev, int timeOut) {
  return ziAPIPollDataEx(conn, (ZIEvent*)ev, timeOut);
}

/// @deprecated
/// @ingroup Parameters
DEPRECATED(inline ZIResult_enum ziAPIGetValueS(ZIConnection conn, char* path, DemodSample* value));
inline ZIResult_enum ziAPIGetValueS(ZIConnection conn, char* path, DemodSample* value) {
  return ziAPIGetDemodSample(conn, path, (ZIDemodSample*)value);
}

/// @deprecated
/// @ingroup Parameters
DEPRECATED(inline ZIResult_enum ziAPIGetValueDIO(ZIConnection conn, char* path, DIOSample* value));
inline ZIResult_enum ziAPIGetValueDIO(ZIConnection conn, char* path, DIOSample* value) {
  return ziAPIGetDIOSample(conn, path, (ZIDIOSample*)value);
}

/// @deprecated
/// @ingroup Parameters
DEPRECATED(inline ZIResult_enum ziAPIGetValueAuxIn(ZIConnection conn, char* path, AuxInSample* value));
inline ZIResult_enum ziAPIGetValueAuxIn(ZIConnection conn, char* path, AuxInSample* value) {
  return ziAPIGetAuxInSample(conn, path, (ZIAuxInSample*)value);
}

/// @deprecated
/// converts a ziTimeStampType into a double-type representing seconds
/**
     @param[in] TS the timestamp to convert to seconds
     @return The timestamp in seconds as a double
*/
DEPRECATED(double ZI_EXPORT ziAPISecondsTimeStamp(ziTimeStampType TS));

#define ZI_ERROR(dummy, result) return result;

#ifdef __GNUC__
#if __GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 6
// Only supported by GCC >= 4.6
#pragma GCC diagnostic pop
#else
// There is no way for GCC < 4.6 to restore the previously set diagnostic level (push/pop is not supported),
// therefore we just set it to the default 'warning' level. Unwanted side effect - it will be set to warning
// for the ramining of any file that includes ziAPI.h, even if it was changed via command line or with another
// pragma.
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#endif
#elif defined(_MSC_VER)
// Visual C++ specific
// restore 4996 - declared deprecated
#pragma warning(pop)
#endif

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // __ZIAPI_H__
