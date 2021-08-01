const result = require('./index');
const fs = require('fs');

let buff = result.getWindowBitmap("ARK: Survival Evolved");
console.log("Buffer: ");
console.log(buff);

const view = new Uint8Array(buff);
console.log(view);

fs.writeFileSync('test.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});