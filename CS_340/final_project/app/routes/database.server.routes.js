module.exports = function(app) {
    var database = require('../controllers/database.server.controller');
    app.get('/getItems', database.getItems);
    app.get('/getLocations', database.getLocations);
    app.get('/getProduction', database.getProductions);
    app.get('/getTransit', database.getTransit);
    app.get('/getTransitItems', database.getTransitItems);
    app.get('/getItemsAtLocation', database.getItemsByLocation);
    app.get('/getLocationDestinations', database.getLocationDestinations);


    app.post('/createItem', database.createItem);
    app.post('/deleteItem', database.deleteItem);
    app.post('/createTransitItem', database.createTransitItem);
    app.post('/updateTransitItem', database.updateTransitItem);
    app.post('/deleteTransitItem', database.deleteTransitItem);
};