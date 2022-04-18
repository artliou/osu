function neoViewer(parentDOMObject) {
    this.currentDate = Date.now();
    this.dayMSRange = 8.64e+7;
    this.dateRange = 3;
    this.parentDOMObject = parentDOMObject;
    this.dataSet = {};

    this.diameter = {
        earth: 12742,
        moon: 3474,
    };

    this.distance = {
        toMoon: 225623
    }

    this.graphicObjects = {};

    this.Initalize = function () {
        console.log('[neoWS] Initalizing graphics.')
        this.viewportWidth = document.getElementById(parentDOMObject).offsetWidth - 40;
        this.viewportHeight = document.getElementById(parentDOMObject).offsetHeight - 40;
        this.graphics = Raphael(this.parentDOMObject, this.viewportWidth, this.viewportHeight);

        this.createUIGraphics();
        this.getNeoWSData(this);
        document.getElementById('closeHelp').addEventListener('click', function () {
            document.getElementById('helpBox').style.display = "none";
        });
    }

    this.parseNeoWSData = function (data, context) {
        context.dataSet = data;
        context.updateGraphics(context);
    };

    this.getNeoWSData = function (context) {
        var startDate = new Date(this.currentDate - (this.dayMSRange * this.dateRange));
        var endDate = new Date(this.currentDate + (this.dayMSRange * this.dateRange));
        getNeoWSData(startDate.toISOString().substring(0, 10),
            endDate.toISOString().substring(0, 10),
            this.parseNeoWSData, context);
    };

    this.createUIGraphics = function () {
        console.log('[neoWS] Creating UI graphics.');
        this.graphicObjects.leftArrow = this.graphics.image('images/arrow.png', 10, this.viewportHeight - 74, 64, 64);
        this.graphicObjects.leftArrow.rotate(180);
        this.graphicObjects.rightArrow = this.graphics.image('images/arrow.png', this.viewportWidth - 74, this.viewportHeight - 74, 64, 64);
        this.graphicObjects.leftArrow.click(function () {
            this.currentDate -= (this.dayMSRange); // * this.dateRange);
            this.getNeoWSData(this);
        }.bind(this));
        this.graphicObjects.rightArrow.click(function () {
            this.currentDate += (this.dayMSRange); // * this.dateRange);
            this.getNeoWSData(this);
        }.bind(this));

        this.graphicObjects.dataSetCountText = this.graphics.text(10, 20, 'Objects in Dataset: ' + this.dataSet.element_count);
        this.graphicObjects.dataSetCountText.attr("fill", "#444");
        this.graphicObjects.dataSetCountText.attr("stroke", "#00f");
        this.graphicObjects.dataSetCountText.attr("text-anchor", "start");
        this.graphicObjects.dataSetCountText.attr("font-size", "25px");

        this.graphicObjects.startDateText = this.graphics.text(10, this.viewportHeight / 3, 'YYYY-MM-DD');
        this.graphicObjects.startDateText.rotate(90);
        this.graphicObjects.startDateText.attr("fill", "#444");
        this.graphicObjects.startDateText.attr("stroke", "#00f");
        this.graphicObjects.startDateText.attr("text-anchor", "start");
        this.graphicObjects.startDateText.attr("font-size", "25px");

        this.graphicObjects.endDateText = this.graphics.text(this.viewportWidth - 20, this.viewportHeight / 3, 'YYYY-MM-DD');
        this.graphicObjects.endDateText.rotate(90);
        this.graphicObjects.endDateText.attr("fill", "#444");
        this.graphicObjects.endDateText.attr("stroke", "#00f");
        this.graphicObjects.endDateText.attr("text-anchor", "start");
        this.graphicObjects.endDateText.attr("font-size", "25px");

        var earthWidth = this.viewportWidth * 0.15;
        var earthX = (this.viewportWidth / 2) - (earthWidth / 2);
        this.graphicObjects.earth = this.graphics.image('images/earth.png', earthX, this.viewportHeight * 0.85, earthWidth, earthWidth);

        var moonWidth = earthWidth * (this.diameter.moon / this.diameter.earth);
        var moonX = (this.viewportWidth / 2) - (moonWidth / 2);
        this.graphicObjects.moon = this.graphics.image('images/moon.png', moonX, this.viewportHeight * 0.05, moonWidth, moonWidth);

    };

    this.updateGraphics = function (context) {
        console.log('[neoWS] Updating dataset graphics');

        // Extract keys from the list of asteroids
        // Sort keys by date
        var keys = Object.keys(context.dataSet.near_earth_objects).sort(function (a, b) {
            var dateA = new Date(a);
            var dateB = new Date(b);
            if (dateA > dateB) {
                return true;
            } else {
                return false;
            }
        });

        context.graphicObjects.dataSetCountText.attr("text", 'Objects in Dataset: ' + context.dataSet.element_count);
        //console.log(context.dataSet);
        context.graphicObjects.startDateText.attr("text", keys[0]);
        context.graphicObjects.endDateText.attr("text", keys[keys.length - 1]);

        var maxRange = 0;

        for (var keyIndex = 0; keyIndex < keys.length; keyIndex++) {
            var localSet = context.dataSet.near_earth_objects[keys[keyIndex]];

            // Sort asteroids by distance to earth.
            context.dataSet.near_earth_objects[keys[keyIndex]].sort(function (a, b) {
                if (a.close_approach_data[0].miss_distance.kilometers > b.close_approach_data[0].miss_distance.kilometers) {
                    return true;
                } else {
                    return false;
                }
            });

            // Calculate the maximum distance from earth to the furthest asteroid.

            for (var localIndex = 0; localIndex < localSet.length; localIndex++) {
                maxRange = Math.max(maxRange, localSet[localIndex].close_approach_data[0].miss_distance.kilometers);
            }
        }

        context.graphicObjects.moon.attr('y',
            context.calculateObjectDistance(context.distance.toMoon, maxRange, context));

        // Draw the asteroids!!
        context.ClearGraphicSet(context);
        context.graphics.setStart();
        for (var keyIndex = 0; keyIndex < keys.length; keyIndex++) {
            var localSet = context.dataSet.near_earth_objects[keys[keyIndex]];
            for (var localIndex = 0; localIndex < localSet.length; localIndex++) {
                var asteroidY = context.calculateObjectDistance(localSet[localIndex].close_approach_data[0].miss_distance.kilometers, maxRange, context);
                var asteroidX = context.calculateObjectPassing(keyIndex, keys.length, context);
                var asteroidDiameterKM = (localSet[localIndex].estimated_diameter.kilometers.estimated_diameter_max + localSet[localIndex].estimated_diameter.kilometers.estimated_diameter_min) / 2;
                var asteroidR = asteroidDiameterKM * 15;
                asteroidR = Math.max(asteroidR, 5);
                asteroidR = Math.min(asteroidR, 30);
                var newAsteroid = context.graphics.circle(asteroidX, asteroidY, asteroidR);
                newAsteroid.attr("stroke", "#fff");
                if (localSet[localIndex].is_potentially_hazardous_asteroid === true) {
                    newAsteroid.attr("fill", "#f00");
                } else {
                    newAsteroid.attr("fill", "#88f");
                }
                var titleText = 'Click to open information about: ' + localSet[localIndex].name + '\n';
                titleText += 'Missed Earth by: ' + localSet[localIndex].close_approach_data[0].miss_distance.kilometers + ' km\n';
                titleText += 'Size in KM: ' + asteroidDiameterKM + '\n';
                if (localSet[localIndex].is_potentially_hazardous_asteroid === true) {
                    titleText += "POTENTIALLY HAZARDOUS!!";
                }
                newAsteroid.attr("title", titleText);

                newAsteroid.click(context.GenerateJPLURL(localSet[localIndex]));
                newAsteroid.mouseover(context.GenerateGlowEffect(newAsteroid, context));
                newAsteroid.mouseout(context.ClearGlowEffect(context));
            }
        }
        context.asteroidGraphicSet = context.graphics.setFinish();
    };

    this.calculateObjectPassing = function (index, max, context) {
        var left = context.viewportWidth * 0.05;
        var right = context.viewportWidth * 0.95;

        var result = (((index / max)) * (right - left)) + left;

        return result;
    };

    this.calculateObjectDistance = function (position, max, context) {
        var top = context.viewportHeight * 0.05;
        var bottom = context.viewportHeight * 0.85;

        var result = ((1 - (position / max)) * (bottom - top)) + top;

        return result;
    };

    this.ClearGraphicSet = function (context) {
        try {
            context.asteroidGraphicSet.forEach(function (element) {
                element.remove();
            }, context);
        } catch (exception) {}
    }

    this.GenerateJPLURL = function (localSet) {
        return function () {
            console.log('Opening URL: ' + localSet.nasa_jpl_url);
            window.open(localSet.nasa_jpl_url, '_blank');
        }
    };
    this.GenerateGlowEffect = function (newAsteroid, context) {
        return function () {
            context.glowSet = newAsteroid.glow({
                size: 40,
                color: "white"
            });
        }
    };
    this.ClearGlowEffect = function (context) {
        return function () {
            context.glowSet.forEach(function (element) {
                element.remove();
            });
        }
    };

}