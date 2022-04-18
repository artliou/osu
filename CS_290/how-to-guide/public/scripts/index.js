////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

window.onload = function () {
    //SetupRaphael();
}

var neoWSViewer = undefined;

////////////////////////////////////////////////////////////
//
// Show/Hide functions
//

function showNasa() {
    console.log('showNasa');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "block";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "none";
}

var graphicsCreated = false;

function showRaphael() {
    console.log('showRaphael');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "block";
    document.getElementById('exampleContent').style.display = "none";
    if (graphicsCreated === false) {
        graphicsCreated = true;
        SetupRaphael();
    }
}

var exampleCreated = false;

function showExample() {
    console.log('showExample');
    document.getElementById('welcomeContent').style.display = "none";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "block";
    if (exampleCreated === false) {
        exampleCreated = true;
        neoWSViewer = new neoViewer('neoIntegration');
        neoWSViewer.Initalize();
    }
}

function showWelcome() {
    document.getElementById('welcomeContent').style.display = "block";
    document.getElementById('nasaContent').style.display = "none";
    document.getElementById('raphaelContent').style.display = "none";
    document.getElementById('exampleContent').style.display = "none";

}

////////////////////////////////////////////////////////////
//
// NeoWs example
//

const APIKEY = '0XRgmcoq1HTEKEbDPx4ZXLtAPYpKVUfWHsdJ5ZNC';

function getNeoWSData(start, end, callback, context) {
    var req = new XMLHttpRequest();
    var targetUrl = 'https://api.nasa.gov/neo/rest/v1/feed?start_date=' + start + '&end_date=' + end + '&api_key=' + APIKEY;
    console.log('Getting NeoWs:' + targetUrl);
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status >= 200 && req.status < 400) {
            try {
                callback(JSON.parse(req.responseText), context);
            } catch (exception) {}
        } else {
            console.log("Error in network request: " + req.statusText);
        }
    };
    req.send(null);
}

function setExampleText(data) {
    var dataString = JSON.stringify(data);
    document.getElementById('example1_code').innerHTML = dataString.substring(0, 250) + '...';
    document.getElementById('example2_code').innerHTML += 'element_count: ' + data.element_count + '<br>';
    var dates = Object.keys(data.near_earth_objects);
    document.getElementById('example2_code').innerHTML += 'first date: ' + dates[0] + '<br>';
    var asteroid = data.near_earth_objects[dates[0]][0];
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].name = ' + asteroid.name + '<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].is_potentially_hazardous_asteroid = ' + asteroid.is_potentially_hazardous_asteroid + '<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].estimated_diameter(avg) = ' + (asteroid.estimated_diameter.kilometers.estimated_diameter_min + asteroid.estimated_diameter.kilometers.estimated_diameter_max) / 2 + ' km<br>';
    document.getElementById('example2_code').innerHTML += 'near_earth_objects[' + dates[0] + '][0].missed_earth_by = ' + asteroid.close_approach_data[0].miss_distance.kilometers + ' km<br>';
}

showWelcome();
getNeoWSData('2017-02-22', '2017-02-27', setExampleText, undefined);

////////////////////////////////////////////////////////////
//
// Raphael JS example
//

function SetupRaphael() {
    var viewportWidth = document.getElementById('raphaelExample1').offsetWidth - 40;
    var viewportHeight = document.getElementById('raphaelExample1').offsetHeight - 40;

    var graphics = Raphael('raphaelExample1', viewportWidth, viewportHeight);
    var circleObject = graphics.circle(viewportWidth / 2, viewportHeight / 2, viewportWidth / 10, viewportHeight / 10, viewportWidth / 15);
    circleObject.attr("fill", "#0f0");
    circleObject.attr("stroke", "#00f");
    circleObject.click(function () {
        alert('You clicked the circle!');
    });

    graphics = Raphael('raphaelExample2', viewportWidth, viewportHeight);
    var boxObject = graphics.rect(viewportWidth / 2, viewportHeight / 2, 20, 20, 3);
    boxObject.attr("fill", "#0f0");
    boxObject.attr("stroke", "#00f");
    var dragging = false;
    var location = {};
    var viewport = {
        x: 0,
        y: 0
    };
    document.getElementById('raphaelExample2').addEventListener("mousedown", function (event) {
        dragging = true;
        location.x = event.screenX;
        location.y = event.screenY;
    });
    document.getElementById('raphaelExample2').addEventListener("mouseup", function (event) {
        dragging = false;
    });
    document.getElementById('raphaelExample2').addEventListener("mousemove", function (event) {
        if (dragging === true) {
            var delta = {};
            delta.x = location.x - event.screenX;
            delta.y = location.y - event.screenY;
            location.x = event.screenX;
            location.y = event.screenY;
            viewport.x += delta.x;
            viewport.y += delta.y;
            graphics.setViewBox(viewport.x, viewport.y, viewportWidth, viewportHeight, false);
        }
    });

}