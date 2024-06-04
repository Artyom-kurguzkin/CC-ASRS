const functions = require('firebase-functions');
const express = require('express');
const path = require('path');
const fs = require('fs');
const axios = require('axios');
const cors = require('cors');


const app = express();

app.use(cors());

app.use(express.json());
app.use(express.urlencoded({extended: true})); 



// check who logs in and log!
app.post('/login', (req, res) => {
    
    const { email } = req.body;
    axios.post('http://34.151.86.177/logUser', email);
    console.log( req.body );

    let redirectUrl; // Define redirectUrl outside the if-else blocks
    if (userName.toLowerCase() === "alicepharmacist") {
        redirectUrl = "http://34.151.86.177/ui/#!/0?socketid=HxzMq6Yc0o7lBZnNAABR";
    } else if (userName.toLowerCase() === "bobstaff") {
        redirectUrl = "http://34.151.86.177/ui/#!/1?socketid=HxzMq6Yc0o7lBZnNAABR";
    } else {
        redirectUrl = "https://www.google.com";
    }

    res.json({ redirectUrl });
});


// serve login page
app.get('/', (req, res) => {
    const filePath = path.join(__dirname, '..', 'public', 'index.html');
  
    fs.readFile(filePath, 'utf8', (err, data) => {
        if (err) {
            console.error('Error reading index.html:', err);
            return res.status(500).send('Internal Server Error');
        }
  
        res.send(data);
    });
});

exports.app = functions.https.onRequest(app);
//exports.app = functions.region('australia-southeast2').https.onRequest(app);