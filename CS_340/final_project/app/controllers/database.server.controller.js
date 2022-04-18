var mysqlDB = require('../components/db');
var dbPool = new mysqlDB();

exports.getItems = function (req, res) {
    dbPool.getItems(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getLocations = function (req, res) {
    dbPool.getLocations(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getProductions = function (req, res) {
    dbPool.getProductions(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getItemsByLocation = function (req, res) {
    dbPool.getItemsByLocation(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getLocationDestinations = function (req, res) {
    dbPool.getLocationDestinations(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getTransit = function (req, res) {
    dbPool.getTransit(req, res, function (payload) {
        res.json(payload);
    });
};

exports.getTransitItems = function (req, res) {
    dbPool.getTransitItems(req, res, function (payload) {
        res.json(payload);
    });
};

exports.createItem = function (req, res) {
    dbPool.createItem(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteItem = function (req, res) {
    dbPool.deleteItem(req, res, function (payload) {
        res.json(payload);
    });
};

exports.createTransitItem = function (req, res) {
    dbPool.createTransitItem(req, res, function (payload) {
        res.json(payload);
    });
};

exports.updateTransitItem = function (req, res) {
    dbPool.updateTransitItem(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteTransitItem = function (req, res) {
    dbPool.deleteTransitItem(req, res, function (payload) {
        res.json(payload);
    });
};