module.exports = function(app) {
    var index = require('../controllers/slips.server.controller');

    // Get all slips
    app.get('/slips', index.slips);

    // Get a specific slip
    app.get('/slips/:slipid', index.slips);

    // Get a specific slip
    app.get('/slips/:slipid/current_boat', index.boatinslip);

    // Create a new slip
    app.post('/slips', index.slips);

    // Update a slip's metadata
    app.patch('/slips/:slipid', index.slips);

    // Destroy a slip
    app.delete('/slips/:slipid', index.slips);
};