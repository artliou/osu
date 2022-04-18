var port = 8080;
var hostname = 'localhost';
var express = require('./config/express');
var app = express();

app.listen(port);
module.exports = app;

console.log(`OAuth 2.0 Demo running at http://${hostname}:${port}`);
