xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.bios');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');
    xdc.loadPackage('xdc.bld');

/* ======== OBJECTS ======== */

// package ti.bios
    var pkg = $om.$$bind('ti.bios.Package', $$PObj());
    $om.$$bind('ti.bios', $$VObj('ti.bios', pkg));
// module Build
    var po = $om.$$bind('ti.bios.Build.Module', $$PObj());
    var vo = $om.$$bind('ti.bios.Build', $$VObj('ti.bios.Build', po));
    pkg.$$bind('Build', vo);

/* ======== CONSTS ======== */

// module Build

/* ======== CREATES ======== */

// module Build

/* ======== FUNCTIONS ======== */

// fxn Build.getIncludes
    var fxn = $om.$$bind('ti.bios.Build$$getIncludes', $$PFxn($om['ti.bios.Build.Module'], $$T_Str, 1, 1, false));
        fxn.$$arg(0, 'targetName', $$T_Str, undefined);
// fxn Build.getLibPath
    var fxn = $om.$$bind('ti.bios.Build$$getLibPath', $$PFxn($om['ti.bios.Build.Module'], $$T_Str, 1, 1, false));
        fxn.$$arg(0, 'targetName', $$T_Str, undefined);
// fxn Build.addExecutable
    var fxn = $om.$$bind('ti.bios.Build$$addExecutable', $$PFxn($om['ti.bios.Build.Module'], $om['xdc.bld.Executable.Instance'], 8, 8, false));
        fxn.$$arg(0, 'exeName', $$T_Str, undefined);
        fxn.$$arg(1, 'target', $om['xdc.bld.ITarget.Module'], undefined);
        fxn.$$arg(2, 'platformName', $$T_Str, undefined);
        fxn.$$arg(3, 'exeAttrs', $om['xdc.bld.Executable.Attrs'], $$DEFAULT);
        fxn.$$arg(4, 'tconfScript', $$T_Str, undefined);
        fxn.$$arg(5, 'genBaseName', $$T_Str, undefined);
        fxn.$$arg(6, 'tconfImportPath', $$T_Str, undefined);
        fxn.$$arg(7, 'tconfOptions', $$T_Str, undefined);
// fxn Build.expandLinkTemplate
    var fxn = $om.$$bind('ti.bios.Build$$expandLinkTemplate', $$PFxn($om['ti.bios.Build.Module'], null, 2, 2, false));
        fxn.$$arg(0, 'outStream', $$T_Obj, undefined);
        fxn.$$arg(1, 'args', $$T_Obj, undefined);

/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module Build
    var cap = $om.$$bind('ti.bios.Build$$capsule', xdc.loadCapsule('ti/bios/Build.xs'));
    var po = $om['ti.bios.Build.Module'].$$init('ti.bios.Build.Module', $$Module);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('ti.bios.Build$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        po.$$fxn('getIncludes', $om['ti.bios.Build$$getIncludes'], cap['getIncludes']);
        po.$$fxn('getLibPath', $om['ti.bios.Build$$getLibPath'], cap['getLibPath']);
        po.$$fxn('addExecutable', $om['ti.bios.Build$$addExecutable'], cap['addExecutable']);
        po.$$fxn('expandLinkTemplate', $om['ti.bios.Build$$expandLinkTemplate'], cap['expandLinkTemplate']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.bios
    var po = $om['ti.bios.Package'].$$init('ti.bios.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/bios/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.bios'].$$init(po, 'ti.bios', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.bios');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.bios.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [5, 2, 5, 44]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'lib/lnknone.a62e',
        'lib/lnknone.a28FP',
        'lib/bios.a55H',
        'lib/bios6747.a674',
        'lib/psclnull.a64P',
        'lib/bios.a55L',
        'lib/drivers.a64P',
        'lib/sioir.a674',
        'lib/bios_NONINST.a62e',
        'lib/biosDRA442.a64P',
        'lib/psclnull.a64e',
        'lib/bios2320.a55',
        'lib/bios5510.a55L',
        'lib/biosDM420IDMA0.a64P',
        'lib/bios6x1x.a62',
        'lib/bios6x1x.a67',
        'lib/drivers.a64e',
        'lib/lnkrtdx.a62e',
        'lib/biosDA700.a67P',
        'lib/lnkrtdx.a55',
        'lib/lnknone.a64P',
        'lib/sioir.a67P',
        'lib/log8.a55',
        'lib/bios2420.a55',
        'lib/sioir.a28L',
        'lib/bios_NONINST.a64P',
        'lib/pwrm.a55',
        'lib/sioboth.a55H',
        'lib/lnknone.a64e',
        'lib/sioboth.a55L',
        'lib/sioir.a67e',
        'lib/lnkrtdx.a62',
        'lib/psclnull.a674',
        'lib/lnkrtdx.a64',
        'lib/lnkrtdx.a67',
        'lib/log8.a62',
        'lib/biosTCI6488.a64P',
        'lib/bios5505.a55',
        'lib/log8.a64',
        'lib/drivers.a674',
        'lib/lnkrtdx.a64P',
        'lib/bios_NONINST.a64e',
        'lib/log8.a67',
        'lib/biosF761990.a64Pe',
        'lib/biosSK.a64Pe',
        'lib/biosTCI6482.a64Pe',
        'lib/biosC6000.a62',
        'lib/biosDM6467.a64Pe',
        'lib/biosC6000.a64',
        'lib/log8.a62e',
        'lib/lnkrtdx.a64e',
        'lib/biosC6000.a67',
        'lib/pslnull.a62e',
        'lib/bios5507.a55L',
        'lib/drivers.a67P',
        'lib/lnknone.a674',
        'lib/lnknone.a55',
        'lib/psclnull.a28L',
        'lib/bios.a64Pe',
        'lib/bios5503.a55L',
        'lib/psclnull.a67e',
        'lib/drivers.a28L',
        'lib/pwrm.a64P',
        'lib/bios_NONINST.a674',
        'lib/biosTCI6488.a64Pe',
        'lib/biosDM420IDMA0.a64Pe',
        'lib/bios5509.a55',
        'lib/drivers.a67e',
        'lib/bios6x0x.a62',
        'lib/biosDM420.a64Pe',
        'lib/biosDRA442.a64Pe',
        'lib/bios.a28FP',
        'lib/bios6x0x.a67',
        'lib/bios2420.a55H',
        'lib/bios.a62e',
        'lib/biosTCI6486.a64Pe',
        'lib/bios5502.a55',
        'lib/lnknone.a67P',
        'lib/lnknone.a62',
        'lib/bios2420.a55L',
        'lib/lnknone.a64',
        'lib/bios6x0x.a62e',
        'lib/lnkrtdx.a64Pe',
        'lib/log8.a64P',
        'lib/lnknone.a67',
        'lib/lnkrtdx.a674',
        'lib/pslnull.a64P',
        'lib/lnknone.a28L',
        'lib/bios_NONINST.a67P',
        'lib/lnkrtdx.a28FP',
        'lib/lnknone.a67e',
        'lib/log8.a64e',
        'lib/log8.a64Pe',
        'lib/sioir.a55H',
        'lib/bios1510.a55L',
        'lib/pslnull.a64e',
        'lib/sioir.a55L',
        'lib/bios6x1x.a62e',
        'lib/lnkrtdx.a67P',
        'lib/bios_NONINST.a67e',
        'lib/bios.a64P',
        'lib/log8.a28FP',
        'lib/pslnull.a64Pe',
        'lib/lnkrtdx.a28L',
        'lib/pwrm.a674',
        'lib/drivers.a55',
        'lib/bios6424.a64P',
        'lib/sioboth.a62e',
        'lib/lnkrtdx.a67e',
        'lib/bios.a64e',
        'lib/pslnull.a28FP',
        'lib/bios5561.a55',
        'lib/bios.a55',
        'lib/bios5510.a55',
        'lib/bios3430.a64P',
        'lib/log8.a674',
        'lib/bios_NONINST.a55',
        'lib/pslnull.a674',
        'lib/sioir.a64Pe',
        'lib/psclnull.a55H',
        'lib/drivers.a64Pe',
        'lib/biosC6000.a62e',
        'lib/drivers.a62',
        'lib/bios5502.a55L',
        'lib/drivers.a64',
        'lib/psclnull.a55L',
        'lib/sioir.a55',
        'lib/drivers.a67',
        'lib/biosDA300.a55',
        'lib/drivers.a55H',
        'lib/sioir.a28FP',
        'lib/drivers.a55L',
        'lib/drivers.a28FP',
        'lib/bios.a62',
        'lib/sioboth.a64P',
        'lib/log8.a67P',
        'lib/bios.a64',
        'lib/bios_NONINST.a62',
        'lib/bios6424.a64Pe',
        'lib/bios_NONINST.a64',
        'lib/bios.a67',
        'lib/bios_NONINST.a67',
        'lib/bios.a674',
        'lib/biosC6000.a64Pe',
        'lib/bios2320.a55H',
        'lib/bios5503.a55',
        'lib/biosDA300.a55L',
        'lib/log8.a28L',
        'lib/bios2320.a55L',
        'lib/sioir.a62',
        'lib/sioir.a64',
        'lib/pslnull.a28L',
        'lib/bios2430.a64Pe',
        'lib/sioir.a67',
        'lib/lnknone.a55H',
        'lib/sioboth.a64e',
        'lib/log8.a67e',
        'lib/bios1510.a55',
        'lib/biosC6000.a64P',
        'lib/lnknone.a55L',
        'lib/pslnull.a67e',
        'lib/bios_NONINST.a64Pe',
        'lib/bios.a67P',
        'lib/biosSK.a64P',
        'lib/bios_NONINST.a55H',
        'lib/psclnull.a55',
        'lib/bios_NONINST.a55L',
        'lib/biosTCI6486.a64P',
        'lib/biosC6000.a64e',
        'lib/bios1710.a55',
        'lib/bios.a28L',
        'lib/biosTCI6482.a64P',
        'lib/bios6748.a674',
        'lib/bios.a67e',
        'lib/lnkrtdx.a55H',
        'lib/bios5509.a55L',
        'lib/bios1710.a55H',
        'lib/bios5507.a55',
        'lib/sioir.a62e',
        'lib/lnkrtdx.a55L',
        'lib/bios6x0x.a67e',
        'lib/bios1710.a55L',
        'lib/sioboth.a674',
        'lib/bios5505.a55H',
        'lib/psclnull.a62',
        'lib/psclnull.a64',
        'lib/bios5505.a55L',
        'lib/pslnull.a55',
        'lib/psclnull.a67',
        'lib/biosF761990.a64P',
        'lib/bios6x1x.a67e',
        'lib/sioboth.a67P',
        'lib/pslnull.a62',
        'lib/pwrm.a55H',
        'lib/bios2430.a64P',
        'lib/pslnull.a64',
        'lib/sioir.a64P',
        'lib/biosSK.a674',
        'lib/pslnull.a67',
        'lib/pwrm.a55L',
        'lib/sioboth.a28L',
        'lib/sioboth.a55',
        'lib/psclnull.a62e',
        'lib/sioboth.a67e',
        'lib/sioboth.a64Pe',
        'lib/biosC6000.a67P',
        'lib/log8.a55H',
        'lib/bios5561.a55L',
        'lib/sioir.a64e',
        'lib/log8.a55L',
        'lib/pslnull.a55H',
        'lib/drivers.a62e',
        'lib/biosDM6467.a64P',
        'lib/pslnull.a55L',
        'lib/psclnull.a64Pe',
        'lib/sioboth.a28FP',
        'lib/biosDM420.a64P',
        'lib/sioboth.a62',
        'lib/sioboth.a64',
        'lib/lnknone.a64Pe',
        'lib/biosC6000.a67e',
        'lib/sioboth.a67',
        'lib/psclnull.a28FP',
    ];
    
    pkg.build.libDesc = [
        [
            'lib/lnknone.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnknone.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/bios.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios6747.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/psclnull.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/drivers.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/sioir.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/bios_NONINST.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/biosDRA442.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/psclnull.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/bios2320.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios5510.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/biosDM420IDMA0.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios6x1x.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/bios6x1x.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/drivers.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/biosDA700.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/lnkrtdx.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/lnknone.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/sioir.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/log8.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios2420.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/sioir.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/bios_NONINST.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/pwrm.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/sioboth.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/lnknone.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/sioboth.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioir.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/psclnull.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/lnkrtdx.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/lnkrtdx.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/log8.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/biosTCI6488.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios5505.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/log8.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/drivers.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/lnkrtdx.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios_NONINST.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/log8.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/biosF761990.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosSK.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosTCI6482.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosC6000.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/biosDM6467.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosC6000.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/log8.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/biosC6000.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/pslnull.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/bios5507.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/drivers.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/lnknone.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/lnknone.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/psclnull.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/bios.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios5503.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/psclnull.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/drivers.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/pwrm.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios_NONINST.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/biosTCI6488.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosDM420IDMA0.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios5509.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/drivers.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios6x0x.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/biosDM420.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosDRA442.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/bios6x0x.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/bios2420.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/biosTCI6486.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios5502.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/lnknone.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/lnknone.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/bios2420.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/lnknone.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/bios6x0x.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/log8.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/lnknone.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/lnkrtdx.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/pslnull.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/lnknone.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/bios_NONINST.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/lnkrtdx.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/lnknone.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/log8.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/log8.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/sioir.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios1510.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/pslnull.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/sioir.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/bios6x1x.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/bios_NONINST.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/log8.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/pslnull.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/pwrm.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/drivers.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios6424.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/sioboth.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/pslnull.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/bios5561.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios5510.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios3430.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/log8.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/bios_NONINST.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/pslnull.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/sioir.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/psclnull.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/drivers.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosC6000.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/drivers.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/bios5502.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/drivers.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/psclnull.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioir.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/drivers.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/biosDA300.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/drivers.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/sioir.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/drivers.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/drivers.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/bios.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/sioboth.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/log8.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/bios.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/bios_NONINST.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/bios6424.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios_NONINST.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/bios.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/bios_NONINST.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/bios.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/biosC6000.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios2320.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios5503.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/biosDA300.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/log8.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/bios2320.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioir.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/sioir.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/pslnull.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/bios2430.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/sioir.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/lnknone.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/sioboth.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/log8.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios1510.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/biosC6000.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/lnknone.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/pslnull.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios_NONINST.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/bios.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/biosSK.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios_NONINST.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/psclnull.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios_NONINST.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/biosTCI6486.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/biosC6000.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/bios1710.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/bios.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/biosTCI6482.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios6748.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/bios.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios5509.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/bios1710.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios5507.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/sioir.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/lnkrtdx.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/bios6x0x.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/bios1710.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioboth.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/bios5505.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/psclnull.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/psclnull.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/bios5505.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/pslnull.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/psclnull.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/biosF761990.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/bios6x1x.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/sioboth.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/pslnull.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/pwrm.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios2430.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/pslnull.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/sioir.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/biosSK.a674',
            {
                target: 'ti.targets.C674'
            }
        ],
        [
            'lib/pslnull.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/pwrm.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioboth.a28L',
            {
                target: 'ti.targets.C28_large'
            }
        ],
        [
            'lib/sioboth.a55',
            {
                target: 'ti.targets.C55'
            }
        ],
        [
            'lib/psclnull.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/sioboth.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/sioboth.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosC6000.a67P',
            {
                target: 'ti.targets.C67P'
            }
        ],
        [
            'lib/log8.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/bios5561.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/sioir.a64e',
            {
                target: 'ti.targets.C64_big_endian'
            }
        ],
        [
            'lib/log8.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/pslnull.a55H',
            {
                target: 'ti.targets.C55_huge'
            }
        ],
        [
            'lib/drivers.a62e',
            {
                target: 'ti.targets.C62_big_endian'
            }
        ],
        [
            'lib/biosDM6467.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/pslnull.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/psclnull.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/sioboth.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
        [
            'lib/biosDM420.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/sioboth.a62',
            {
                target: 'ti.targets.C62'
            }
        ],
        [
            'lib/sioboth.a64',
            {
                target: 'ti.targets.C64'
            }
        ],
        [
            'lib/lnknone.a64Pe',
            {
                target: 'ti.targets.C64P_big_endian'
            }
        ],
        [
            'lib/biosC6000.a67e',
            {
                target: 'ti.targets.C67_big_endian'
            }
        ],
        [
            'lib/sioboth.a67',
            {
                target: 'ti.targets.C67'
            }
        ],
        [
            'lib/psclnull.a28FP',
            {
                target: 'ti.targets.C28_float'
            }
        ],
    ];
    if ('suffix' in xdc.om['xdc.IPackage$$LibDesc']) {
        pkg.build.libDesc['lib/lnknone.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnknone.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/bios.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios6747.a674'].suffix = '674';
        pkg.build.libDesc['lib/psclnull.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/drivers.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/sioir.a674'].suffix = '674';
        pkg.build.libDesc['lib/bios_NONINST.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/biosDRA442.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/psclnull.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/bios2320.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios5510.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/biosDM420IDMA0.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios6x1x.a62'].suffix = '62';
        pkg.build.libDesc['lib/bios6x1x.a67'].suffix = '67';
        pkg.build.libDesc['lib/drivers.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/lnkrtdx.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/biosDA700.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/lnkrtdx.a55'].suffix = '55';
        pkg.build.libDesc['lib/lnknone.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/sioir.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/log8.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios2420.a55'].suffix = '55';
        pkg.build.libDesc['lib/sioir.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/bios_NONINST.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/pwrm.a55'].suffix = '55';
        pkg.build.libDesc['lib/sioboth.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/lnknone.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/sioboth.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioir.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/lnkrtdx.a62'].suffix = '62';
        pkg.build.libDesc['lib/psclnull.a674'].suffix = '674';
        pkg.build.libDesc['lib/lnkrtdx.a64'].suffix = '64';
        pkg.build.libDesc['lib/lnkrtdx.a67'].suffix = '67';
        pkg.build.libDesc['lib/log8.a62'].suffix = '62';
        pkg.build.libDesc['lib/biosTCI6488.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios5505.a55'].suffix = '55';
        pkg.build.libDesc['lib/log8.a64'].suffix = '64';
        pkg.build.libDesc['lib/drivers.a674'].suffix = '674';
        pkg.build.libDesc['lib/lnkrtdx.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios_NONINST.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/log8.a67'].suffix = '67';
        pkg.build.libDesc['lib/biosF761990.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosSK.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosTCI6482.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosC6000.a62'].suffix = '62';
        pkg.build.libDesc['lib/biosDM6467.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosC6000.a64'].suffix = '64';
        pkg.build.libDesc['lib/log8.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnkrtdx.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/biosC6000.a67'].suffix = '67';
        pkg.build.libDesc['lib/pslnull.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/bios5507.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/drivers.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/lnknone.a674'].suffix = '674';
        pkg.build.libDesc['lib/lnknone.a55'].suffix = '55';
        pkg.build.libDesc['lib/psclnull.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/bios.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios5503.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/psclnull.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/drivers.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/pwrm.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios_NONINST.a674'].suffix = '674';
        pkg.build.libDesc['lib/biosTCI6488.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosDM420IDMA0.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios5509.a55'].suffix = '55';
        pkg.build.libDesc['lib/drivers.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios6x0x.a62'].suffix = '62';
        pkg.build.libDesc['lib/biosDM420.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosDRA442.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/bios6x0x.a67'].suffix = '67';
        pkg.build.libDesc['lib/bios2420.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/biosTCI6486.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios5502.a55'].suffix = '55';
        pkg.build.libDesc['lib/lnknone.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/lnknone.a62'].suffix = '62';
        pkg.build.libDesc['lib/bios2420.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/lnknone.a64'].suffix = '64';
        pkg.build.libDesc['lib/bios6x0x.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnkrtdx.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/log8.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/lnknone.a67'].suffix = '67';
        pkg.build.libDesc['lib/lnkrtdx.a674'].suffix = '674';
        pkg.build.libDesc['lib/pslnull.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/lnknone.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/bios_NONINST.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/lnkrtdx.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/lnknone.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/log8.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/log8.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/sioir.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios1510.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/pslnull.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/sioir.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/bios6x1x.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnkrtdx.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/bios_NONINST.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/log8.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/pslnull.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/lnkrtdx.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/pwrm.a674'].suffix = '674';
        pkg.build.libDesc['lib/drivers.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios6424.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/sioboth.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnkrtdx.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/pslnull.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/bios5561.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios5510.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios3430.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/log8.a674'].suffix = '674';
        pkg.build.libDesc['lib/bios_NONINST.a55'].suffix = '55';
        pkg.build.libDesc['lib/pslnull.a674'].suffix = '674';
        pkg.build.libDesc['lib/sioir.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/psclnull.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/drivers.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosC6000.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/drivers.a62'].suffix = '62';
        pkg.build.libDesc['lib/bios5502.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/drivers.a64'].suffix = '64';
        pkg.build.libDesc['lib/psclnull.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioir.a55'].suffix = '55';
        pkg.build.libDesc['lib/drivers.a67'].suffix = '67';
        pkg.build.libDesc['lib/biosDA300.a55'].suffix = '55';
        pkg.build.libDesc['lib/drivers.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/sioir.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/drivers.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/drivers.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/bios.a62'].suffix = '62';
        pkg.build.libDesc['lib/sioboth.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/log8.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/bios.a64'].suffix = '64';
        pkg.build.libDesc['lib/bios_NONINST.a62'].suffix = '62';
        pkg.build.libDesc['lib/bios6424.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios_NONINST.a64'].suffix = '64';
        pkg.build.libDesc['lib/bios.a67'].suffix = '67';
        pkg.build.libDesc['lib/bios_NONINST.a67'].suffix = '67';
        pkg.build.libDesc['lib/bios.a674'].suffix = '674';
        pkg.build.libDesc['lib/biosC6000.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios2320.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios5503.a55'].suffix = '55';
        pkg.build.libDesc['lib/biosDA300.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/log8.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/bios2320.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioir.a62'].suffix = '62';
        pkg.build.libDesc['lib/sioir.a64'].suffix = '64';
        pkg.build.libDesc['lib/pslnull.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/bios2430.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/sioir.a67'].suffix = '67';
        pkg.build.libDesc['lib/lnknone.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/sioboth.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/log8.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios1510.a55'].suffix = '55';
        pkg.build.libDesc['lib/biosC6000.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/lnknone.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/pslnull.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios_NONINST.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/bios.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/biosSK.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios_NONINST.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/psclnull.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios_NONINST.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/biosTCI6486.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/biosC6000.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/bios1710.a55'].suffix = '55';
        pkg.build.libDesc['lib/bios.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/biosTCI6482.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios6748.a674'].suffix = '674';
        pkg.build.libDesc['lib/bios.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/lnkrtdx.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios5509.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/bios1710.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios5507.a55'].suffix = '55';
        pkg.build.libDesc['lib/sioir.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/lnkrtdx.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/bios6x0x.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/bios1710.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioboth.a674'].suffix = '674';
        pkg.build.libDesc['lib/bios5505.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/psclnull.a62'].suffix = '62';
        pkg.build.libDesc['lib/psclnull.a64'].suffix = '64';
        pkg.build.libDesc['lib/bios5505.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/pslnull.a55'].suffix = '55';
        pkg.build.libDesc['lib/psclnull.a67'].suffix = '67';
        pkg.build.libDesc['lib/biosF761990.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/bios6x1x.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/sioboth.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/pslnull.a62'].suffix = '62';
        pkg.build.libDesc['lib/pwrm.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios2430.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/pslnull.a64'].suffix = '64';
        pkg.build.libDesc['lib/sioir.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/biosSK.a674'].suffix = '674';
        pkg.build.libDesc['lib/pslnull.a67'].suffix = '67';
        pkg.build.libDesc['lib/pwrm.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioboth.a28L'].suffix = '28L';
        pkg.build.libDesc['lib/sioboth.a55'].suffix = '55';
        pkg.build.libDesc['lib/psclnull.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/sioboth.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/sioboth.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosC6000.a67P'].suffix = '67P';
        pkg.build.libDesc['lib/log8.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/bios5561.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/sioir.a64e'].suffix = '64e';
        pkg.build.libDesc['lib/log8.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/pslnull.a55H'].suffix = '55H';
        pkg.build.libDesc['lib/drivers.a62e'].suffix = '62e';
        pkg.build.libDesc['lib/biosDM6467.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/pslnull.a55L'].suffix = '55L';
        pkg.build.libDesc['lib/psclnull.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/sioboth.a28FP'].suffix = '28FP';
        pkg.build.libDesc['lib/biosDM420.a64P'].suffix = '64P';
        pkg.build.libDesc['lib/sioboth.a62'].suffix = '62';
        pkg.build.libDesc['lib/sioboth.a64'].suffix = '64';
        pkg.build.libDesc['lib/lnknone.a64Pe'].suffix = '64Pe';
        pkg.build.libDesc['lib/biosC6000.a67e'].suffix = '67e';
        pkg.build.libDesc['lib/sioboth.a67'].suffix = '67';
        pkg.build.libDesc['lib/psclnull.a28FP'].suffix = '28FP';
    }
    
// module Build
    var vo = $om['ti.bios.Build'];
    var po = $om['ti.bios.Build.Module'];
    vo.$$init(po, 'ti.bios.Build', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.bios.Build'));
    vo.$$bind('$capsule', $om['ti.bios.Build$$capsule']);
    vo.$$bind('$package', $om['ti.bios']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 0);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 0);
    vo.$$bind('$$romcfgs', '|');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('ti.bios.Build$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    pkg.$$bind('Build', vo);
    pkg.$unitNames.$add('Build');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['ti.bios.Build'].module$meta$init();
    pkg.init();
    $om['ti.bios.Build'].$$bless();
