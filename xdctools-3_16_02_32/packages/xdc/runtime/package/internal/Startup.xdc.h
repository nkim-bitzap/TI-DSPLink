/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u16
 */

#ifndef xdc_runtime_Startup__INTERNAL__
#define xdc_runtime_Startup__INTERNAL__

#ifndef xdc_runtime_Startup__internalaccess
#define xdc_runtime_Startup__internalaccess
#endif

#include <xdc/runtime/Startup.h>

#undef xdc_FILE__
#ifndef xdc_FILE
#define xdc_FILE__ NULL
#else
#define xdc_FILE__ xdc_FILE
#endif

/* exec */
#undef xdc_runtime_Startup_exec
#define xdc_runtime_Startup_exec xdc_runtime_Startup_exec__F

/* rtsDone */
#undef xdc_runtime_Startup_rtsDone
#define xdc_runtime_Startup_rtsDone xdc_runtime_Startup_rtsDone__F

/* reset */
#define Startup_reset xdc_runtime_Startup_reset__I

/* startMods */
#define Startup_startMods xdc_runtime_Startup_startMods__I

/* Module_startup */
#undef xdc_runtime_Startup_Module_startup
#define xdc_runtime_Startup_Module_startup xdc_runtime_Startup_Module_startup__F

/* Instance_init */
#undef xdc_runtime_Startup_Instance_init
#define xdc_runtime_Startup_Instance_init xdc_runtime_Startup_Instance_init__F

/* Instance_finalize */
#undef xdc_runtime_Startup_Instance_finalize
#define xdc_runtime_Startup_Instance_finalize xdc_runtime_Startup_Instance_finalize__F

/* module */
#define Startup_module ((xdc_runtime_Startup_Module_State *)(xdc__MODOBJADDR__(xdc_runtime_Startup_Module__state__V)))
#if !defined(__cplusplus) || !defined(xdc_runtime_Startup__cplusplus)
#define module ((xdc_runtime_Startup_Module_State *)(xdc__MODOBJADDR__(xdc_runtime_Startup_Module__state__V)))
#endif
/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Startup_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Startup_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Startup_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Startup_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Startup_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Startup_Module__loggerObj__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Startup_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Startup_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Startup_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Startup_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Startup_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Startup_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Startup_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Startup_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Startup_Module_GateProxy_query


#endif /* xdc_runtime_Startup__INTERNAL____ */