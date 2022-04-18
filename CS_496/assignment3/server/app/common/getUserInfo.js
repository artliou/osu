var https = require("https");


module.exports = function () {
    this.userInfoURL = "www.googleapis.com";
    this.userInfoPath = "/plus/v1/people/me";

    this.userData = {};

    this.Connect = function(tokenObject, callback) {
        console.log("Checkpoint 1");
        var request = https.request({
            host: this.userInfoURL,
            method: 'GET',
            headers: {
                "Authorization": `${tokenObject.token_type} ${tokenObject.access_token}`
            },
            path: this.userInfoPath
        }, function (response) {
            console.log(`STATUS: ${response.statusCode}`);
            console.log(`HEADERS: ${JSON.stringify(response.headers)}`);
            response.setEncoding('utf8');
            var data = "";
            response.on('data', (chunk) => {
                console.log (`Adding chunk [${chunk}]`);
                data += chunk;
                console.log (`Data [${data}]`);
            });
            response.on('end', () => {
                console.log (`Data [${data}]`);
                this.userData = JSON.parse(data);
                callback(this.userData);
            });
        });
          
        request.on('error', (e) => {
            console.error(`problem with request: ${e.message}`);
        });
        request.end();
    }

    this.GetUserData = function() {
        console.log(this.userData);
        return this.userData;
    }

    return this;
};
