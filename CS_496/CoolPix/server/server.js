var port = 1337;
var express = require('./config/express');
var app = express();

app.listen(port);
module.exports = app;

console.log('CoolPix http://localhost:' + port);
