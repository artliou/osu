var mysqlDB = require('../components/db');
var dbPool = new mysqlDB();

exports.getWorkouts = function (req, res) {
    dbPool.getWorkouts(req, res, function (payload) {
        res.json(payload);
    });
};

exports.insertWorkout = function (req, res) {
    dbPool.insertWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.updateWorkout = function (req, res) {
    dbPool.updateWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteWorkout = function (req, res) {
    dbPool.deleteWorkout(req, res, function (payload) {
        res.json(payload);
    });
};

exports.deleteAllWorkouts = function (req, res) {
    dbPool.deleteAllWorkouts(req, res, function (payload) {
        res.json(payload);
    });
};