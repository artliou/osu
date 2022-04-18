var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.content = function (req, res) {
    /////////////////////////////////////////
    //
    // Add new image to database
    //
    if (req.method === 'POST') {
        var newImage = dataStore.AddImage(req.body.email, req.body.imageData, req.body.title, req.body.body);
        if (newImage == undefined) {
            res.sendStatus(500);
        } else {
            console.log(`[HTTP] User Added content ${JSON.stringify(newImage)}`);
            res.send(newImage);
        }  
    }
    /*if ("user" in req.params) {
        var boat = dataStore.GetBoatInSlipByID(req.params.slipid);
        if (boat !== undefined) {
            res.send(boat);
        } else {
            res.sendStatus(404);
        }
    }*/
};