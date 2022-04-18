var DataStore = require('../datastore/datastore');

var dataStore = new DataStore();

exports.boatinslip = function (req, res) {
    if (req.method === 'GET') {
        if ("slipid" in req.params) {
            var boat = dataStore.GetBoatInSlipByID(req.params.slipid);
            if (boat !== undefined) {
                res.send(boat);
            } else {
                res.sendStatus(404);
            }
        }
    }
}

exports.slips = function (req, res) {
    if (req.method === 'GET') {
        if ("slipid" in req.params) {
            var slip = dataStore.GetSlipByID(req.params.slipid);
            if (slip !== undefined) {
                res.send(slip);
            } else {
                res.sendStatus(404);
            }
        } else {
            res.send(dataStore.GetAllSlips());
        }
    } else if (req.method === 'POST') {
        var newSlip = dataStore.CreateSlip(req.body);
        if (newSlip == undefined) {
            res.sendStatus(409);
        } else {
            console.log(`Created Slip ${JSON.stringify(newSlip)}`);
            res.send(newSlip);
        }
    }
    else if (req.method === 'PATCH')
    {
        if ("slipid" in req.params) {
            if (dataStore.UpdateSlipByID(req.params.slipid, req.body))
            {
                var update = dataStore.GetSlipByID(req.params.slipid);
                res.send(update);
                console.log(`Updated Slip ${JSON.stringify(update)}`);
            }
        }
        else
        {
            res.sendStatus(404);
        }
    }

    else if (req.method === 'DELETE')
    {
        if ("slipid" in req.params) {
            if (dataStore.DeleteSlipByID(req.params.slipid))
            {
                console.log(`Deleted Slip ${req.params.slipid}`);
                res.sendStatus(204);
            }
        }
        else
        {
            res.sendStatus(404);
        }
    }

};