const mysql = require('mysql');

module.exports = function () {
    var context = this;


    this.pool = mysql.createPool({
        host: 'mysql.cs.orst.edu',
        user: 'cs340_praterj',
        password: '7221',
        database: 'cs340_praterj'
    });
    console.log('[MYSQL] Created Database object.');

    this.insertData = function (table, names, data, callback) {
        var itemData =
            "INSERT INTO " + table + " (" + names + ") VALUES (" + data + ");"
        context.pool.query(itemData, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                console.log('[MYSQL] Query: ' + itemData);
            } else {
                if (callback) {
                    callback();
                }
            }
        });
    };

    this.insertCodex = function (codexType) {
        switch (codexType) {
            case 'items':
                {
                    console.log("[MYSQL] Adding items...");
                    // Raw materials
                    // Semiconductor stuff
                    this.insertData('space_items', 'itemID, name', '1, "Silicon"');
                    this.insertData('space_items', 'itemID, name', '2, "Germanium"');
                    this.insertData('space_items', 'itemID, name', '3, "Gold"');

                    // Structural stuff
                    this.insertData('space_items', 'itemID, name', '4, "Aluminum"');
                    this.insertData('space_items', 'itemID, name', '5, "Titanium"');
                    this.insertData('space_items', 'itemID, name', '6, "Iron"');

                    // Manufactured stuff
                    this.insertData('space_items', 'itemID, name', '10, "Semiconductor components"');
                    this.insertData('space_items', 'itemID, name', '11, "Computer equipment"');
                    this.insertData('space_items', 'itemID, name', '12, "Experimental components"');

                    this.insertData('space_items', 'itemID, name', '20, "External structure components"');
                    this.insertData('space_items', 'itemID, name', '21, "Internal structure components"');
                    this.insertData('space_items', 'itemID, name', '22, "Solar panel components"');

                    this.insertData('space_items', 'itemID, name', '30, "Oxygen canister"');
                    this.insertData('space_items', 'itemID, name', '31, "Hydrogen fuel"');
                    this.insertData('space_items', 'itemID, name', '32, "Ammonia coolant"');
                }
                break;
            case 'locations':
                {
                    console.log("[MYSQL] Adding locations...");
                    // Locations

                    // Quarries for getting metals
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '1, "Kappa Quarry",       0.1, 0.7, 1');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '2, "Fisher Quarry",      0.05, 0.6, 1');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '3, "Cedar Creek Quarry", 0.03, 0.2, 1');

                    // Factories for making stuff
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '4, "Lundt Gas works",   0.3, 0.37, 2');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '5, "SemiFab",           0.22, 0.22, 2');
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '6, "Boing",             0.14, 0.8, 2');

                    // Launch site
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '7, "Space taXi",        0.4, 0.5, 3');

                    // ISS
                    this.insertData('space_locations', 'locationID, name, xLocation, yLocation, locationStyle', '8, "ISS",               0.9, 0.4, 4');
                }
                break;
            case 'production':
                {
                    console.log("[MYSQL] Adding production...");

                    // Quarries that produce material
                    // Kappa Quarry produces Silicon, Aluminum, and Titanium
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '1, 1, 1, 0.2, 0.6');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '2, 1, 4, 0.3, 0.7');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '3, 1, 5, 0.0, 0.3');

                    // Fisher Quarry produces Iron
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '4, 2, 6, 0.5, 0.8');

                    // Cedar Creek Quarry produces Germanium and Gold
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '5, 3, 2, 0.5, 0.8');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '6, 3, 3, 0.5, 0.8');

                    // Lundt Gas works makes O2, H2, and Ammonia
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '7, 4, 30, 0.4, 0.4');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '8, 4, 31, 0.3, 0.7');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '9, 4, 32, 0.2, 0.4');

                    // SemiFab makes Semiconductor stuff
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '10, 5, 10, 0.4, 0.4');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '11, 5, 11, 0.3, 0.7');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '12, 5, 12, 0.2, 0.4');

                    // Boing makes mechanical stuff
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '13, 6, 20, 0.4, 0.4');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '14, 6, 21, 0.3, 0.7');
                    this.insertData('space_locationProduction', 'productionID, f_locationID, f_itemID, min, max', '15, 6, 22, 0.2, 0.4');
                }
                break;
            case 'transit':
                {
                    console.log("[MYSQL] Adding transit...");

                    // Allowable destinations
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '1, 1, 4, 10');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '2, 1, 5, 6');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '3, 1, 6, 8');


                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '4, 2, 4, 10');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '5, 2, 5, 6');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '6, 2, 6, 8');

                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '7, 3, 4, 10');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '8, 3, 5, 6');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '9, 3, 6, 8');

                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '10, 4, 7, 15');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '11, 5, 7, 12');
                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '12, 6, 7, 10');

                    this.insertData('space_locationTransit', 'locationTransitID, f_startLocation, f_endLocation, totalTime', '13, 7, 8, 13');
                }
                break;
        }
    }

    this.getItems = function (req, res, callback) {
        var sqlString = 'SELECT itemID, name FROM space_items;';
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getLocations = function (req, res, callback) {
        var sqlString = 'SELECT locationID, name, xLocation, yLocation, locationStyle FROM space_locations;';
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getProductions = function (req, res, callback) {
        var sqlString = 'SELECT productionID, f_locationID, f_itemID, min, max FROM space_locationProduction;';
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getItemsByLocation = function (req, res, callback) {
        var sqlString =
            'SELECT itemLocationID, space_items.name AS itemName, space_locations.name as locationName, qty FROM space_itemLocations ' +
            'INNER JOIN space_items ON space_items.itemID=space_itemLocations.f_itemID ' +
            'INNER JOIN space_locations ON space_locations.locationID=space_itemLocations.f_locationID ' +
            'WHERE space_itemLocations.f_locationID=' + req.query.locationID + ';'
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getLocationDestinations = function (req, res, callback) {
        console.log ("[MYSQL] /database.getLocationDestinations : " + req.query.locationID);
        var sqlString =
            'SELECT space_locations.name as locationName, f_endLocation FROM space_locationTransit ' +
            'INNER JOIN space_locations ON space_locations.locationID=space_locationTransit.f_endlocation ' +
            'WHERE space_locationTransit.f_startLocation=' + req.query.locationID + ';'
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getTransit = function (req, res, callback) {
        console.log ("[MYSQL] /database.getTransit");
        var sqlString =
            'SELECT f_startLocation, f_endLocation, totalTime FROM space_locationTransit;';
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.getTransitItems = function (req, res, callback) {
        console.log ("[MYSQL] /database.getTransitItems");
        var sqlString =
            'SELECT transitID, f_itemID, f_startLocation, f_endLocation, qty, currentTime, totalTime FROM space_itemTransit;';
        context.pool.query(sqlString, function (err, rows, fields) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
                callback({
                    "error": err
                });
                return;
            } else {
                callback(rows);
            }
        });
    };

    this.createItem = function (req, res, callback) {
        console.log('[MYSQL] /database.createItem');
        var payload = {};
        var dataSet = [
            req.body.itemID,
            req.body.locationID,
            req.body.qty
        ];
        context.pool.query("INSERT INTO space_itemLocations (f_itemID, f_locationID, qty) VALUES (?, ?, ?)", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.createTransitItem = function (req, res, callback) {
        console.log('[MYSQL] /database.createTransitItem');
        var payload = {};
        var dataSet = [
            req.body.itemID,
            req.body.startLocation,
            req.body.endLocation,
            req.body.qty,
            0,
            req.body.totalTime
        ];
        context.pool.query("INSERT INTO space_itemTransit (f_itemID, f_startLocation, f_endLocation, qty, currentTime, totalTime) VALUES (?, ?, ?, ?, ?, ?)", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.updateTransitItem = function (req, res, callback) {
        console.log('[MYSQL] /database.createTransitItem');
        var payload = {};
        var dataSet = [
            req.body.currentTime,
            req.body.transitID
        ];
        context.pool.query("UPDATE space_itemTransit SET currentTime=? WHERE transitID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "updated": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "updated": true,
                    };
                    callback(payload);
                }
            });
    };

    this.deleteTransitItem = function (req, res, callback) {
        console.log('[MYSQL] /database.createTransitItem');
        var payload = {};
        var dataSet = [
            req.body.transitID
        ];
        context.pool.query("DELETE FROM space_itemTransit WHERE transitID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.deleteItem = function (req, res, callback) {
        console.log('[MYSQL] /database.deleteItem');
        var payload = {};
        var dataSet = [
            req.body.locationItemID
        ];
        context.pool.query("DELETE FROM space_itemLocations WHERE itemLocationID=?", dataSet,
            function (err, result) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                    payload = {
                        "created": false,
                        "error": err
                    };
                    callback(payload);
                } else {
                    payload = {
                        "created": true,
                        "createdID": result.insertId
                    };
                    callback(payload);
                }
            });
    };

    this.createTables = function () {
        console.log('[MYSQL] Create Table');
        var createString =
            "CREATE TABLE space_items (" +
            "itemID int," +
            "name VARCHAR(255) NOT NULL," +
            "required0_itemID int," +
            "required0_qty int," +
            "required1_itemID int," +
            "required1_qty int," +
            "required2_itemID int," +
            "required2_qty int," +
            "PRIMARY KEY (itemID)," +
            "FOREIGN KEY (required0_itemID) REFERENCES space_items(itemID)," +
            "FOREIGN KEY (required1_itemID) REFERENCES space_items(itemID)," +
            "FOREIGN KEY (required2_itemID) REFERENCES space_items(itemID)" +
            ") ENGINE=InnoDB;";
        context.pool.query(createString, function (err) {
            if (err) {
                console.log('[MSQL] Error: ' + err);
            } else {
                context.insertCodex('items');
            }
            createString =
                "CREATE TABLE space_locations (" +
                "locationID int," +
                "name VARCHAR(255) NOT NULL," +
                "xLocation double NOT NULL," +
                "yLocation double NOT NULL," +
                "locationStyle int NOT NULL," +
                "PRIMARY KEY(locationID)" +
                ") ENGINE=InnoDB;";
            context.pool.query(createString, function (err) {
                if (err) {
                    console.log('[MSQL] Error: ' + err);
                } else {
                    context.insertCodex('locations');
                }
                createString =
                    "CREATE TABLE space_locationProduction (" +
                    "productionID int," +
                    "f_locationID int," +
                    "f_itemID int," +
                    "min double NOT NULL," +
                    "max double NOT NULL," +
                    "PRIMARY KEY(productionID)," +
                    "FOREIGN KEY (f_locationID) REFERENCES space_locations(locationID)," +
                    "FOREIGN KEY (f_itemID) REFERENCES space_items(itemID)" +
                    ") ENGINE=InnoDB;";
                context.pool.query(createString, function (err) {
                    if (err) {
                        console.log('[MSQL] Error: ' + err);
                    } else {
                        context.insertCodex('production');
                    }
                    createString =
                        "CREATE TABLE space_itemLocations (" +
                        "itemLocationID int AUTO_INCREMENT," +
                        "f_locationID int," +
                        "f_itemID int," +
                        "qty double NOT NULL," +
                        "PRIMARY KEY(itemLocationID)," +
                        "FOREIGN KEY (f_locationID) REFERENCES space_locations(locationID)," +
                        "FOREIGN KEY (f_itemID) REFERENCES space_items(itemID)" +
                        ") ENGINE=InnoDB;";
                    context.pool.query(createString, function (err) {
                        if (err) {
                            console.log('[MSQL] Error: ' + err);
                        } else {}
                        createString =
                            "CREATE TABLE space_itemRequest (" +
                            "requestID int AUTO_INCREMENT," +
                            "f_locationID int," +
                            "f_itemID int," +
                            "timeLeft int NOT NULL," +
                            "qty double NOT NULL," +
                            "PRIMARY KEY(requestID)," +
                            "FOREIGN KEY (f_locationID) REFERENCES space_locations(locationID)," +
                            "FOREIGN KEY (f_itemID) REFERENCES space_items(itemID)" +
                            ") ENGINE=InnoDB;";
                        context.pool.query(createString, function (err) {
                            if (err) {
                                console.log('[MSQL] Error: ' + err);
                            } else {}
                            createString =
                                "CREATE TABLE space_itemTransit (" +
                                "transitID int AUTO_INCREMENT," +
                                "f_itemID int," +
                                "f_startLocation int," +
                                "f_endLocation int," +
                                "qty double NOT NULL," +
                                "currentTime int NOT NULL," +
                                "totalTime int NOT NULL," +
                                "PRIMARY KEY(transitID)," +
                                "FOREIGN KEY (f_startLocation) REFERENCES space_locations(locationID)," +
                                "FOREIGN KEY (f_endLocation) REFERENCES space_locations(locationID)," +
                                "FOREIGN KEY (f_itemID) REFERENCES space_items(itemID)" +
                                ") ENGINE=InnoDB;";
                            context.pool.query(createString, function (err) {
                                if (err) {
                                    console.log('[MSQL] Error: ' + err);
                                } else {}
                                createString =
                                    "CREATE TABLE space_locationTransit (" +
                                    "locationTransitID int AUTO_INCREMENT," +
                                    "f_startLocation int," +
                                    "f_endLocation int," +
                                    "totalTime int NOT NULL," +
                                    "PRIMARY KEY(locationTransitID)," +
                                    "FOREIGN KEY (f_startLocation) REFERENCES space_locations(locationID)," +
                                    "FOREIGN KEY (f_endLocation) REFERENCES space_locations(locationID)" +
                                    ") ENGINE=InnoDB;";
                                context.pool.query(createString, function (err) {
                                    if (err) {
                                        console.log('[MSQL] Error: ' + err);
                                    } else {
                                        context.insertCodex('transit');
                                    }
                                });

                            });
                        });
                    });
                });
            });
        });
    };

    // Functions are defined. Do any initialization needed.
    this.createTables();
}