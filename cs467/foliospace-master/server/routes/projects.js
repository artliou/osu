const express = require('express');
var cloudinary = require('cloudinary').v2;
const configObj = require('../config');
const c_config = configObj.cloudinary;
const m_config = configObj.mysql;
const mysql = require('mysql');
const request = require('request');

const router = express.Router();

cloudinary.config({ 
    cloud_name: c_config.cloud_name,
    api_key: c_config.api_key, 
    api_secret: c_config.api_secret
});

var con = mysql.createConnection({
    host: m_config.host,
    user: m_config.user,
    password: m_config.password,
    database: m_config.database
});

/*-------- BEGIN MODEL FUNCTIONS --------*/

/** 
 * Get all of the user's projects.
 * Use this to list out projects.
 */
var getAllProjects = async function (name, callback){
    var queryString = "SELECT * FROM project WHERE `login` = ?";
    await con.query(queryString, [name], function (err, result, fields) {
        if (err) {
            callback(err, null);
        } else {
            callback(null, result);
        }
    });
}

/** 
 * Get a specific project.
 */
var getProject = async function (prjId, callback){
    var key = prjId;
    // Will need a link table between files and projects
    var queryString = "SELECT * FROM project WHERE projectId = ?";
    await con.query(queryString, [key], function (err, result, fields) {
        if (err) {
            callback(err, null);
        } else {
            callback(null, result);
        }
    });
}

/** 
 * Create a new project.
 * This should redirect to a page that allows editing of the project.
 */
var createProject = async function (name, blurb, login, callback){
    var queryString = "INSERT INTO project (`projectName`, `projectBlurb`, `login`) VALUES (?, ?, ?)";
    await con.query(queryString, [name, blurb, login], function (err, result) {
        if (err) {
            callback(err, null);
        } else {
            //console.log('createProject: Inside query result: ' + result.insertId);
            callback(null, result.insertId);
        }
    });
}

/** 
 * Update an existing project.
 */
var updateProject = async function (name, blurb, prjId, callback){
    var queryString = "UPDATE project SET `projectName` = ?, `projectBlurb` = ? WHERE `projectId` = ?";
    await con.query(queryString, [name, blurb, prjId], function (err, result) {
        if (err) {
            callback(err, null);
        } else {
            console.log('updateProject result: ' + result);
            callback(null, result);
        }
    });    
}

/** 
 * Delete a project.
 */
var deleteProject = async function (prjId, callback){
    var queryString = "DELETE FROM project WHERE `projectId` = ?";
    await con.query(queryString, [prjId], function (err, result) {
        if (err) {
            console.log("ERROR: " + err);
            callback(err, null);
        } else {
            console.log(result);
            callback(null, result);
        }
    });    
}

/**
 * Upload files
 * SOURCE: https://cloudinary.com/documentation/image_upload_api_reference#upload_method
 */
var uploadFiles = async function (data, prjId, callback){
    // send the public_id of the image(s) to the database
    // fileId is the auto-gen public_id from result JSON
    // fileUrl is part of the result JSON 
    var queryString = "INSERT INTO files (`fileId`, `projectId`, `fileUrl`) VALUES (?, ?, ?)";
    //var i;
    //for (i = 0; i < data.length; i++) {
        var fileId = data.info.public_id;
        var fileUrl = data.info.url;
        await con.query(queryString, [fileId, prjId, fileUrl], function (err, result) {
            if (err) {
                console.log("ERROR: " + err);
                callback(err, null);
            } else {
                console.log(result);
                callback(null, result);
            }
        });
    //}
}

/**
 * Get files
 * Returns JSON object
 * RESOURCES: https://cloudinary.com/documentation/admin_api
 */
function getAllFiles(prjId){
   cloudinary.v2.api.resources({ type: 'upload', prefix: prjId }, 
        function(error, result) { 
            return result;
        }
    );
}

/**
 * Get a specific file
 * Returns JSON object
 * RESOURCE:
 */
function getFile(fileId){
    cloudinary.v2.api.resources_by_ids(fileId, function(error, result) {
        return result;
    });
}

/**
 * Delete all files associated with a project
 * RESOURCE: https://cloudinary.com/documentation/admin_api#delete_resources
 */
function deleteAllFiles(projectId){
    cloudinary.v2.api.delete_resources_by_prefix(projectId, function(error, result) {
        return result;
    });
}

/**
 * Delete a specific file
 * RESOURCE: https://cloudinary.com/documentation/admin_api#delete_resources
 */
function deleteFile(fileId){
    cloudinary.v2.api.delete_resources([fileId], function(error, result){
        return result;
    });
}

/*-------- END MODEL FUNCTIONS --------*/

/*-------- BEGIN CONTROLLER FUNCTIONS --------*/

/** 
 * Get all of the user's projects.
 * Use this to list out projects.
 */
router.get('/', async function(req, res){
    let projectList = [];
    await getAllProjects(req.user.profile.login, function(err, data) {
        if (err) {
            console.log('ERROR: ' + err);
        } else {
            console.log(data);
            var i;
            for (i = 0; i < data.length; i++) {
                let project = {
                    'projectId': data[i].projectId,
                    'projectName': data[i].projectName 
                }
                projectList.push(project);
            }
            console.log(JSON.stringify(projectList));
            res.status(200);
            res.render('project_list', {"projectList": projectList});
        }
    })
});

/** 
 * Get a specific project.
 * This should redirect to a page that allows editing of the project.
 */
router.get('/:projectId', async function(req, res){
    let project;
    await getProject(req.params.projectId, function(err, data) {
        if (err) {
            console.log('ERROR: ' + err);
        } else {
            console.log(data);
            const accepts = req.accepts(['application/json']);
            if(!accepts){
                res.status(406).send('Content-Type must be application/json.');
            } else if (accepts) {
                project = {
                    'projectId': data[0].projectId,
                    'projectName': data[0].projectName,
                    'projectBlurb': data[0].projectBlurb
                }
                res.status(200);
                res.render('project', { "project": project });
            } else { 
                res.status(500).send('Content-Type got messed up!'); 
            }  
        }
    });
});

/** 
 * Create a new project.
 * This should redirect to a page that allows editing of the project (i.e. uploading photos).
 */
router.post('/', async function(req, res){
    // Create the project
    var name = "";
    var blurb = null;
    await createProject(name, blurb, req.user.profile.login, function(err, data) {
        if (err) {
            console.log(name + ", " + blurb + ", " + req.user.profile.login);
            console.log('ERROR: ' + err);
        } else {
            console.log('Project created. ID: ' + data);
            res.redirect(301,'/projects/' + data);
            /*
            // Redirect to the project edit page
            var options = {
                method: 'GET',
                url: req.protocol + "://" + req.get("host") + req.baseUrl + "/" + data
            }
            request(options, (error, response) => {
                if (error) {
                    res.render("error");
                } else {
                    res.status(200);
                }
            });
            */
        }
    });
});

/** 
 * Update an existing project.
 * Currently only allows for changing the name and description.
 */
router.put('/:projectId', async function(req, res){
    // SOURCE: http://classes.engr.oregonstate.edu/eecs/perpetual/cs493-400/modules/5-advanced-rest-api/3-nodejs-implementation/
    if(req.get('Content-Type') !== 'application/json'){
        res.status(415).send('Please resend with application/json data.').end();
    } else {
        await updateProject(req.body.name, req.body.blurb, req.params.projectId, function(err, data) {
            // Return a 303 code with the location of the updated project ID in the appropriate header field
            res.location(req.protocol + "://" + req.get("host") + req.baseUrl + "/" + req.params.projectId).status(303).end();
        });
    }
});

/** 
 * Delete a project.
 */
router.delete('/:projectId', async function(req, res){
    await deleteProject(req.params.projectId, function(err, data) {
        if (err) {
            console.log('ERROR: ' + err);
        } else {
            res.status(204).end();
        }      
    });
    
});

/** 
 * Upload Images to project
 * SOURCE: https://cloudinary.com/documentation/image_upload_api_reference#upload_method
 */
router.post('/:projectId/files', async function(req, res) {
    await uploadFiles(req.body, req.params.projectId, function(err, data) {
        if (err) {
            console.log('ERROR: ' + err);
        } else {
            res.status(201).json(data);
        }
    }); 
});

/**
 * Retrieve all images uploaded to a project
 * SOURCE: https://cloudinary.com/documentation/admin_api#browse_resources
 */
router.get(':/projectId/files', function(req, res) {
    const prjFiles = getAllFiles(req.params.projectId)
    .then( (prjFiles) => {
        console.log(prjFiles);
        res.status(200).json(prjFiles);
    });
});

/**
 * Retrieve a specific image uploaded to a project
 * SOURCE: https://cloudinary.com/documentation/admin_api#browse_resources
 */
router.get(':/projectId/files/:fileId', function(req, res) {
    const prjFile = getFile(req.params.fileId)
    .then( (prjFile) => {
        console.log(prjFile);
        res.status(200).json(prjFile);
    });
});

/**
 * Delete all files associated with a project
 * 
 */
router.delete(':/projectId/files', function(req, res) {
    deleteAllFiles(req.params.projectId)
    .then(res.status(204).end());
});

/**
 * Delete a specific file associated with a project
 * 
 */ 
router.delete(':/projectId/files/:fileId', function(req, res) {
    deleteFile(req.params.fileId)
    .then(res.status(204).end());
});
/*-------- END CONTROLLER FUNCTIONS --------*/

module.exports = router;
