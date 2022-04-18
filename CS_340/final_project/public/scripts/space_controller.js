////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

////////////////////////////////////////////////////////////
//
// Initalize any DOM objects data
//

var context = this;

this.setupGraphics = function () {
    this.spaceView = new SpaceView(document.getElementById("spaceView"), context);
}

////////////////////////////////////////////////////////////
//
// Global timer
//

this.timerRunning = true;
this.timerStep = 50;
this.timerDelta = timerStep;

function timerClick() {
    if (context.timerRunning) {
        context.timerRunning = false;
        context.timerDelta = 0;
    } else {
        context.timerRunning = true;
        context.timerDelta = 100;
    }
    context.timerRunning = true;
    context.timerDelta = timerStep;
    this.currentTime = 0;
}

function sendItems() {
    var itemToSend = document.getElementById('itemToSend').innerText;
    var destination = document.getElementById('itemDestinationLocation').innerText;
    var itemQty = document.getElementById('itemQtySend').value;
    var sendPayload = {
        itemName: itemToSend,
        endLocationName: destination,
        startLocationName: spaceView.currentLocation.name,
        itemID: context.FindItemByName(itemToSend).itemID,
        startLocation: spaceView.currentLocation.locationID,
        endLocation: context.FindLocationByName(destination).locationID,
        qty: parseInt(itemQty),
        currentTime: 0,
        totalTime: context.FindTransitTime(spaceView.currentLocation.locationID, context.FindLocationByName(destination).locationID)
    };
    moveItemLocation(sendPayload);
}

this.FindItemByName = function (item) {
    for (var itemIndex = 0; itemIndex < context.spaceItems.length; itemIndex++) {
        var currentItem = context.spaceItems[itemIndex];
        if (currentItem.name === item) {
            return currentItem;
        }
    }
    return undefined;
}

this.FindLocationByName = function (location) {
    for (var locationIndex = 0; locationIndex < context.spaceLocations.length; locationIndex++) {
        var currentLocation = context.spaceLocations[locationIndex];
        if (currentLocation.name === location) {
            return currentLocation;
        }
    }
    return undefined;
}

this.FindTransitTime = function (startLocation, endLocation) {
    for (var outerLoop = 0; outerLoop < context.spaceTransit.length; outerLoop++) {
        for (var innerLoop = 0; innerLoop < context.spaceTransit.length; innerLoop++) {
            if (context.spaceTransit[innerLoop].f_startLocation === context.spaceTransit[outerLoop].f_endLocation) {
                return context.spaceTransit[innerLoop].totalTime;
            }
        }
    }
    return undefined;
}

this.startTimer = function () {
    var resetValue = 10000;
    this.currentTime = resetValue;
    setInterval(function () {
        this.currentTime -= context.timerDelta;
        if (this.currentTime < 1) {
            this.currentTime = resetValue;
            this.updateDatabaseContent();
        }
        var curTimeString = Math.floor(this.currentTime / 1000) + "." + ((this.currentTime / 1000) % 1).toPrecision(5).substring(2, 5);
        document.getElementById("timerControl").innerText = curTimeString;
    }, timerStep);
}


////////////////////////////////////////////////////////////
//
// Database logic functions
//

this.updateDatabaseContent = function () {
    for (var productionIndex = 0; productionIndex < this.spaceProduction.length; productionIndex++) {
        var currentProduction = this.spaceProduction[productionIndex];
        addItemToLocation({
            itemID: currentProduction.f_itemID,
            locationID: currentProduction.f_locationID,
            qty: (Math.random() * (currentProduction.max - currentProduction.min)) + currentProduction.min,
        }, undefined);
    }

    getItemsByLocation(this.spaceView.currentLocation, this.spaceView.updateSideBarItems);

    getTransitItems(stepTransitItems);
}

////////////////////////////////////////////////////////////
//
// Database access functions
//

function getDBItem(targetUrl, callback) {
    var req = new XMLHttpRequest();
    console.log("[SPACE] Getting DB object : " + targetUrl);
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

function addItemToLocation(payload, callback) {
    console.log("[SPACE ITEM] Adding " + payload.itemID + " at location " + payload.locationID + " [Qty: " + payload.qty + "]");
    var req = new XMLHttpRequest();
    var targetUrl = '/createItem';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function getItemsByLocation(currentLocation, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getItemsAtLocation?locationID=' + currentLocation.locationID;
    console.log("[SPACE ITEM] Getting items at [" + currentLocation.locationID + "]");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(currentLocation, JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

function getTransitItems(callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getTransitItems';
    console.log("[SPACE ITEM] Getting Transit items");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

function getLocationDestinations(currentLocation, callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getLocationDestinations?locationID=' + currentLocation.locationID;
    console.log("[SPACE ITEM] Getting destinations for [" + currentLocation.locationID + "]");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                callback(currentLocation, JSON.parse(req.responseText));
            } catch (exception) {}
        }
    };
    req.send(null);
}

function DeleteLocationItem(locationItemID) {
    console.log("[SPACE ITEM] Deleting locationItem " + locationItemID);
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteItem';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify({
        locationItemID: locationItemID
    }));
}

function moveItemLocation(payload) {
    var comsumeIDs = [];
    //context.spaceView.locationItems
    var totalPayload = payload.qty;

    ////////////////////////////////////////////////
    //
    // Find items to send
    //

    for (var locationItemIndex = 0; locationItemIndex < context.spaceView.locationItems.length; locationItemIndex++) {
        var currentItem = context.spaceView.locationItems[locationItemIndex];
        if ((currentItem.itemName === payload.itemName) && (totalPayload > 0)) {
            comsumeIDs.push(currentItem.itemLocationID);
            totalPayload -= currentItem.qty;
        }
    }

    ////////////////////////////////////////////////
    //
    // Delete transit items from database
    //

    for (var consumeIndex = 0; consumeIndex < comsumeIDs.length; consumeIndex++) {
        DeleteLocationItem(comsumeIDs[consumeIndex]);
    }

    var outgoingQty = -totalPayload + payload.qty;

    ////////////////////////////////////////////////
    //
    // Create transit object
    //
    payload.qty = outgoingQty;
    CreateTransitObject(payload);
}

function CreateTransitObject(payload) {
    console.log("[SPACE ITEM] Creating Transit object");
    var req = new XMLHttpRequest();
    var targetUrl = '/createTransitItem';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

////////////////////////////////////////////////////////////
//
// Transient Object functions
//

function updateTransitItems(payload, callback) {
    console.log("[SPACE ITEM] updating transient Object");
    var req = new XMLHttpRequest();
    var targetUrl = '/updateTransitItem';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function deleteTransitItem(payload, callback) {
    console.log("[SPACE ITEM] Deleting transient Object");
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteTransitItem';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                //localDataSet = req.responseText;
                callback();
            } catch (exception) {}
        }
    };
    req.send(JSON.stringify(payload));
}

function stepTransitItems(data) {

    context.spaceView.ResetTransit();

    for (var dataIndex = 0; dataIndex < data.length; dataIndex++) {

        var currentData = data[dataIndex];

        //////////////////////////////////////////////////
        //
        // Check if transit has arrived
        //

        console.log(currentData);
        if (currentData.currentTime === currentData.totalTime) {
            deleteTransitItem({
                transitID: currentData.transitID
            });
            addItemToLocation({
                itemID: currentData.f_itemID,
                locationID: currentData.f_endLocation,
                qty: currentData.qty
            }, undefined);
        } else {
            spaceView.AddTransit(currentData);
            updateTransitItems({
                currentTime: currentData.currentTime + 1,
                transitID: currentData.transitID
            })
        }
    }

    context.spaceView.EndTransit();
}

////////////////////////////////////////////////////////////
//
// Helper functions
//

this.FindSpaceLocationByID = function (testID) {
    for (var locationID = 0; locationID < context.spaceLocations.length; locationID++) {
        var currentLocation = context.spaceLocations[locationID];
        if (currentLocation.locationID === testID) {
            return currentLocation;
        }
    }
    return undefined;
}

////////////////////////////////////////////////////////////
//
// Client startup functions
//

this.Init = function () {
    this.setupGraphics();

    // Get static SQL data
    getDBItem('/getItems', function (items) {
        context.spaceItems = items;

        getDBItem('/getLocations', function (locations) {
            context.spaceLocations = locations;
            context.spaceView.CreateLocations(context.spaceLocations);

            getDBItem('/getProduction', function (production) {
                context.spaceProduction = production;
                getDBItem('/getTransit', function (transit) {
                    context.spaceTransit = transit;
                    this.startTimer();
                    this.updateDatabaseContent();
                });
            });
        });
    });
}

this.Init();