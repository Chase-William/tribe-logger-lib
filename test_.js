var wrapped = require('bindings')('addon');

var obj = wrapped.NewBitmapReturn(10);
console.log('Should be 10: ' + obj.GetValue());