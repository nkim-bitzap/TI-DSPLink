/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-u15
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.*;

public class ti_catalog_arm_lm3init
{
    static final String VERS = "@(#) xdc-u15\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "xdc.rov");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("ti.catalog.arm.lm3init.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("ti.catalog.arm.lm3init", new Value.Obj("ti.catalog.arm.lm3init", pkgP));
    }

    void Boot$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("ti.catalog.arm.lm3init.Boot.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("ti.catalog.arm.lm3init.Boot", new Value.Obj("ti.catalog.arm.lm3init.Boot", po));
        pkgV.bind("Boot", vo);
        // decls 
        spo = (Proto.Obj)om.bind("ti.catalog.arm.lm3init.Boot$$ModuleView", new Proto.Obj());
        om.bind("ti.catalog.arm.lm3init.Boot.ModuleView", new Proto.Str(spo, true));
        om.bind("ti.catalog.arm.lm3init.Boot.SysDiv", new Proto.Enm("ti.catalog.arm.lm3init.Boot.SysDiv"));
        om.bind("ti.catalog.arm.lm3init.Boot.PwmDiv", new Proto.Enm("ti.catalog.arm.lm3init.Boot.PwmDiv"));
        om.bind("ti.catalog.arm.lm3init.Boot.XtalFreq", new Proto.Enm("ti.catalog.arm.lm3init.Boot.XtalFreq"));
        om.bind("ti.catalog.arm.lm3init.Boot.OscSrc", new Proto.Enm("ti.catalog.arm.lm3init.Boot.OscSrc"));
        om.bind("ti.catalog.arm.lm3init.Boot.LdoOut", new Proto.Enm("ti.catalog.arm.lm3init.Boot.LdoOut"));
    }

    void Boot$$CONSTS()
    {
        // module Boot
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_1", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_1", xdc.services.intern.xsr.Enum.intValue(0x00000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_2", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_2", xdc.services.intern.xsr.Enum.intValue(0x00800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_3", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_3", xdc.services.intern.xsr.Enum.intValue(0x01000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_4", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_4", xdc.services.intern.xsr.Enum.intValue(0x01800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_5", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_5", xdc.services.intern.xsr.Enum.intValue(0x02000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_6", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_6", xdc.services.intern.xsr.Enum.intValue(0x02800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_7", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_7", xdc.services.intern.xsr.Enum.intValue(0x03000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_8", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_8", xdc.services.intern.xsr.Enum.intValue(0x03800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_9", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_9", xdc.services.intern.xsr.Enum.intValue(0x04000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_10", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_10", xdc.services.intern.xsr.Enum.intValue(0x04800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_11", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_11", xdc.services.intern.xsr.Enum.intValue(0x05000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_12", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_12", xdc.services.intern.xsr.Enum.intValue(0x05800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_13", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_13", xdc.services.intern.xsr.Enum.intValue(0x06000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_14", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_14", xdc.services.intern.xsr.Enum.intValue(0x06800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_15", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_15", xdc.services.intern.xsr.Enum.intValue(0x07000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.SYSDIV_16", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.SYSDIV_16", xdc.services.intern.xsr.Enum.intValue(0x07800000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_2", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_2", xdc.services.intern.xsr.Enum.intValue(0x00000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_4", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_4", xdc.services.intern.xsr.Enum.intValue(0x00020000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_8", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_8", xdc.services.intern.xsr.Enum.intValue(0x00040000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_16", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_16", xdc.services.intern.xsr.Enum.intValue(0x00060000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_32", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_32", xdc.services.intern.xsr.Enum.intValue(0x00080000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.PWMDIV_64", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.PWMDIV_64", xdc.services.intern.xsr.Enum.intValue(0x000A0000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_1MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_1MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_1_84MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_1_84MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000040L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_2MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_2MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000080L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_2_45MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_2_45MHZ", xdc.services.intern.xsr.Enum.intValue(0x000000C0L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_3_57MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_3_57MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000100L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_3_68MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_3_68MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000140L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_4MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_4MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000180L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_4_09MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_4_09MHZ", xdc.services.intern.xsr.Enum.intValue(0x000001C0L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_4_91MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_4_91MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000200L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_5MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_5MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000240L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_5_12MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_5_12MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000280L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_6MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_6MHZ", xdc.services.intern.xsr.Enum.intValue(0x000002C0L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_6_14MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_6_14MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000300L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_7_37MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_7_37MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000340L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_8MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_8MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000380L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_8_19MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_8_19MHZ", xdc.services.intern.xsr.Enum.intValue(0x000003C0L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_10MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_10MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000400L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_12MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_12MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000440L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_12_2MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_12_2MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000480L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_13_5MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_13_5MHZ", xdc.services.intern.xsr.Enum.intValue(0x000004C0L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_14_3MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_14_3MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000500L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_16MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_16MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000540L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.XTAL_16_3MHZ", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.XTAL_16_3MHZ", xdc.services.intern.xsr.Enum.intValue(0x00000580L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.OSCSRC_MAIN", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.OSCSRC_MAIN", xdc.services.intern.xsr.Enum.intValue(0x00000000L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.OSCSRC_INT", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.OSCSRC_INT", xdc.services.intern.xsr.Enum.intValue(0x00000010L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.OSCSRC_INT4", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.OSCSRC_INT4", xdc.services.intern.xsr.Enum.intValue(0x00000020L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.OSCSRC_30", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.OSCSRC_30", xdc.services.intern.xsr.Enum.intValue(0x00000030L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_55V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_55V", xdc.services.intern.xsr.Enum.intValue(0x0000001FL)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_60V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_60V", xdc.services.intern.xsr.Enum.intValue(0x0000001EL)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_65V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_65V", xdc.services.intern.xsr.Enum.intValue(0x0000001DL)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_70V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_70V", xdc.services.intern.xsr.Enum.intValue(0x0000001CL)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_75V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_75V", xdc.services.intern.xsr.Enum.intValue(0x0000001BL)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_25V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_25V", xdc.services.intern.xsr.Enum.intValue(0x00000005L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_30V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_30V", xdc.services.intern.xsr.Enum.intValue(0x00000004L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_35V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_35V", xdc.services.intern.xsr.Enum.intValue(0x00000003L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_40V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_40V", xdc.services.intern.xsr.Enum.intValue(0x00000002L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_45V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_45V", xdc.services.intern.xsr.Enum.intValue(0x00000001L)+0));
        om.bind("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_50V", xdc.services.intern.xsr.Enum.make((Proto.Enm)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), "ti.catalog.arm.lm3init.Boot.LDOPCTL_2_50V", xdc.services.intern.xsr.Enum.intValue(0x00000000L)+0));
    }

    void Boot$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

    }

    void Boot$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Boot$$SIZES()
    {
    }

    void Boot$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/arm/lm3init/Boot.xs");
        om.bind("ti.catalog.arm.lm3init.Boot$$capsule", cap);
        po = (Proto.Obj)om.findStrict("ti.catalog.arm.lm3init.Boot.Module", "ti.catalog.arm.lm3init");
        po.init("ti.catalog.arm.lm3init.Boot.Module", $$Module);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("rovViewInfo", (Proto)om.findStrict("xdc.rov.ViewInfo.Instance", "ti.catalog.arm.lm3init"), $$UNDEF, "wh");
                po.addFld("configureClock", $$T_Bool, false, "wh");
                po.addFld("sysClockDivEnable", $$T_Bool, false, "wh");
                po.addFld("sysClockDiv", (Proto)om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"), om.find("ti.catalog.arm.lm3init.Boot.SYSDIV_1"), "wh");
                po.addFld("pwmClockDivEnable", $$T_Bool, false, "wh");
                po.addFld("pwmClockDiv", (Proto)om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"), om.find("ti.catalog.arm.lm3init.Boot.PWMDIV_2"), "wh");
                po.addFld("xtal", (Proto)om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"), om.find("ti.catalog.arm.lm3init.Boot.XTAL_1MHZ"), "wh");
                po.addFld("oscSrc", (Proto)om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"), om.find("ti.catalog.arm.lm3init.Boot.OSCSRC_MAIN"), "wh");
                po.addFld("pllBypass", $$T_Bool, false, "wh");
                po.addFld("pllOutEnable", $$T_Bool, false, "wh");
                po.addFld("ioscDisable", $$T_Bool, false, "wh");
                po.addFld("moscDisable", $$T_Bool, false, "wh");
                po.addFld("configureLdo", $$T_Bool, false, "wh");
                po.addFld("ldoOut", (Proto)om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"), om.find("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_50V"), "wh");
                po.addFld("bootCodeSection", $$T_Str, ".bootCodeSection", "rh");
                po.addFld("ulConfig", Proto.Elm.newCNum("(xdc_UInt)"), $$UNDEF, "wh");
                fxn = Global.get(cap, "module$use");
                if (fxn != null) om.bind("ti.catalog.arm.lm3init.Boot$$module$use", true);
                if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
                fxn = Global.get(cap, "module$meta$init");
                if (fxn != null) om.bind("ti.catalog.arm.lm3init.Boot$$module$meta$init", true);
                if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
                fxn = Global.get(cap, "module$validate");
                if (fxn != null) om.bind("ti.catalog.arm.lm3init.Boot$$module$validate", true);
                if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        // struct Boot.ModuleView
        po = (Proto.Obj)om.findStrict("ti.catalog.arm.lm3init.Boot$$ModuleView", "ti.catalog.arm.lm3init");
        po.init("ti.catalog.arm.lm3init.Boot.ModuleView", null);
                po.addFld("$hostonly", $$T_Num, 1, "r");
                po.addFld("configureClock", $$T_Bool, $$UNDEF, "w");
                po.addFld("sysClockDivEnable", $$T_Bool, $$UNDEF, "w");
                po.addFld("sysClockDiv", $$T_Str, $$UNDEF, "w");
                po.addFld("pwmClockDivEnable", $$T_Bool, $$UNDEF, "w");
                po.addFld("pwmClockDiv", $$T_Str, $$UNDEF, "w");
                po.addFld("xtal", $$T_Str, $$UNDEF, "w");
                po.addFld("oscSrc", $$T_Str, $$UNDEF, "w");
                po.addFld("pllBypass", $$T_Bool, $$UNDEF, "w");
                po.addFld("pllOutEnable", $$T_Bool, $$UNDEF, "w");
                po.addFld("ioscDisable", $$T_Bool, $$UNDEF, "w");
                po.addFld("moscDisable", $$T_Bool, $$UNDEF, "w");
                po.addFld("configureLdo", $$T_Bool, $$UNDEF, "w");
                po.addFld("ldoOut", $$T_Str, $$UNDEF, "w");
    }

    void Boot$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("ti.catalog.arm.lm3init.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "ti.catalog.arm.lm3init"));
        Scriptable cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "ti/catalog/arm/lm3init/package.xs");
        om.bind("xdc.IPackage$$capsule", cap);
        Object fxn;
                fxn = Global.get(cap, "init");
                if (fxn != null) pkgP.addFxn("init", (Proto.Fxn)om.findStrict("xdc.IPackage$$init", "ti.catalog.arm.lm3init"), fxn);
                fxn = Global.get(cap, "close");
                if (fxn != null) pkgP.addFxn("close", (Proto.Fxn)om.findStrict("xdc.IPackage$$close", "ti.catalog.arm.lm3init"), fxn);
                fxn = Global.get(cap, "validate");
                if (fxn != null) pkgP.addFxn("validate", (Proto.Fxn)om.findStrict("xdc.IPackage$$validate", "ti.catalog.arm.lm3init"), fxn);
                fxn = Global.get(cap, "exit");
                if (fxn != null) pkgP.addFxn("exit", (Proto.Fxn)om.findStrict("xdc.IPackage$$exit", "ti.catalog.arm.lm3init"), fxn);
                fxn = Global.get(cap, "getLibs");
                if (fxn != null) pkgP.addFxn("getLibs", (Proto.Fxn)om.findStrict("xdc.IPackage$$getLibs", "ti.catalog.arm.lm3init"), fxn);
                fxn = Global.get(cap, "getSects");
                if (fxn != null) pkgP.addFxn("getSects", (Proto.Fxn)om.findStrict("xdc.IPackage$$getSects", "ti.catalog.arm.lm3init"), fxn);
        pkgP.bind("$capsule", cap);
        pkgV.init2(pkgP, "ti.catalog.arm.lm3init", Value.DEFAULT, false);
        pkgV.bind("$name", "ti.catalog.arm.lm3init");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "ti.catalog.arm.lm3init.");
        pkgV.bind("$vers", Global.newArray("1, 0, 0"));
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['ti.catalog.arm.lm3init'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
            sb.append("'lib/Boot.am3e',\n");
            sb.append("'lib/Boot.aem3',\n");
            sb.append("'lib/Boot.am3',\n");
            sb.append("'lib/Boot.aem3e',\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
            sb.append("['lib/Boot.am3e', {target: 'ti.targets.arm.M3_big_endian'}],\n");
            sb.append("['lib/Boot.aem3', {target: 'ti.targets.arm.elf.M3'}],\n");
            sb.append("['lib/Boot.am3', {target: 'ti.targets.arm.M3'}],\n");
            sb.append("['lib/Boot.aem3e', {target: 'ti.targets.arm.elf.M3_big_endian'}],\n");
        sb.append("];\n");
        sb.append("if('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {\n");
            sb.append("pkg.build.libDesc['lib/Boot.am3e'].suffix = 'm3e';\n");
            sb.append("pkg.build.libDesc['lib/Boot.aem3'].suffix = 'em3';\n");
            sb.append("pkg.build.libDesc['lib/Boot.am3'].suffix = 'm3';\n");
            sb.append("pkg.build.libDesc['lib/Boot.aem3e'].suffix = 'em3e';\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Boot$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("ti.catalog.arm.lm3init.Boot", "ti.catalog.arm.lm3init");
        po = (Proto.Obj)om.findStrict("ti.catalog.arm.lm3init.Boot.Module", "ti.catalog.arm.lm3init");
        vo.init2(po, "ti.catalog.arm.lm3init.Boot", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("ti.catalog.arm.lm3init.Boot$$capsule", "ti.catalog.arm.lm3init"));
        vo.bind("$package", om.findStrict("ti.catalog.arm.lm3init", "ti.catalog.arm.lm3init"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        vo.bind("ModuleView", om.findStrict("ti.catalog.arm.lm3init.Boot.ModuleView", "ti.catalog.arm.lm3init"));
        tdefs.add(om.findStrict("ti.catalog.arm.lm3init.Boot.ModuleView", "ti.catalog.arm.lm3init"));
        vo.bind("SysDiv", om.findStrict("ti.catalog.arm.lm3init.Boot.SysDiv", "ti.catalog.arm.lm3init"));
        vo.bind("PwmDiv", om.findStrict("ti.catalog.arm.lm3init.Boot.PwmDiv", "ti.catalog.arm.lm3init"));
        vo.bind("XtalFreq", om.findStrict("ti.catalog.arm.lm3init.Boot.XtalFreq", "ti.catalog.arm.lm3init"));
        vo.bind("OscSrc", om.findStrict("ti.catalog.arm.lm3init.Boot.OscSrc", "ti.catalog.arm.lm3init"));
        vo.bind("LdoOut", om.findStrict("ti.catalog.arm.lm3init.Boot.LdoOut", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_1", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_1", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_2", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_2", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_3", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_3", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_4", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_4", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_5", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_5", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_6", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_6", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_7", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_7", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_8", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_8", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_9", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_9", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_10", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_10", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_11", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_11", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_12", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_12", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_13", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_13", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_14", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_14", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_15", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_15", "ti.catalog.arm.lm3init"));
        vo.bind("SYSDIV_16", om.findStrict("ti.catalog.arm.lm3init.Boot.SYSDIV_16", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_2", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_2", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_4", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_4", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_8", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_8", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_16", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_16", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_32", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_32", "ti.catalog.arm.lm3init"));
        vo.bind("PWMDIV_64", om.findStrict("ti.catalog.arm.lm3init.Boot.PWMDIV_64", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_1MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_1MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_1_84MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_1_84MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_2MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_2MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_2_45MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_2_45MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_3_57MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_3_57MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_3_68MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_3_68MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_4MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_4MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_4_09MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_4_09MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_4_91MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_4_91MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_5MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_5MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_5_12MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_5_12MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_6MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_6MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_6_14MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_6_14MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_7_37MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_7_37MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_8MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_8MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_8_19MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_8_19MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_10MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_10MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_12MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_12MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_12_2MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_12_2MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_13_5MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_13_5MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_14_3MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_14_3MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_16MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_16MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("XTAL_16_3MHZ", om.findStrict("ti.catalog.arm.lm3init.Boot.XTAL_16_3MHZ", "ti.catalog.arm.lm3init"));
        vo.bind("OSCSRC_MAIN", om.findStrict("ti.catalog.arm.lm3init.Boot.OSCSRC_MAIN", "ti.catalog.arm.lm3init"));
        vo.bind("OSCSRC_INT", om.findStrict("ti.catalog.arm.lm3init.Boot.OSCSRC_INT", "ti.catalog.arm.lm3init"));
        vo.bind("OSCSRC_INT4", om.findStrict("ti.catalog.arm.lm3init.Boot.OSCSRC_INT4", "ti.catalog.arm.lm3init"));
        vo.bind("OSCSRC_30", om.findStrict("ti.catalog.arm.lm3init.Boot.OSCSRC_30", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_55V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_55V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_60V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_60V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_65V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_65V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_70V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_70V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_75V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_75V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_25V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_25V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_30V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_30V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_35V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_35V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_40V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_40V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_45V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_45V", "ti.catalog.arm.lm3init"));
        vo.bind("LDOPCTL_2_50V", om.findStrict("ti.catalog.arm.lm3init.Boot.LDOPCTL_2_50V", "ti.catalog.arm.lm3init"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "ti.catalog.arm.lm3init")).add(vo);
        vo.bind("$$instflag", 0);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 0);
        vo.bind("$$romcfgs", "|");
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("ti.catalog.arm.lm3init.Boot$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.setElem("", "./Boot.xdt");
        atmap.seal("length");
        vo.bind("TEMPLATE$", "./Boot.xdt");
        pkgV.bind("Boot", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Boot");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("ti.catalog.arm.lm3init.Boot", "ti.catalog.arm.lm3init"));
        vo = (Value.Obj)om.findStrict("ti.catalog.arm.lm3init.Boot", "ti.catalog.arm.lm3init");
        Global.put(vo, "rovViewInfo", Global.callFxn("create", (Scriptable)om.find("xdc.rov.ViewInfo"), Global.newObject("viewMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"Module", Global.newObject("type", om.find("xdc.rov.ViewInfo.MODULE"), "viewInitFxn", "viewInitModule", "structName", "ModuleView")})}))));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("ti.catalog.arm.lm3init.Boot")).bless();
        ((Value.Arr)om.findStrict("$packages", "ti.catalog.arm.lm3init")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Boot$$OBJECTS();
        Boot$$CONSTS();
        Boot$$CREATES();
        Boot$$FUNCTIONS();
        Boot$$SIZES();
        Boot$$TYPES();
        if (isROV) {
            Boot$$ROV();
        }//isROV
        $$SINGLETONS();
        Boot$$SINGLETONS();
        $$INITIALIZATION();
    }
}
