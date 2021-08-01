const result = require('./index');
const fs = require('fs');

console.log(result.calculateSync(9));
console.log(result.getMyNumber());
let buff = result.getWindowBitmap("ARK: Survival Evolved");
console.log("Buffer: ");
console.log(buff);

const view = new Uint8Array(buff);
console.log(view);

fs.writeFileSync('test.bmp', view, (err) => {
  if (err) return console.log(err);
  console.log("Saved");
});