function loadSetting(index) {
    let value;

    Object.entries(Module['settings']).forEach(([, sValue], sIndex) => {
        if (sIndex == index) {
            return value = sValue;
        }
    });

    return value;
};

// Module['preRun'] = [];
// Module['preRun'].push(function () {
//     console.log(Module['settings']);
// });

Module['print'] = function (text) {
    if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
    console.info("avPluginProjectM => " + text);
};

Module['printErr'] = function (text) {
    if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
    console.error("avPluginProjectM => " + text);
};

