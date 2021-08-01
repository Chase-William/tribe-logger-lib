const result = require('./dist/index');
const fs = require('fs');

let buff = result.GetWindowBitmap("ARK: Survival Evolved");
console.log("Js-Buffer: ");
console.log(buff);

const view = new Uint8Array(buff);
console.log(view);

fs.writeFileSync('test.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});