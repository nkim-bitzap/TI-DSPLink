print("start of examples.xs file building");
var filterC28x = [
    {deviceFamily:"C2000", toolChain:"TI"},
];

var filterC55x = [
    {deviceFamily:"C5500", toolChain:"TI"},
];

var filterC6x = [
    {deviceFamily:"C6000", toolChain:"TI"},
];

var boards = [
    {
    name: "ezdsp2812",
    filter: filterC28x,
    id: "ti.bios.examples.root.ezdsp2812",
    },
    {
    name: "ezdsp28335",
    filter: filterC28x,
    id: "ti.bios.examples.root.ezdsp28335",
    },
    {
    name: "control28055",
    filter: filterC28x,
    id: "ti.bios.examples.root.control28055",
    },
    {
    name: "control28069",
    filter: filterC28x,
    id: "ti.bios.examples.root.control28069",
    },
    {
    name: "ezdsp5502",
    filter: filterC55x,
    id: "ti.bios.examples.root.ezdsp5502",
    },
    {
    name: "evm5505",
    filter: filterC55x,
    id: "ti.bios.examples.root.evm5505",
    },
    {
    name: "ezdsp5535",
    filter: filterC55x,
    id: "ti.bios.examples.root.ezdsp5535",
    },
    {
    name: "evm5515",
    filter: filterC55x,
    id: "ti.bios.examples.root.evm5515",
    },
    {
    name: "evm5517",
    filter: filterC55x,
    id: "ti.bios.examples.root.evm5517",
    },
    {
    name: "dsk5510",
    filter: filterC55x,
    id: "ti.bios.examples.root.dsk5510",
    },
    {
    name: "ezdsp5505",
    filter: filterC55x,
    id: "ti.bios.examples.root.ezdsp5505",
    },
    {
    name: "dsk6416",
    filter: filterC6x,
    id: "ti.bios.examples.root.dsk6416",
    },
    {
    name: "dsk6455",
    filter: filterC6x,
    id: "ti.bios.examples.root.dsk6455",
    },
    {
    name: "evm6424",
    filter: filterC6x,
    id: "ti.bios.examples.root.evm6424",
    },
    {
    name: "evm6474",
    filter: filterC6x,
    id: "ti.bios.examples.root.evm6474",
    },
    {
    name: "evm6747",
    filter: filterC6x,
    id: "ti.bios.examples.root.evm6747",
    },
    {
    name: "evm6748",
    filter: filterC6x,
    id: "ti.bios.examples.root.evm6748",
    },
    {
    name: "evmDM6437",
    filter: filterC6x,
    id: "ti.bios.examples.root.evmDM6437",
    },
    {
    name: "evmDM6446",
    filter: filterC6x,
    id: "ti.bios.examples.root.evmDM6446",
    },
    {
    name: "evmDM6467",
    filter: filterC6x,
    id: "ti.bios.examples.root.evmDM6467",
    },
    {
    name: "evmOMAPL137",
    filter: filterC6x,
    id: "ti.bios.examples.root.evmOMAPL137",
    },
    {
    name: "evmOMAPL138",
    filter: filterC6x,
    id: "ti.bios.examples.root.evmOMAPL138",
    },
    {
    name: "padk6727",
    filter: filterC6x,
    id: "ti.bios.examples.root.padk6727",
    },
    {
    name: "sim6416",
    filter: filterC6x,
    id: "ti.bios.examples.root.sim6416",
    },
]

var genericExamples = [
    {
        title: "bigtime example",
        description: "This is an example of using statically created DSP/BIOS objects, idle (IDL), period (PRD), and task (TSK), along with some C++ objects.  In this program, C++ is used to create a real-time clock/calendar.  The C++ class object, Clock, is driven by a variety of DSP/BIOS objects: two PRD objects, two TSK objects, and an IDL object, which are created through the DSP/BIOS Textual Configuration (TConf) Tools.",
        cFile: "bigtime.cpp",
        tcfFile: "bigtime.tcf",
    },
    {
        title: "clk example",
        description: "This example simply shows a statically recreated DSP/BIOS TSK object, task, using LOG_printf to print clock ticks. In this example, a task goes to sleep some number of ticks and prints the time after it wakes up.",
        cFile: "clk.c",
        tcfFile: "clk.tcf",
    },
    {
        title: "hello example",
        description: "This example serves as a basic sanity check program for DSP/BIOS. It demonstrates how to print the string 'hello world!' to the DSP/BIOS message log. This example also introduces new users to DSP/BIOS by performing basic string output using a LOG object.",
        cFile: "hello.c",
        tcfFile: "hello.tcf",
    },
    {
        title: "mailbox example",
        description: "This example uses a mailbox (from the MBX module of DSP/BIOS)to send messages from multiple writer tasks to a single reader task.  In this example, the mailbox, the reader task, and three writer tasks are created by the Configuration Tool.",
        cFile: "mailbox.c",
        tcfFile: "mailbox.tcf",
    },
    {
        title: "semaphore example",
        description: "This is an example of using statically created DSP/BIOS objects, semaphore (SEM) and task (TSK) and dynamically created queue (QUE) objects. This example will show you how to use DSP/BIOS's QUE and SEM APIs to synchronize message sending among tasks.",
        cFile: "semaphore.c",
        tcfFile: "semaphore.tcf",
    },
    {
        title: "stairstep example",
        description: "The purpose of this example is to illustrate the cpuload graph.  In cpuloadInit it gets the CPU frequency using an API and fills the loadValue array with load values corresponding to 25, 50, 75 and 98 percent cpuload. The loadPrd which has a small period calls AUDIO_load function with loadValue. The stepPrd which has a very long period changes the loadValue in a circular fashion.",
        cFile: "stairstep.c",
        tcfFile: "stairstep.tcf",
    },
    {
        title: "swi example",
        description: "This example shows how a lower priority software interrupt (SWI) can interrupt itself by posting a higher priority software interrupt.",
        cFile: "swi.c",
        tcfFile: "swi.tcf",
    },
    {
        title: "tsk example",
        description: "This example shows the round robin scheduling scheme for tasks of equal priority.",
        cFile: "tsk.c",
        tcfFile: "tsk.tcf",
    },
]



/*
 *  ======== module$meta$init ========
 */

function module$meta$init()
{
    Examples = this;

    Examples.templateGroupArr.$add({
        id          : "ti.bios.examples.root",
        name        : "DSP/BIOS v5.xx Examples",
        description : "DSP/BIOS v5.xx Examples",
    });
    
    for (i = 0; i < boards.length; i++) {
        // print("name = " + boards[i].name);
        // print("id = " + boards[i].id);
        Examples.templateGroupArr.$add({
            id          : boards[i].id,
            name        : boards[i].name + " Examples",
            description : boards[i].name + " specific DSP/BIOS Examples.",
            groups      : ["ti.bios.examples.root"],
        });
    }

    for (i = 0; i < boards.length; i++) {
        for (j = 0; j < genericExamples.length; j++) {

            Examples.templateArr.$add({

                filterArr: boards[i].filter,

                title: genericExamples[j].title,
                description: genericExamples[j].description,
                fileList: [
		    {path: genericExamples[j].cFile},
		    {path: boards[i].name + "/" + genericExamples[j].tcfFile}
                ],
                groups: [ boards[i].id ],
                linkerCommandFile: "",
                legacyTcf: true,
            });
        // print("groups = " + boards[i].id);
        }
    }
}

