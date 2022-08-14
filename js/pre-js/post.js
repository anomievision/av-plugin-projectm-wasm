
async function presetPack() {
    if (Module['presetPack']) {
        console.log("Found presets module");

        for (let i = 0; i < Module['presetPack'].length; i++) {
            switch (Module['presetPack'][i]) {
                case 'bltc201':
                    await Module['bltc201']();
                    break;
                case 'yin':
                    await Module['yin']();
                    break;
                case 'stock':
                    await Module['stock']();
                    break;
                case 'milkdrop-original':
                    await Module['milkdrop-original']();
                    break;
                case 'eyetune':
                    await Module['eyetune']();
                    break;
                case 'milkdrop':
                    await Module['milkdrop']();
                    break;
                case 'milkdrop-104':
                    await Module['milkdrop-104']();
                    break;
                case 'milkdrop-200':
                    await Module['milkdrop-200']();
                    break;
                case 'mischa':
                    await Module['mischa']();
                    break;
                case 'tryptonaut':
                    await Module['tryptonaut']();
                    break;
                case 'projectm':
                    await Module['projectm']();
                    break;
                default:
                    console.log("No preset pack was selected!");
            }

            console.log("PresetPack: " + Module['presetPack'][i] + " was activated!")
        }
    }
}

presetPack();
