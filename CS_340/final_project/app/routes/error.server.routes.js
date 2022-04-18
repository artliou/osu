module.exports = function(app) {
    var error = require('../controllers/error.server.controller');
    app.get('*', error.render);
    app.post('*', error.render);
};