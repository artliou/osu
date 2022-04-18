module.exports = function(app) {
    var index = require('../controllers/boats.server.controller');
    
    // Get all boats
    app.get('/boats', index.boat);
    
    // Get a single boat
    app.get('/boats/:boatid', index.boat);
    
    // Create a boat
    app.post('/boats', index.boat);
    
    // Update a boat's metadata
    app.patch('/boats/:boatid', index.boat);
    
    // Destroy a boat
    app.delete('/boats/:boatid', index.boat);
    
    // Dock a boat at a slip
    app.put('/boats/:boatid/:slipid', index.boatdock);
    
    // Undock a boat from a slip
    app.delete('/boats/:boatid/:slipid', index.boatdock);
};