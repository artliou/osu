const pug = require('pug');

exports.render = function(req, res) {

    this.stuff = [];

    var items = Object.keys(req.headers);
    console.log('Headers: ' + JSON.stringify(req.headers));
    for (var itemIndex=0; itemIndex < items.length; itemIndex++) {
        var currentItem = req.headers[items[itemIndex]];
        this.stuff.push({
            name: items[itemIndex],
            value: currentItem
        });
    }

    if (req.method === 'GET')
    {
        this.httpMethod = "GET Request Received";
    }
    else if (req.method === 'POST')
    {
        this.httpMethod = "POST Request Received";

        // Extract POST data
        var items = Object.keys(req.body);
        console.log('Post Data: ' + JSON.stringify(req.body));
        for (var itemIndex=0; itemIndex < items.length; itemIndex++) {
            var currentItem = req.body[items[itemIndex]];
            this.stuff.push({
                name: items[itemIndex],
                value: currentItem
            });
        }

    }

    res.render('index', {
        title: 'CS_290: Assignment - HTTP GET/POST checker',
        httpMethod: this.httpMethod,
        stuff: this.stuff
    })
};
