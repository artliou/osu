var SpaceView = function (domElement, controller) {
    console.log('[SPACE VIEW] Initalizing graphics.')

    var context = this;

    this.parentDOMObject = domElement;
    this.viewportWidth = this.parentDOMObject.offsetWidth;
    this.viewportHeight = this.parentDOMObject.offsetHeight;
    this.viewportSize = this.viewportHeight + this.viewportWidth;
    this.graphics = Raphael(this.parentDOMObject, this.viewportWidth, this.viewportHeight);

    this.ClearNavLines = function () {
        if (context.navLineSet) {
            context.navLineSet.forEach(function (element) {
                element.remove();
            });
        }
    }
    this.ClearGlow = function () {
        if (context.glowSet) {
            context.glowSet.forEach(function (element) {
                element.remove();
            });
        }
    }

    this.GenerateLocationClick = function (currentLocation, graphicObject) {
        return function () {
            context.currentLocation = currentLocation;
            console.log("[SPACE VIEW] Selected location : " + currentLocation.name);
            document.getElementById('itemToSend').innerHTML = 'Item to send<span class="caret"/>';
            document.getElementById('itemDestinationLocation').innerHTML = 'Location to send to<span class="caret"/>';
            controller.getItemsByLocation(currentLocation, context.updateSideBarItems);
            context.ClearGlow();
            context.ClearNavLines();
            context.glowSet = graphicObject.glow({
                color: "40ffff",
                width: "2"
            });
        }
    };

    this.updateSideBarItems = function (currentLocation, dataSet) {
        console.log("[SPACE VIEW] Updating location ui : " + currentLocation.name);
        var summedData = {};
        context.locationItems = dataSet;
        for (var dataIndex = 0; dataIndex < dataSet.length; dataIndex++) {
            var currentData = dataSet[dataIndex];
            if (summedData[currentData.itemName] === undefined) {
                summedData[currentData.itemName] = {};
                summedData[currentData.itemName].totalAmmount = 0;
                summedData[currentData.itemName].packages = 0;
                summedData[currentData.itemName].name = currentData.itemName;
            }
            summedData[currentData.itemName].totalAmmount += currentData.qty;
            summedData[currentData.itemName].packages++;
        }
        document.getElementById('locationName').innerText = currentLocation.name;
        var locItems = document.getElementById('locationItems');
        locItems.innerHTML = "";
        var keys = Object.keys(summedData);
        if (keys.length === 0) {
            locItems.innerHTML = "<br>No items are at this location.<br><br>";
        } else {
            for (var summedIndex = 0; summedIndex < keys.length; summedIndex++) {
                var currentData = summedData[keys[summedIndex]];
                locItems.innerHTML += currentData.name + " : " + currentData.totalAmmount.toPrecision(5) + "<br>";
            }
        }


        ////////////////////////////////////////////////////////////////////////////////////////////
        //
        // Remove elements from dropdowns
        //
        var itemsToSend = document.getElementById('itemsToSend');
        while (itemsToSend.hasChildNodes()) {
            itemsToSend.removeChild(itemsToSend.lastChild);
        }
        var destLocation = document.getElementById('destinationLocations');
        while (destLocation.hasChildNodes()) {
            destLocation.removeChild(destLocation.lastChild);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////
        //
        // Add item elements
        //
        for (var keyIndex = 0; keyIndex < keys.length; keyIndex++) {
            var newItem = document.createElement('li');
            var newItemlink = document.createElement('a');
            newItemlink.innerText = keys[keyIndex];
            newItemlink.onclick = new context.GenerateItemSendClickHandler(keys[keyIndex]);
            newItem.appendChild(newItemlink);
            itemsToSend.appendChild(newItem);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////
        //
        // Add destination locations to drop down
        //
        controller.getLocationDestinations(currentLocation, context.UpdateLocationDestinations);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Transient items
    //

    this.ResetTransit = function () {
        if (context.TransitSet) {
            context.TransitSet.forEach(function (element) {
                element.remove();
            });
        }
        context.graphics.setStart();
    }

    this.AddTransit = function (payload) {
        console.log('Creating transit line');
        console.log(payload);
        var startLocation = controller.FindSpaceLocationByID(payload.f_startLocation);
        var endLocation = controller.FindSpaceLocationByID(payload.f_endLocation);
        var startX = startLocation.xLocation * context.viewportWidth;
        var startY = startLocation.yLocation * context.viewportHeight;
        var endX = endLocation.xLocation * context.viewportWidth;
        var endY = endLocation.yLocation * context.viewportHeight;
        var renderString = "M" + Math.floor(startX) + "," + Math.floor(startY) + " L" + Math.floor(endX) + "," + Math.floor(endY);
        console.log (renderString);
        var newLine = context.graphics.path(renderString)
        newLine.attr("stroke-width", "3");
        newLine.attr("stroke", "C34500");

        var travelDist = payload.currentTime / payload.totalTime;

        var middleX = ((endX - startX) * travelDist) + startX;
        var middleY = ((endY - startY) * travelDist) + startY;

        var newRect = context.graphics.rect (middleX - 10, middleY - 10, 20, 20, 4);
        newRect.attr("stroke-width", "3");
        newRect.attr("stroke", "C34500");
        newRect.attr("fill", "C34500");

        newRect.toBack();
        newLine.toBack();
    }

    this.EndTransit = function () {
        context.TransitSet = context.graphics.setFinish();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Client Update functions
    //

    this.UpdateLocationDestinations = function (currentLocation, dataSet) {
        var destLocation = document.getElementById('destinationLocations');
        context.ClearNavLines();
        context.graphics.setStart();
        for (var dataIndex = 0; dataIndex < dataSet.length; dataIndex++) {
            var newItem = document.createElement('li');
            var newItemlink = document.createElement('a');
            newItemlink.innerText = dataSet[dataIndex].locationName;
            newItemlink.onclick = new context.GenerateLocationDestClickHandler(dataSet[dataIndex].locationName);
            newItem.appendChild(newItemlink);
            destLocation.appendChild(newItem);

            ////////////////////////////////////////////////////////////////////////
            //
            // Draw the nav lines and save the graphics set
            //

            for (var locationIndex = 0; locationIndex < controller.spaceLocations.length; locationIndex++) {
                var testLocation = controller.spaceLocations[locationIndex];
                if (testLocation.locationID === dataSet[dataIndex].f_endLocation) {
                    var startX = currentLocation.xLocation * context.viewportWidth;
                    var startY = currentLocation.yLocation * context.viewportHeight;
                    var endX = testLocation.xLocation * context.viewportWidth;
                    var endY = testLocation.yLocation * context.viewportHeight;
                    var renderString = "M" + Math.floor(startX) + "," + Math.floor(startY) + " L" + Math.floor(endX) + "," + Math.floor(endY);
                    var newLine = context.graphics.path(renderString)
                    newLine.attr("stroke-width", "5");
                    newLine.attr("stroke", "40ffff");
                    newLine.toBack();
                }
            }
        }
        context.navLineSet = context.graphics.setFinish();
    }

    this.GenerateItemSendClickHandler = function (data) {
        return function () {
            document.getElementById('itemToSend').innerText = data;
        }
    }

    this.GenerateLocationDestClickHandler = function (data) {
        return function () {
            document.getElementById('itemDestinationLocation').innerText = data;
        }
    }

    this.CreateLocations = function (locationData) {
        for (var locationIndex = 0; locationIndex < locationData.length; locationIndex++) {
            var currentLocation = locationData[locationIndex];
            console.log("[SPACE VIEW] Creating location : " + currentLocation.name);
            console.log("[SPACE VIEW] x: " + currentLocation.xLocation + " y: " + currentLocation.yLocation);
            var newObject = this.graphics.circle(currentLocation.xLocation * this.viewportWidth, currentLocation.yLocation * this.viewportHeight, this.viewportSize * 0.007);
            switch (currentLocation.locationStyle) {
                case 1:
                    {
                        newObject.attr("fill", "#fff");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation, newObject));
                    }
                    break;
                case 2:
                    {
                        newObject.attr("fill", "#34e");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation, newObject));
                    }
                    break;
                case 3:
                    {
                        newObject.attr("fill", "#4fa");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation, newObject));
                    }
                    break;
                case 4:
                    {
                        newObject.attr("fill", "#27e");
                        newObject.attr("title", currentLocation.name);
                        newObject.click(context.GenerateLocationClick(currentLocation, newObject));
                    }
                    break;
            }

            // Go ahead and select the first location...
            if (locationIndex === 0) {
                context.currentLocation = currentLocation;
                console.log("[SPACE VIEW] Selected location : " + currentLocation.name);
                controller.getItemsByLocation(currentLocation, context.updateSideBarItems);
                context.glowSet = newObject.glow({
                    color: "40ffff",
                    width: "2"
                });

            }
        }
    }
};