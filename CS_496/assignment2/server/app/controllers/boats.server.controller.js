var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.boat = function(req, res) {
    if (req.method === 'GET')
    {
        if ("boatid" in req.params) {
            var boat = dataStore.GetBoatByID(req.params.boatid);
            if (boat !== undefined) {
                res.send(boat);
            } else {
                res.sendStatus(404);
            }
        } else {
            res.send(dataStore.GetAllBoats());
        }
    }
    else if (req.method === 'POST')
    {
        var newBoat = dataStore.CreateBoat(req.body);
        if (newBoat == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Boat ${JSON.stringify(newBoat)}`);
            res.send(newBoat);
        }
    }
    else if (req.method === 'PATCH')
    {
        if ("boatid" in req.params) {
            if (dataStore.UpdateBoatByID(req.params.boatid, req.body))
            {
                var update = dataStore.GetBoatByID(req.params.boatid);
                res.send(update);
                console.log(`Updated Boat ${JSON.stringify(update)}`);
            }
        }
        else
        {
            res.sendStatus(404);
        }
    }
    else if (req.method === 'DELETE')
    {
        if ("boatid" in req.params) {
            if (dataStore.DeleteBoatByID(req.params.boatid))
            {
                console.log(`Deleted Boat ${req.params.boatid}`);
                res.sendStatus(204);
            }
        }
        else
        {
            res.sendStatus(404);
        }
    }
};

exports.boatdock = function(req, res) {
    if (req.method === 'PUT')
    {
        if (("boatid" in req.params) && ("slipid" in req.params)) {
            var boatid = req.params.boatid;
            var slipid = req.params.slipid;

            // Is the slip empty?
            if (dataStore.DockBoat(boatid, slipid)) {
                res.sendStatus(204);
            } else {
                res.sendStatus(403);
            }
        } else {
            res.sendStatus(404);
        }
    }
    else if (req.method === 'DELETE')
    {
        if (("boatid" in req.params) && ("slipid" in req.params)) {
            var boatid = req.params.boatid;
            var slipid = req.params.slipid;

            // Is the slip empty?
            if (dataStore.UndockBoat(boatid, slipid)) {
                res.sendStatus(204);
            } else {
                res.sendStatus(403);
            }
        } else {
            res.sendStatus(404);
        }
    }
}