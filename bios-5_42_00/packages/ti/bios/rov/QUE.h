/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-v53
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_bios_rov_QUE__include
#define ti_bios_rov_QUE__include

#ifndef __nested__
#define __nested__
#define ti_bios_rov_QUE__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_bios_rov_QUE___VERS 150


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/bios/rov/package/package.defs.h>

#include <xdc/runtime/IModule.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* QUE_Elem */
struct ti_bios_rov_QUE_QUE_Elem {
    ti_bios_rov_QUE_QUE_Elem* next;
    ti_bios_rov_QUE_QUE_Elem* prev;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_bios_rov_QUE_Module__diagsEnabled;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__diagsEnabled ti_bios_rov_QUE_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_bios_rov_QUE_Module__diagsIncluded;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__diagsIncluded ti_bios_rov_QUE_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16* CT__ti_bios_rov_QUE_Module__diagsMask;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__diagsMask ti_bios_rov_QUE_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_bios_rov_QUE_Module__gateObj;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__gateObj ti_bios_rov_QUE_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_bios_rov_QUE_Module__gatePrms;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__gatePrms ti_bios_rov_QUE_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_bios_rov_QUE_Module__id;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__id ti_bios_rov_QUE_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_bios_rov_QUE_Module__loggerDefined;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerDefined ti_bios_rov_QUE_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_bios_rov_QUE_Module__loggerObj;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerObj ti_bios_rov_QUE_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_bios_rov_QUE_Module__loggerFxn0;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerFxn0 ti_bios_rov_QUE_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_bios_rov_QUE_Module__loggerFxn1;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerFxn1 ti_bios_rov_QUE_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_bios_rov_QUE_Module__loggerFxn2;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerFxn2 ti_bios_rov_QUE_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_bios_rov_QUE_Module__loggerFxn4;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerFxn4 ti_bios_rov_QUE_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_bios_rov_QUE_Module__loggerFxn8;
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__loggerFxn8 ti_bios_rov_QUE_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_bios_rov_QUE_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_bios_rov_QUE_Module__startupDoneFxn ti_bios_rov_QUE_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_bios_rov_QUE_Object__count;
__extern __FAR__ const CT__ti_bios_rov_QUE_Object__count ti_bios_rov_QUE_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_bios_rov_QUE_Object__heap;
__extern __FAR__ const CT__ti_bios_rov_QUE_Object__heap ti_bios_rov_QUE_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_bios_rov_QUE_Object__sizeof;
__extern __FAR__ const CT__ti_bios_rov_QUE_Object__sizeof ti_bios_rov_QUE_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_bios_rov_QUE_Object__table;
__extern __FAR__ const CT__ti_bios_rov_QUE_Object__table ti_bios_rov_QUE_Object__table__C;


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_bios_rov_QUE_Module_startup( state ) -1

/* Handle__label__S */
xdc__CODESECT(ti_bios_rov_QUE_Handle__label__S, "ti_bios_rov_QUE_Handle__label")
__extern xdc_runtime_Types_Label* ti_bios_rov_QUE_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab );

/* Module__startupDone__S */
xdc__CODESECT(ti_bios_rov_QUE_Module__startupDone__S, "ti_bios_rov_QUE_Module__startupDone")
__extern xdc_Bool ti_bios_rov_QUE_Module__startupDone__S( void );

/* Object__create__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__create__S, "ti_bios_rov_QUE_Object__create")
__extern xdc_Ptr ti_bios_rov_QUE_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb );

/* Object__delete__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__delete__S, "ti_bios_rov_QUE_Object__delete")
__extern xdc_Void ti_bios_rov_QUE_Object__delete__S( xdc_Ptr instp );

/* Object__destruct__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__destruct__S, "ti_bios_rov_QUE_Object__destruct")
__extern xdc_Void ti_bios_rov_QUE_Object__destruct__S( xdc_Ptr objp );

/* Object__get__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__get__S, "ti_bios_rov_QUE_Object__get")
__extern xdc_Ptr ti_bios_rov_QUE_Object__get__S( xdc_Ptr oarr, xdc_Int i );

/* Object__first__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__first__S, "ti_bios_rov_QUE_Object__first")
__extern xdc_Ptr ti_bios_rov_QUE_Object__first__S( void );

/* Object__next__S */
xdc__CODESECT(ti_bios_rov_QUE_Object__next__S, "ti_bios_rov_QUE_Object__next")
__extern xdc_Ptr ti_bios_rov_QUE_Object__next__S( xdc_Ptr obj );

/* Params__init__S */
xdc__CODESECT(ti_bios_rov_QUE_Params__init__S, "ti_bios_rov_QUE_Params__init")
__extern xdc_Void ti_bios_rov_QUE_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz );

/* Proxy__abstract__S */
xdc__CODESECT(ti_bios_rov_QUE_Proxy__abstract__S, "ti_bios_rov_QUE_Proxy__abstract")
__extern xdc_Bool ti_bios_rov_QUE_Proxy__abstract__S( void );

/* Proxy__delegate__S */
xdc__CODESECT(ti_bios_rov_QUE_Proxy__delegate__S, "ti_bios_rov_QUE_Proxy__delegate")
__extern xdc_Ptr ti_bios_rov_QUE_Proxy__delegate__S( void );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_bios_rov_QUE_Module_startupDone() ti_bios_rov_QUE_Module__startupDone__S()

/* Object_heap */
#define ti_bios_rov_QUE_Object_heap() ti_bios_rov_QUE_Object__heap__C

/* Module_heap */
#define ti_bios_rov_QUE_Module_heap() ti_bios_rov_QUE_Object__heap__C

/* Module_id */
static inline CT__ti_bios_rov_QUE_Module__id ti_bios_rov_QUE_Module_id( void ) 
{
    return ti_bios_rov_QUE_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_bios_rov_QUE_Module_hasMask( void ) 
{
    return ti_bios_rov_QUE_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_bios_rov_QUE_Module_getMask( void ) 
{
    return ti_bios_rov_QUE_Module__diagsMask__C != NULL ? *ti_bios_rov_QUE_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_bios_rov_QUE_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_bios_rov_QUE_Module__diagsMask__C != NULL) *ti_bios_rov_QUE_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_bios_rov_QUE__top__
#undef __nested__
#endif

#endif /* ti_bios_rov_QUE__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_bios_rov_QUE__internalaccess))

#ifndef ti_bios_rov_QUE__include_state
#define ti_bios_rov_QUE__include_state


#endif /* ti_bios_rov_QUE__include_state */

#endif

/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_bios_rov_QUE__nolocalnames)

#ifndef ti_bios_rov_QUE__localnames__done
#define ti_bios_rov_QUE__localnames__done

/* module prefix */
#define QUE_QUE_Elem ti_bios_rov_QUE_QUE_Elem
#define QUE_Module_name ti_bios_rov_QUE_Module_name
#define QUE_Module_id ti_bios_rov_QUE_Module_id
#define QUE_Module_startup ti_bios_rov_QUE_Module_startup
#define QUE_Module_startupDone ti_bios_rov_QUE_Module_startupDone
#define QUE_Module_hasMask ti_bios_rov_QUE_Module_hasMask
#define QUE_Module_getMask ti_bios_rov_QUE_Module_getMask
#define QUE_Module_setMask ti_bios_rov_QUE_Module_setMask
#define QUE_Object_heap ti_bios_rov_QUE_Object_heap
#define QUE_Module_heap ti_bios_rov_QUE_Module_heap

#endif /* ti_bios_rov_QUE__localnames__done */
#endif
