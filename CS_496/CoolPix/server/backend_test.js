var DataStore = require('./app/datastore/datastore');

var dataStore = new DataStore();

var email = 'test@email.com'

dataStore.CreateAccount(email, 'Testy McTesterson');
var imageID = dataStore.AddImage(email, '#imagedata', '#title', '#body');
dataStore.EditImage(email, imageID, 'title', '#title2');
console.log (JSON.stringify(dataStore.GetImage(email, imageID)));
console.log (JSON.stringify(dataStore.GetAllImages(email)));

dataStore.DeleteImage(email, imageID);

console.log(JSON.stringify(dataStore.users));