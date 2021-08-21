const getter = require('./dist/window-imagetter/index');

const test = getter.WindowImgetter.CreateNewBitmapReturn(10);
console.log("Value returned: " + test.GetValue());