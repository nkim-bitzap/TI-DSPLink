/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
requires xdc.bld [1,0,1];

/*!
 *  ======== gnu.targets ========
 *  Package of targets that wrap GNU gcc code generation tools.
 */
package gnu.targets [1,0,1] {
    module Sparc, Linux86, Mingw;
    module MVArm9, UCArm9;
    interface ITarget;
}
/*
 *  @(#) gnu.targets; 1, 0, 1,374; 12-18-2009 11:42:01; /db/ztree/library/trees/xdctargets/xdctargets-b30x/src/
 */

