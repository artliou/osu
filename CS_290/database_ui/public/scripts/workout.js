////////////////////////////////////////////////////////////
//
// Bootstrap components once the page is loaded
//

var sortType = 0;
var lastSortType = 0;
var localDataSet = [];

////////////////////////////////////////////////////////////
//
// Initalize any DOM objects data
//


////////////////////////////////////////////////////////////
//
// Click handler functions
//

function sortDate() {
    sortType = 0;
    updateSorttype();
}

function sortWeight() {
    sortType = 1;
    updateSorttype();
}

function sortReps() {
    sortType = 2;
    updateSorttype();
}

function clearAll() {
    deleteAllWorkouts();
}

////////////////////////////////////////////////////////////
//
// Client DOM update functions
//

function updateSorttype() {
    if (lastSortType == sortType) {
        return;
    } else {
        lastSortType = sortType;
        getWorkouts(updateWorkouts);
    }
}

function deleteAllWorkouts() {
    deleteAllWorkout(updateWorkouts);
}

function updateWorkouts() {
    console.log("Updating Workouts...");
    var parentElement = document.getElementById('workoutData');

    // Remove all child nodes
    while (parentElement.hasChildNodes()) {
        parentElement.removeChild(parentElement.lastChild);
    }

    // Add new data elements to the DOM
    for (var workoutIndex = 0; workoutIndex < localDataSet.length; workoutIndex++) {
        var currentWorkout = localDataSet[workoutIndex];

        var newDiv = document.createElement("div");
        newDiv.className = "workout-content";

        var nameDiv = document.createElement("div");
        nameDiv.id = currentWorkout.name + "-name";
        nameDiv.className = "workout-content-text"
        var nameSpan = document.createElement("span");
        nameSpan.className = "workout-content-span";
        nameSpan.innerText = currentWorkout.name;
        nameDiv.appendChild(nameSpan);

        var dateDiv = document.createElement("div");
        dateDiv.id = currentWorkout.name + "-date";
        dateDiv.className = "workout-content-text"
        var dateSpan = document.createElement("span");
        dateSpan.className = "workout-content-span";
        dateSpan.innerText = new Date(currentWorkout.date).toLocaleString();
        dateDiv.appendChild(dateSpan);

        var repsDiv = document.createElement("div");
        repsDiv.id = currentWorkout.name + "-reps";
        repsDiv.className = "workout-content-text"
        var repsSpan = document.createElement("span");
        repsSpan.className = "workout-content-span";
        repsSpan.innerText = currentWorkout.reps;
        repsDiv.appendChild(repsSpan);

        var weightTypeDiv = document.createElement("div");
        weightTypeDiv.id = currentWorkout.name + "-weightType";
        weightTypeDiv.className = "workout-content-text"
        var lbs = 0;
        var kg = 0;
        if (currentWorkout.lbs === 1) {
            lbs = currentWorkout.weight;
            kg = currentWorkout.weight * 0.453592;
        } else {
            kg = currentWorkout.weight;
            lbs = currentWorkout.weight * 2.20462;
        }
        var weightSpan = document.createElement("span");
        weightSpan.className = "workout-content-span";
        weightSpan.innerHTML = lbs.toFixed(0) + " lbs<br>" + kg.toFixed(0) + " kg";
        weightTypeDiv.appendChild(weightSpan);

        var clearStyleDiv = document.createElement("div");
        clearStyleDiv.id = currentWorkout.name + "-reset";
        clearStyleDiv.className = "workout-content-reset"

        var editWorkout = document.createElement("div");
        editWorkout.id = currentWorkout.name + "-edit";
        editWorkout.className = "workout-content-edit"
        var editSpan = document.createElement("span");
        editSpan.className = "workout-content-span";
        editSpan.innerText = "Edit Workout";
        editWorkout.appendChild(editSpan);

        var deleteWorkout = document.createElement("div");
        deleteWorkout.id = currentWorkout.name + "-delete";
        deleteWorkout.className = "workout-content-delete";
        var deleteSpan = document.createElement("span");
        deleteSpan.className = "workout-content-span";
        deleteSpan.innerText = "Delete Workout";
        deleteWorkout.appendChild(deleteSpan);
        deleteWorkout.onclick = GenerateDeleteFunction(currentWorkout.workoutID);

        newDiv.appendChild(dateDiv);
        newDiv.appendChild(nameDiv);
        newDiv.appendChild(repsDiv);
        newDiv.appendChild(weightTypeDiv);

        newDiv.appendChild(editWorkout);
        newDiv.appendChild(clearStyleDiv);
        newDiv.appendChild(deleteWorkout);

        parentElement.appendChild(newDiv);


        ///////////////////////////////////////////////////////////////
        //
        // Create the edit form embedded in the results list, but hide it.
        //

        var editDiv = document.createElement("div");
        editDiv.className = "workout-content";
        editDiv.style.display = "none";

        editWorkout.onclick = GenerateEditFunction(newDiv, editDiv);

        var editForm = document.createElement("form");
        editForm.className = "form-inline";

        ////////////////////////////
        //
        // Date Edit

        var editDateDiv = document.createElement("div");
        editDateDiv.className = "form-group";
        editDateDiv.style.width = "20%";
        var editDateInput = document.createElement("input");
        editDateInput.setAttribute("type", "text");
        editDateInput.className = "form-control";
        editDateInput.id = "edit-date-" + currentWorkout.name;
        editDateInput.value = new Date(currentWorkout.date).toLocaleString();

        ////////////////////////////
        //
        // Name Edit

        var editNameDiv = document.createElement("div");
        editNameDiv.className = "form-group";
        editNameDiv.style.width = "20%";
        var editNameInput = document.createElement("input");
        editNameInput.setAttribute("type", "text");
        editNameInput.className = "form-control";
        editNameInput.id = "edit-Name-" + currentWorkout.name;
        editNameInput.value = currentWorkout.name;

        ////////////////////////////
        //
        // Reps Edit

        var editRepsDiv = document.createElement("div");
        editRepsDiv.className = "form-group";
        editRepsDiv.style.width = "20%";
        var editRepsInput = document.createElement("input");
        editRepsInput.setAttribute("type", "text");
        editRepsInput.className = "form-control";
        editRepsInput.id = "edit-Reps-" + currentWorkout.name;
        editRepsInput.value = currentWorkout.reps;

        var editWeightDiv = document.createElement("div");
        editWeightDiv.className = "form-group";
        editWeightDiv.style.width = "20%";
        var editWeightInput = document.createElement("input");
        editWeightInput.setAttribute("type", "text");
        editWeightInput.className = "form-control";
        editWeightInput.id = "edit-Weight-" + currentWorkout.name;
        editWeightInput.value = currentWorkout.weight;

        ////////////////////////////
        //
        // Weight Type Edit

        var editWeightTypeDiv = document.createElement("div");
        editWeightTypeDiv.className = "form-group";
        editWeightTypeDiv.setAttribute("data-toggle", "buttons");

        var editWeightLBSLabel = document.createElement("label");
        editWeightLBSLabel.innerText = "LBS";
        if (currentWorkout.lbs) {
            editWeightLBSLabel.className = "btn btn-primary active";
        } else {
            editWeightLBSLabel.className = "btn btn-primary";
        }

        var editWeightLBSInput = document.createElement("input");
        editWeightLBSInput.setAttribute("type", "radio");
        editWeightLBSInput.name = "options";
        editWeightLBSInput.id = "edit-Weight-" + currentWorkout.name + "-lbs";
        editWeightLBSInput.autocomplete = "off";
        editWeightLBSInput.checked = currentWorkout.lbs;

        var editWeightKGLabel = document.createElement("label");
        editWeightKGLabel.innerText = "KG";
        if (!currentWorkout.lbs) {
            editWeightKGLabel.className = "btn btn-primary active";
        } else {
            editWeightKGLabel.className = "btn btn-primary";
        }

        var editWeightKGInput = document.createElement("input");
        editWeightKGInput.setAttribute("type", "radio");
        editWeightKGInput.name = "options";
        editWeightKGInput.id = "edit-Weight-" + currentWorkout.name + "-kg";
        editWeightKGInput.autocomplete = "off";
        editWeightKGInput.checked = !currentWorkout.lbs;

        ////////////////////////////
        //
        // Save changes

        var submitEditDiv = document.createElement("div");
        submitEditDiv.className = "form-group";
        submitEditDiv.setAttribute("data-toggle", "buttons");
        var submitEditButton = document.createElement("button");
        submitEditButton.className = "btn btn-primary";
        submitEditButton.type = "button";
        submitEditButton.id = "submit-changes-" + currentWorkout.name;
        submitEditButton.setAttribute("data-loading-text", "Submit");
        submitEditButton.style.marginLeft = "15%";
        submitEditButton.autocomplete = "off";
        submitEditButton.innerText = "Save changes";

        editDateDiv.appendChild(editDateInput);
        editNameDiv.appendChild(editNameInput);
        editRepsDiv.appendChild(editRepsInput);
        editWeightDiv.appendChild(editWeightInput);

        editWeightLBSLabel.appendChild(editWeightLBSInput);
        editWeightKGLabel.appendChild(editWeightKGInput);
        editWeightTypeDiv.appendChild(editWeightLBSLabel);
        editWeightTypeDiv.appendChild(editWeightKGLabel);

        submitEditDiv.appendChild(submitEditButton);

        editForm.appendChild(editDateDiv);
        editForm.appendChild(editNameDiv);
        editForm.appendChild(editRepsDiv);
        editForm.appendChild(editWeightDiv);
        editForm.appendChild(editWeightTypeDiv);
        editForm.appendChild(submitEditDiv);


        editDiv.appendChild(editForm);
        parentElement.appendChild(editDiv);
        submitEditButton.onclick = GenerateSubmitFunction(newDiv, editDiv, currentWorkout.workoutID, editDateInput, editNameInput, editRepsInput, editWeightInput, editWeightLBSInput);
    }
}

////////////////////////////////////////////////////////////
//
// UI database generator functions
//

function GenerateDeleteFunction(workoutID) {
    return function () {
        deleteWorkout(workoutID, function () {
            getWorkouts(updateWorkouts);
        })
    }
}

function GenerateEditFunction(workoutDiv, editDiv) {
    return function () {
        workoutDiv.style.display = "none";
        editDiv.style.display = "block";
    }
}

function GenerateSubmitFunction(workoutDiv, editDiv, workoutID, editDateInput, editNameInput, editRepsInput, editWeightInput, editWeightLBSInput) {
    return function () {
        workoutDiv.style.display = "block";
        editDiv.style.display = "none";
        var payload = {
            name: editNameInput.value,
            reps: editRepsInput.value,
            weight: editWeightInput.value,
            date: editDateInput.value,
            lbs: editWeightLBSInput.checked,
            workoutID: workoutID
        };
        updateWorkout(payload, function () {
            getWorkouts(updateWorkouts);
        });
    }
}

function postAddWorkout() {
    getWorkouts(updateWorkouts);
    updateClientTime();
}

////////////////////////////////////////////////////////////
//
// Database access functions
//

function getWorkouts(callback) {
    var req = new XMLHttpRequest();
    var targetUrl = '/getWorkouts?sortby=' + sortType;
    console.log("[Workout] Getting workouts [" + targetUrl + "]");
    req.open('GET', targetUrl, true);
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = JSON.parse(req.responseText);
                console.log(req.responseText);
                callback();
            } catch (exception) {}
        }
    };
    req.send(null);
}

function addWorkout(callback) {
    console.log("[Workout] Adding workout.");
    var payload = {
        name: document.getElementById('name').value,
        reps: document.getElementById('reps').value,
        weight: document.getElementById('weight').value,
        date: document.getElementById('date').value,
        lbs: document.getElementById('weight_lbs').checked
    };
    var req = new XMLHttpRequest();
    var targetUrl = '/insertWorkout';
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

function updateWorkout(payload, callback) {
    console.log("[Workout] Adding workout.");
    var req = new XMLHttpRequest();
    var targetUrl = '/updateWorkout';
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

function deleteWorkout(workoutID, callback) {
    console.log("[Workout] Deleting workout :" + workoutID);
    var payload = {
        workoutID: workoutID
    };
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteWorkout';
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

function deleteAllWorkout(callback) {
    console.log("[Workout] Deleting all workouts.");
    var req = new XMLHttpRequest();
    var targetUrl = '/deleteAllWorkouts';
    req.open('POST', targetUrl, true);
    req.setRequestHeader("Content-type", "application/json");
    req.onreadystatechange = function () {
        if (req.status == 200 && req.readyState === 4) {
            try {
                localDataSet = [];
                callback();
            } catch (exception) {}
        }
    };
    req.send(null);
}

function updateClientTime() {
    document.getElementById('date').value = new Date(Date.now()).toLocaleString();
}

////////////////////////////////////////////////////////////
//
// Client startup functions
//

// Set the Date input to the current DATETIEM (sql)
updateClientTime();

getWorkouts(updateWorkouts);