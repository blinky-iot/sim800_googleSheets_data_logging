# 📡 Google Sheets Logger with Apps Script (GET Method)
This is a guide on logging data to google sheets using Both WiFi and GPRS - SIM800L
---

## 🛠 Step 1: Set Up Google Apps Script

1. Open your **Google Sheet**.
2. Go to `Extensions > Apps Script`.
3. Delete any default code and paste the following:

```javascript

var spreadsheetId = SpreadsheetApp.openById("1v-_PdFnkY7R5TKFmVboEuaFvexIxk8vtSzg4Cy5Rr2o");
var sheet = spreadsheetId.getSheetByName("DHT");
var timezone = "Africa/Nairobi";


function doGet(e) {
  return postData(e);
}

function doPost(e) {
  return postData(e);
}

function postData(e) {
  Logger.log(JSON.stringify(e));

  // Basic error check
  if (!e.parameter.temp || !e.parameter.hum) {
    return ContentService.createTextOutput("Missing parameters");
  }

  var date = new Date();
  var time = Utilities.formatDate(date, timezone, "HH:mm:ss");

  var temp = stripQuotes(e.parameter.temp);
  var hum = stripQuotes(e.parameter.hum);

  var row = [date, time, temp, hum];
  sheet.appendRow(row);

  return ContentService.createTextOutput("Data Sent to Sheets!");
}

function stripQuotes(value) {
  return value.toString().replace(/^["']|["']$/g, "");
}


function getData(e) {
  return postData(e); 
}

```

## 🚀 Step 2: Deploy as a Web App

1. In the **Apps Script editor**, click on `Deploy > Manage deployments`.
2. Click **+ New deployment**.
3. Click **Select type** and choose **Web app**.
4. Fill in the deployment form:
   - **Description**: `Data Logger` (or anything meaningful)
   - **Execute as**: `Me`
   - **Who has access**: `Anyone`
5. Click **Deploy**.
6. Review and accept any **authorization permissions**.
7. Copy the generated **Web App URL**, which will look like this: https://script.google.com/macros/s/AKfycb.../exec


## 📥 Step 3: Clone The Repo 

Clone the repo to the local machine and add the Web URL to the Arduino Sketches

1. esp32-googlesheets-logger.ino - WiFi logging
2. sim800l-googlesheets-logger.ino - GPRS logging


## 🌐 Step 4: Middleware Deployment Guide for SIM800L ➝ Google Sheets

This middleware bridges simple HTTP GET requests from a SIM800L GSM module to Google Sheets' HTTPS endpoint, which SIM800L cannot access directly.


### 🖥️ 1. SSH into Your Server

```bash
ssh your-user@41.90.109.101
cd http-middle-man
node index.js
```

now add the server url to sim800l code: http://41.90.109.101:3000/post-data?temp=25.6&hum=67.3
