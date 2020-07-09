/* 
 * Create recap.build.target
 *
 */   

/* Copy the 'build' object from C55 small model. */
this.build = xdc.loadCapsule('C55_large.rov.xs').build;

/* Update the size and align of the Ptr type. */
this.build.target['stdTypes']['t_Size'] =     { size: 2, align: 2 };
this.build.target['$name'] = unescape('ti.targets.C55_huge');
this.build.target['name'] = unescape('C55_huge');

/* Load the modules from a separate file */
var mods = xdc.loadCapsule('modules.rov.xs');
this.$modules = mods.$modules;
