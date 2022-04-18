var Guid = require('guid');

let instance = null;

module.exports = class {

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Initialization functions
    //

    constructor() {
        if (!instance) {
            instance = this;
            console.log('[DataStore] Created CoolPix');
            this.ResetUsers();
        }
        return instance;
    }

    ResetUsers() {
        this.users = {};
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Account Creation
    //

    CreateAccount (email, name) {
        if (email in this.users) {
            console.log (`[DataStore] User already exists [${email}]`);
            return this.users[email];
        }

        var newUser = {
            'Email': email,
            'Name': name,
            'CreationTime': Date.now(),
            'Posts': {}
        };

        console.log (`[DataStore] Creating user [${email}]`);
        this.users[email] = newUser;
        return newUser;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Creation
    //

    AddImage (email, imageData, title, body) {
        var imageID = Guid.create();
        var currentTime = Date.now();
        console.log (`[DataStore] User [${email}] adding image [${imageID}] [${title}] [${body}] @ [${currentTime}]`);
        this.users[email].Posts[imageID] = {
            imageID: imageID,
            user: email,
            postTime: currentTime,
            imageData: imageData,
            title: title,
            body: body
        };
        return imageID;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Edit
    //

    EditImage (email, imageID, imageAttribute, value) {
        console.log (`[DataStore] User [${email}] edited image [${imageID}] [${imageAttribute}]->[${value}]`);
        this.users[email].Posts[imageID][imageAttribute] = value;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Getting
    //

    GetImage (email, imageID) {
        console.log (`[DataStore] User [${email}] getting image [${imageID}]`);
        return this.users[email].Posts[imageID];
    }

    GetAllImages (email) {
        console.log (`[DataStore] User [${email}] get all images`);
        return this.users[email].Posts;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //
    // Post Delete
    //

    DeleteImage(email, imageID) {
        console.log (`[DataStore] User [${email}] delete image [${imageID}]`);
        delete this.users[email].Posts[imageID];
    }

}